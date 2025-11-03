#include "world.h"
#include "../entities/creatures/creature.h"
#include <queue>
#include <map>
#include "../globals.h"

World::World()
{
	InitGame();
    map = new TerrainNode *[64];

    for (int i = 0; i < 64; i++)
    {
        map[i] = new TerrainNode[48];
    }

    camera = { 0 };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    GenerateWorld();
    GenerateTerrain(TerrainNode::STONE, 30);
    GenerateTerrain(TerrainNode::FOREST, 100);
}

std::vector<Vector2> World::FindPath(Vector2 startPos, Vector2 targetPos)
{
    struct Node
    {
        Vector2 position;
        float cost;
        float priority;
    };

    auto cmp = [](Node left, Node right) { return left.priority > right.priority; };

    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> frontier(cmp);

    std::map<std::pair<int, int>, Vector2> cameFrom;
    std::map<std::pair<int, int>, float> costSoFar;

    auto gridPos = [](Vector2 pos) { return std::make_pair((int)(pos.x / 25), (int)(pos.y / 25)); };
    auto heuristic = [](Vector2 a, Vector2 b)
    {
        return fabs(a.x - b.x) + fabs(a.y - b.y);
    };

    frontier.push({ startPos, 0, 0 });
    cameFrom[gridPos(startPos)] = startPos;
    costSoFar[gridPos(startPos)] = 0;

    while (!frontier.empty())
    {
        Node current = frontier.top();
        frontier.pop();

        if (gridPos(current.position) == gridPos(targetPos))
            break;

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (abs(dx) + abs(dy) != 1) continue;

                int newX = (int)(current.position.x / 25) + dx;
                int newY = (int)(current.position.y / 25) + dy;

                if (newX >= 0 && newX < 64 && newY >= 0 && newY < 48)
                {
                    if (map[newX][newY].GetType() != TerrainNode::GRASS)
                        continue;

                    Vector2 nextPos = map[newX][newY].GetPosition();
                    float newCost = costSoFar[gridPos(current.position)] + 1;

                    if (!costSoFar.count(gridPos(nextPos)) || newCost < costSoFar[gridPos(nextPos)])
                    {
                        costSoFar[gridPos(nextPos)] = newCost;
                        float priority = newCost + heuristic(targetPos, nextPos);
                        frontier.push({ nextPos, newCost, priority });
                        cameFrom[gridPos(nextPos)] = current.position;
                    }
                }
            }
        }
    }

    std::vector<Vector2> path;
    Vector2 current = targetPos;
    while (gridPos(current) != gridPos(startPos))
    {
        path.push_back(current);
        if (cameFrom.find(gridPos(current)) == cameFrom.end())
        {
            path.clear();
            break;
        }
        current = cameFrom[gridPos(current)];
    }
    path.push_back(startPos);
    std::reverse(path.begin(), path.end());

    return path;
}

Camera2D* World::GetCamera()
{
    return &camera;
}

void World::GenerateWorld()
{
	for (uint8_t i = 0; i < 64; i++)
	{
		for (uint8_t j = 0; j < 48; j++)
		{
			map[i][j] = TerrainNode(Vector2{i * 25.0f, j * 25.0f}, TerrainNode::GRASS);
		}
	}
}

void World::GenerateTerrain(TerrainNode::TerrainType type, uint8_t ammount)
{
    uint16_t x = RandomNumber(0, 62);
    uint16_t y = RandomNumber(0,  47);

    for (uint8_t i = 0; i < ammount; i++)
    {

        while (!(CheckTerrain(x, y, TerrainNode::GRASS)))
        {
            x = RandomNumber(0, 62);
            y = RandomNumber(0, 46);
        }

        map[x][y].SetType(type);
        map[x + 1][y].SetType(type);
        map[x][y + 1].SetType(type);
        map[x + 1][y + 1].SetType(type);
    }
}

void World::UnclickNodes()
{
    for (uint8_t i = 0; i < 64; i++)
    {
        for (uint8_t j = 0; j < 48; j++)
        {
            map[i][j].UnClick();
        }
    }
}

void World::SetCameraTarget(Vector2 target)
{
    camera.target = target;
}

void World::WalkingOnNode(TerrainNode* node, Creature* creature, Vector2 target)
{
    Vector2 nearest = FindNearestWalkableNode(target);
    if (creature->IsClicked() && node->IsClicked())
    {
        
        std::vector<Vector2> path;

        path = FindPath(creature->GetPosition(), nearest);
        creature->SetPath(path);
        creature->SetTargetNode(node);
        creature->SetNearestTraget(nearest);


        node->UnClick();
		
        creature->UnClick();
        return;
    }

}

void World::InitGame()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fantasy Commander");
}

void World::AddCreature(Creature* creature)
{
    creatures.push_back(creature);
}

bool World::CheckTerrain(uint16_t x, uint16_t y, TerrainNode::TerrainType type)
{
    return
        map[x][y].GetType() == type ||
        map[x + 1][y].GetType() == type ||
        map[x][y + 1].GetType() == type ||
        map[x + 1][y + 1].GetType() == type;
}

bool World::CheckCreatureOnPosition(Vector2 pos)
{
    for (Creature* c : creatures)
    {
        if (c->GetPosition().x == pos.x && c->GetPosition().y == pos.y)
        {
            return true;
		}
    }
    
	return false;
}

bool World::CheckCreatureOnPosition(Vector2 pos, uint16_t id)
{
    for (Creature* c : creatures)
    {
        if (c->GetPosition().x == pos.x && c->GetPosition().y == pos.y && c->GetId() != id)
        {
            return true;
        }
    }

    return false;
}

Vector2 World::FindNearestWalkableNode(Vector2 startPos)
{
    Vector2 bestPos = startPos;
    double bestDistance = FLT_MAX;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int newX = (int)(startPos.x / 25) + dx;
            int newY = (int)(startPos.y / 25) + dy;

            if (newX >= 0 && newX < 64 && newY >= 0 && newY < 48)
            {
                if (map[newX][newY].GetType() == 0 && !CheckCreatureOnPosition(map[newX][newY].GetPosition()))
                {
                    double distance = sqrt(pow(startPos.x - map[newX][newY].GetPosition().x, 2) + 
                                      pow(startPos.y - map[newX][newY].GetPosition().y, 2));

                    if (distance < bestDistance)
                    {
                        bestDistance = distance;
                        bestPos = map[newX][newY].GetPosition();
                    }
                }
            }
        }
    }

    return bestPos;
}

TerrainNode World::GetTerrainNodeByPosition(Vector2 pos)
{ 
    int x = pos.x;
    int y = pos.y;

    int roundedX = RoundUp(x, (int)TerrainNode::NODE_SIZE);
    int roundedY = RoundUp(y, (int)TerrainNode::NODE_SIZE);

    int arrX = roundedX / 25;
    int arrY = roundedY / 25;

    if (!(arrX > 63) && !(arrY > 47))
    {
        return map[arrX][arrY];
    }

    std::cout << "returned basic node (not good)\n";
    return TerrainNode();
}

size_t World::GetCreaturesQuanity()
{
    return creatures.size();
}

void World::Draw()
{
    BeginMode2D(camera);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j].Draw();
        }
    }

    for (Creature* c : creatures)
    {
        //if (c.IsHero())
        //{
        //    ((Hero&)c).Draw();
        //}
        //else
        //{
        //    c.Draw();
        //}
        c->Draw();
    }

    EndMode2D();
}

void World::Update()
{
    float deltaTime = GetFrameTime();

    for (uint8_t i = 0; i < 64; i++)
    {
        for (uint8_t j = 0; j < 48; j++)
        {
            currentTarget = map[i][j].OnClick(&camera);

            for (Creature* c : creatures)
            {
                WalkingOnNode(&map[i][j], c, currentTarget);
            }
        }
    }

    for (Creature* c : creatures)
    {
        c->OnClick();
        c->UpdateMovement(deltaTime);
        if (c->IsMoving())
        {
            c->Animate();
        }
    }

    int cameraSpeed = 10;
    camera.zoom += GetMouseWheelMove() * cameraSpeed / 100.0f;
}

void World::Move()
{
    
}
    