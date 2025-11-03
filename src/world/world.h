#pragma once
#include "terrain/terrainnode.h"
#include "raylib.h"
#include "../entities/creatures/creature.h"
#include "../client/player/player.h"
#include "../entities/buildings/building.h"
#include <vector>
class World
{
public:
	World();
	std::vector<Vector2> FindPath(Vector2 startPos, Vector2 targetPos);
	Camera2D* GetCamera();
	Vector2 FindNearestWalkableNode(Vector2 startPos);
	TerrainNode GetTerrainNodeByPosition(Vector2 pos);
	size_t GetCreaturesQuanity();
	bool CheckCreatureOnPosition(Vector2 pos);
	bool CheckCreatureOnPosition(Vector2 pos, uint16_t id);
	void Draw();
	void Update();
	void Move();
	void AddCreature(Creature* creature);
	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, uint8_t ammount);
	void UnclickNodes();
	void SetCameraTarget(Vector2 target);
private:
	bool CheckTerrain(uint16_t x, uint16_t y, TerrainNode::TerrainType type);
	
	TerrainNode** map;
	Camera2D camera;
	Vector2 currentTarget;
	
	std::vector<Creature*> creatures;
	void WalkingOnNode(TerrainNode *node, Creature* creature, Vector2 target);
	void InitGame();
};

