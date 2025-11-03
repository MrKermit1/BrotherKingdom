#include "hero.h"
#include "../../../globals.h"
Hero::Hero()
{
}
Hero::Hero(const char* name, uint8_t speed, uint8_t armor, uint8_t attack, uint8_t defence, uint8_t lifePoints, Vector2 position) : Creature(name, speed, armor, attack, defence, lifePoints, position)
{
	world.SetCameraTarget(Vector2{ position.x - (SCREEN_WIDTH / 4), position.y - (SCREEN_HEIGHT / 4) });
	racePath = "assets/creatures/dwarfs/warrior.gif";
	//animation
	currentAnimFrame = 0;
	frameDelay = 10;
	frameCounter = 0;
	animFrames = 0;
	nextFrameDataOffset = 0;
	imCreatureAnim = LoadImageAnim(racePath.c_str(), &animFrames);
	texture = LoadTextureFromImage(imCreatureAnim);
}