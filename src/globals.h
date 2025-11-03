#pragma once
#include "world/world.h"
#include "client/player/player.h"
#include "client/ui/ui.h"
#include "client/ui/components/component/component.h"
#include "client/ui/components/button/button.h"
#include "entities/creatures/hero/hero.h"
#include <iostream>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern Player player;
extern World world;
extern UI ui;

extern std::vector<Component> uiComponents;
extern std::vector<Button> buttons;

size_t SizeOfChar(const char* text);
bool IsMouseOnEntity(Vector2 entityPosition, Vector2 entitySize, Vector2 mousePosition);
int RoundUp(int n, int multiplier);
uint16_t RandomNumber(uint16_t min, uint16_t max);