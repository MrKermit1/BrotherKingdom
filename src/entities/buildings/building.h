#pragma once
#include <iostream>
#include "raylib.h"
class Building
{
public:
	enum BuildingType
	{
		BASE,
		SAWMILL,
	};

	Building(BuildingType type);
	Building(Vector2 pos);
	Building(Vector2 pos, BuildingType type);

	bool IsInBuildMode();

	void Draw();
	void Build();
	void Update();
	void OnClick();
protected: 
	bool clicked;
	bool buildMode;

	static const float BUILDING_SIZE;
	Vector2 position;
	Vector2 size;
	Texture2D texture;
	BuildingType type;
	void SwitchTexture();
	void HandleBuilding();
};

