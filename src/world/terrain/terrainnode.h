#pragma once
#include "raylib.h"
class TerrainNode
{
public:
	enum TerrainType
	{
		GRASS,
		FOREST,
		STONE,
		OCCUPIED,
	};

	static const float NODE_SIZE;

	TerrainNode();
	TerrainNode(Vector2 pos, TerrainNode::TerrainType type);

	bool IsClicked() const;
	bool IsWalkable() const;
	bool operator==(const TerrainNode& other) const;

	Vector2 OnClick(Camera2D* camera);
	TerrainType GetType();
	Vector2 GetPosition();

	void SetType(TerrainType type);
	void SetPosition(Vector2 pos);
	void UnClick();
	void Draw();
private:
	bool clicked;
	bool walkable;

	Vector2 position;
	Texture2D texture;
	TerrainType type;

	void SwitchTexture();
};

