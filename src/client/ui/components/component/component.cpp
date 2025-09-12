#include "component.h"
#include "../../../../globals.h"

Component::Component(Vector2 position, Vector2 size, Color backgroundColor)
{
	this->clicked = false;
	this->position = position;
	this->size = size;
	this->backgroundColor = backgroundColor;
}

Component::Component()
{

}

void Component::OnClick()
{

}

void Component::SetOnClickEvent(void(*onClickEvent)())
{
	this->onClickEvent = onClickEvent;
}

void Component::Draw()
{

}

