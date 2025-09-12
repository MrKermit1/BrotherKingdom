#pragma once
#include "../building.h"
class Base : public Building
{
public:
	Base(Vector2 pos);
	void HandleMenuOpen();
};

