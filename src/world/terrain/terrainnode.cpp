#include "terrainnode.h"
#include <iostream>
#include "../../globals.h"

TerrainNode::TerrainNode()
{
    position = { 0.0f, 0.0f };
    type = TerrainNode::GRASS;
    walkable = false;
    clicked = false;
	SwitchTexture();
}

TerrainNode::TerrainNode(Vector2 pos, TerrainNode::TerrainType type)
{
    position = pos;
    this->type = type;
    walkable = false;
    clicked = false;
    SwitchTexture();
}

const float TerrainNode::NODE_SIZE = 25.0f;

bool TerrainNode::IsClicked() const
{
    return clicked;
}

bool TerrainNode::IsWalkable() const
{
    return walkable;
}

bool TerrainNode::operator==(const TerrainNode& other) const
{
    return this->position.x == other.position.x &&
        this->position.y == other.position.y &&
        this->type == other.type;
}

TerrainNode::TerrainType TerrainNode::GetType()
{
    return this->type;
}

void TerrainNode::SetType(TerrainType type)
{
    if (this != nullptr)
    {
        this->type = type;
        SwitchTexture();
    }
}

void TerrainNode::SetPosition(Vector2 pos)
{
    position = pos;
}

Vector2 TerrainNode::OnClick(Camera2D *camera)
{
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);

    if
    (
        IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)
        && mousePosition.x >= position.x
        && !(mousePosition.x > position.x + NODE_SIZE)
        && mousePosition.y >= position.y
        && !(mousePosition.y > position.y + NODE_SIZE)
    )
    {
        std::cout << "NODE:     x:" << position.x << " y:" << position.y << "\n";
        world.UnclickNodes();
        clicked = !clicked;
        return position;
    }

    return position;
}

void TerrainNode::UnClick()
{
    clicked = false;
}

void TerrainNode::Draw()
{
    DrawTextureV(texture, position, WHITE);
    if (clicked)
    {
        //Draw cross
        DrawLineV(position, { position.x + NODE_SIZE, position.y + NODE_SIZE }, RED);
        DrawLine((int)(position.x + NODE_SIZE), (int)(position.y), (int)(position.x), (int)(position.y + NODE_SIZE), RED);
    }
}

void TerrainNode::SwitchTexture()
{

    switch (type)
    {
    case TerrainNode::GRASS:
        texture = LoadTexture("assets/terrain/grass.png");
		walkable = true;
        break;
    case TerrainNode::FOREST:
        texture = LoadTexture("assets/terrain/forest.png");
        walkable = false;
        break;
    case TerrainNode::STONE:
        texture = LoadTexture("assets/terrain/stone.png");
        walkable = false;
        break;
    default:
        break;
    }
}

Vector2 TerrainNode::GetPosition()
{
	return position;
}
