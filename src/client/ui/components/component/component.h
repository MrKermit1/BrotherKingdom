#pragma once
#include "raylib.h"
#include <functional>
class Component
{
public:
	Component(Vector2 position, Vector2 size, Color backgroundColor);
	Component();
	void Draw();
	void OnClick();
	void SetOnClickEvent(void(*onClickEvent)());
protected:
	Vector2 position;
	Vector2 size;
	bool clicked;
	Color backgroundColor;
	void(*onClickEvent)();
};

