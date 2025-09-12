#include "building.h"
#include "../../globals.h"
#include <cmath>

const float Building::BUILDING_SIZE = 100;

Building::Building(Vector2 pos, BuildingType type)
{
	position = pos;
	this->type = type;
	clicked = false;
	buildMode = true;
	size = { Building::BUILDING_SIZE, Building::BUILDING_SIZE };
	SwitchTexture();
}

Building::Building(BuildingType type)
{
	this->type = type;
	clicked = false;
	buildMode = true;
	size = { Building::BUILDING_SIZE, Building::BUILDING_SIZE };
	SwitchTexture();
}

bool Building::IsInBuildMode()
{
	return buildMode;
}

void Building::Build()
{
	buildMode = true;
}

void Building::Draw()
{
	if (buildMode)
	{
		Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *world.GetCamera());
		mousePosition.x -= texture.width / 2;
		mousePosition.y -= texture.height / 2;
		DrawTextureV(texture, mousePosition, WHITE);
	}
	else
	{
		DrawTextureV(texture, position, WHITE);
	}
}

void Building::Update()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && buildMode)
	{
		Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *world.GetCamera());

		uint16_t ceiledX = RoundUp(mousePosition.x, 25);
		uint16_t ceiledY = RoundUp(mousePosition.y, 25);

		Vector2 ceiledPosition = { ceiledX, ceiledY };

		position = ceiledPosition;

		uint8_t nodesNumber = (size.x / TerrainNode::NODE_SIZE) * (size.y / TerrainNode::NODE_SIZE);

		Vector2 currentPosition = position;
		bool isNonWalkable = false;
		for (uint8_t i = 0; i < nodesNumber; i++)
		{
			if (currentPosition.x < position.x + size.x)
			{
				currentPosition.x += TerrainNode::NODE_SIZE;
			}
			else
			{
				currentPosition.y += TerrainNode::NODE_SIZE;
				currentPosition.x = position.x + TerrainNode::NODE_SIZE;
			}

			std::cout << "it: " << std::to_string(i) << "act pos: " << currentPosition.x << " : " << currentPosition.y << "\n";
			std::cout << "is walkable: " << world.GetTerrainNodeByPosition(currentPosition).IsWalkable() << "\n";

			if (!world.GetTerrainNodeByPosition(currentPosition).IsWalkable())
			{
				isNonWalkable = true;
			}
		}

		if (!isNonWalkable)
		{
			buildMode = false;
		}
	}

	if (clicked)
	{
		ui.OpenBuildingMenu(type);
	}
}

void Building::OnClick()
{
	if 
	(
		(IsMouseOnEntity(position, size, GetScreenToWorld2D(GetMousePosition(), *(world.GetCamera())))
		&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
		&& !buildMode
	)
	{
		clicked = !clicked;
	}
	else
	{

		world.UnclickNodes();
	}
}

void Building::SwitchTexture()
{
	switch (type)
	{
	case Building::BASE:
		texture = LoadTexture("assets/buildings/base.png");
		break;
	case Building::SAWMILL:
		texture = LoadTexture("assets/buildings/sawmill.png");
		break;
	default:
		break;
	}
}