#include "player.h"

Player::Player()
{
	wood = 100;
	stone = 100;
	iron = 0;
	money = 100;
}

uint32_t Player::GetWood()
{
	return wood;
}

uint32_t Player::GetStone()
{
	return stone;
}

uint32_t Player::GetIron()
{
	return iron;
}

uint32_t Player::GetMoney()
{
	return money;
}

void Player::AddToMoney(uint32_t n)
{
	money += n;
}

void Player::AddToWood(uint32_t n)
{
	wood += n;
}

void Player::AddToStone(uint32_t n)
{
	stone += n;
}

void Player::AddToIron(uint32_t n)
{
	iron += n;
}



