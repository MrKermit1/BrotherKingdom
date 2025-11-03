#pragma once
#include "../creature.h"

class Hero : public Creature
{
public:
	Hero();
	Hero(const char* name, uint8_t speed, uint8_t armor, uint8_t attack, uint8_t defence, uint8_t lifePoints, Vector2 position);
	void Draw() override;
};

