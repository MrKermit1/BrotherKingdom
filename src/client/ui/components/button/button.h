#pragma once
#include "raylib.h"
#include "../component/component.h"
#include <iostream>

class Button : public Component
{
public:
	Button(Vector2 position, Vector2 size, Color backgroundColor, const char* text);
	Button();
	void Draw();
	void OnClick();
private:
	
	const char* text;
};

