#include "Base.h"

Base::Base(Vector2 pos) : Building(pos, Building::BASE)
{

}

void Base::HandleMenuOpen()
{
	if (clicked && !buildMode)
	{
		//open base menu
	}
}
