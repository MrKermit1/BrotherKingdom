#include "creature.h"
#include <queue>
#include "../../globals.h"
#include "raymath.h"

Creature::Creature(Vector2 pos, Creature::Profession proffesion)
{
	id = (uint16_t)(world.GetCreaturesQuanity());
	position = pos;
	this->proffesion = proffesion;
	this->taken = false;
	clicked = false;
	AssignRace();
	AssignProffesion();
	speed = 100.0f;
	//animation
	currentAnimFrame = 0;
	frameDelay = 10;
	frameCounter = 0;
	animFrames = 0;
	nextFrameDataOffset = 0;
	imCreatureAnim = LoadImageAnim(racePath.c_str(), &animFrames);
	texture = LoadTextureFromImage(imCreatureAnim);

	//filters
	SetTextureFilter(texture, TEXTURE_FILTER_POINT);
	SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
	world.AddCreature(*this);
}

bool Creature::IsClicked()
{
	return clicked;
}

void Creature::Draw()
{
	const float radius = 15.0f;
	if (clicked)
	{
		DrawCircle((int)(position.x + radius), (int)(position.y + radius), radius, BLUE);
	}
	DrawTextureV(texture, position, WHITE);
}

void Creature::OnClick()
{
	Vector2 nodeSize = { TerrainNode::NODE_SIZE, TerrainNode::NODE_SIZE, };
	if 
	(
		IsMouseOnEntity(position, nodeSize, GetScreenToWorld2D(GetMousePosition(), *(world.GetCamera()))) 
		&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
	)
	{
		clicked = !clicked;
	}
}

void Creature::UnClick()
{
	clicked = false;
}

void Creature::SetNearestTraget(Vector2 pos)
{
	nearestTarget = pos;
}

void Creature::SetPath(const std::vector<Vector2>& newPath)
{
	path = newPath;
}

void Creature::SetTargetNode(TerrainNode* node)
{
	targetNode = node;
}

bool Creature::IsMoving() const
{
	return !path.empty();
}

void Creature::Animate()
{
	frameCounter++;
	if (frameCounter >= frameDelay)
	{
		currentAnimFrame++;

		if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

		nextFrameDataOffset = imCreatureAnim.width * imCreatureAnim.height * 4 * currentAnimFrame;
		UpdateTexture(texture, ((unsigned char*)imCreatureAnim.data) + nextFrameDataOffset);

		frameCounter = 0;
	}
}

void Creature::Take()
{
	this->taken = !taken;
}

bool Creature::IsTaken() const
{
	return taken;
}

void Creature::UpdateMovement(float deltaTime)
{
	if (world.CheckCreatureOnPosition(position, id))
	{
		Vector2 newPosition = world.FindNearestWalkableNode(position);
		position = newPosition;
	}

	if (nearestTarget.x == position.x && nearestTarget.y == position.y)
	{
		targetNode->SetType(TerrainNode::GRASS);

		nearestTarget = { -1, -1 };
	}

	if (!path.empty())
	{
		Vector2 target = path.front();
		Vector2 direction = Vector2Subtract(target, position);
		float distance = Vector2Length(direction);

		if (distance < 1.0f)
		{
			position = target;
			path.erase(path.begin());
		}
		else
		{
			direction = Vector2Normalize(direction);
			position.x += direction.x * speed * deltaTime;
			position.y += direction.y * speed * deltaTime;
		}
	}
}

void Creature::AssignProffesion()
{
	switch (proffesion)
	{
	case Creature::WARRIOR:
		racePath.append("warrior.gif");
		break;
	case Creature::WIZARD:
		racePath.append("wizard.gif");
		break;
	case Creature::WORKER:
		racePath.append("worker.gif");
		break;
	default:
		break;
	}
}

void Creature::AssignRace()
{

	racePath = "assets/creatures/dwarfs/";

}

Vector2 Creature::GetPosition()
{
	return position;
}

TerrainNode* Creature::GetTargetNode() const
{
	return targetNode;
}

int Creature::GetId()
{
	return id;
}

void Creature::SetPosition(Vector2 pos)
{
	position = pos;
}
