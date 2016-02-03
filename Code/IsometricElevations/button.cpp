#include "button.h"

Button::Button(int i)
{
	id = i;
}

Button::~Button()
{
}

bool Button::isHovered(Input* input)
{
	float mouseX = input->getMouseX();
	float mouseY = input->getMouseY();
	if (mouseX >= topLeft.x && mouseX <= topRight.x && mouseY >= topLeft.y && mouseY <= bottomLeft.y) {
		return true;
	}
	return false;
}

bool Button::isClicked(Input* input)
{
	return input->getMouseLButton() && isHovered(input);
}

void Button::update(float frameTime)
{
	Entity::update(frameTime);
}

int Button::getID()
{
	return id;
}

bool Button::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}
