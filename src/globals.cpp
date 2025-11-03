#include "globals.h"
#include "raylib.h"
#include <random>
Player player = Player();
World world = World();
UI ui = UI();
int SCREEN_WIDTH = 1900;
int SCREEN_HEIGHT = 1000;

std::vector<Component> uiComponents;
std::vector<Button> buttons;

size_t SizeOfChar(const char* text)
{
	std::string textInString(text);
	return textInString.size();
}

bool IsMouseOnEntity(Vector2 entityPosition, Vector2 entitySize, Vector2 mousePosition)
{
    return 
    (
        mousePosition.x >= entityPosition.x
        && !(mousePosition.x > entityPosition.x + entitySize.x)
        && mousePosition.y >= entityPosition.y
        && !(mousePosition.y > entityPosition.y + entitySize.y)
    );
}

int RoundUp(int n, int multiplier)
{
    if (multiplier == 0)
    {
        return n;
    }

    int divisionRest = n % multiplier;

    if (divisionRest == 0)
    {
        return n;
    }

    return n + multiplier - divisionRest;
}

uint16_t RandomNumber(uint16_t min, uint16_t max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

