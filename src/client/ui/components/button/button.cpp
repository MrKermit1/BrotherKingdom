#include "button.h"
#include "../../../../globals.h"

Button::Button(Vector2 position, Vector2 size, Color backgroundColor, const char* text) : Component(position, size, backgroundColor)
{
	this->text = text;
}

Button::Button() : Component()
{

}

void Button::Draw()
{
	DrawRectangleV(position, size, backgroundColor);
	DrawText(text, position.x + (size.x / 16), position.y + (size.y / 4), 12, BLACK);
}

void Button::OnClick()
{
	if (IsMouseOnEntity(position, size, GetMousePosition()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		clicked = !clicked;
		onClickEvent();
	}
}

