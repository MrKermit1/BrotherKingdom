#pragma once
#include <vector>

class Player
{
public:
	Player();

	uint32_t GetWood();
	uint32_t GetStone();
	uint32_t GetIron();
	uint32_t GetMoney();

	void AddToMoney(uint32_t n);
	void AddToWood(uint32_t n);
	void AddToStone(uint32_t n);
	void AddToIron(uint32_t n);

private:
	uint32_t money;
	uint32_t wood;
	uint32_t stone;
	uint32_t iron;
};

