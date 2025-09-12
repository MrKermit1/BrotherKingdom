#include "globals.h"
#include "raylib.h"

Player player = Player();
World world = World();
UI ui;

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
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mousePosition.x >= entityPosition.x
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

