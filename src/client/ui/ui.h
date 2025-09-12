#pragma once
#include "components/button/button.h"
#include "raylib.h"
#include "../../entities/buildings/building.h"

class UI
{
public:
	UI();

	void DrawResources();
	void DrawShop();
	void OpenBuildingMenu(Building::BuildingType type);
	void Update();
	void Draw();

private:
	Vector2 menuSize;
	Vector2 menuPosition;
	Vector2 resourcesSize;
	Vector2 resourcesPosition;
	Building::BuildingType typeOfBuildingMenu;
};

