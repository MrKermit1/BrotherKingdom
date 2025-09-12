#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "../../world/terrain/terrainnode.h"

class Creature
{
public:
	enum Profession
	{
		WARRIOR,
		WIZARD,
		WORKER
	};

	Creature(Vector2 pos, Creature::Profession proffesion);
	bool IsClicked();
	bool IsMoving() const;
	Vector2 GetPosition();
	TerrainNode* GetTargetNode() const;
	int GetId();
	void Draw();
	void OnClick();
	void UnClick();
	void SetPosition(Vector2 pos);
	void SetNearestTraget(Vector2 pos);
	void SetPath(const std::vector<Vector2>& newPath);
	void SetTargetNode(TerrainNode* node);
	void UpdateMovement(float deltaTime);
	void Animate();
	void Take();
	bool IsTaken() const;
private:
	uint16_t id;
	uint8_t lifePoints;
	uint8_t currentAnimFrame;
	uint8_t frameDelay;
	uint8_t frameCounter;
	int32_t animFrames ;
	bool taken;
	int32_t nextFrameDataOffset;
	float speed;
	bool clicked;

	Image imCreatureAnim;
	Profession proffesion;
	Vector2 position;
	Vector2 nearestTarget;
	Texture2D texture;
	TerrainNode* targetNode;
	std::vector<Vector2> path;
	std::string racePath;

	void AssignProffesion();
	void AssignRace();
};

