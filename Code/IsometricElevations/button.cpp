#include "button.h"

Button::Button(int i) {
	id = i;
	pressed = false;
}

Button::~Button() {}

bool Button::isHovered(Input* input) {
	float mouseX = input->getMouseX();
	float mouseY = input->getMouseY();
	if (mouseX >= topLeft.x && mouseX <= topRight.x && mouseY >= topLeft.y && mouseY <= bottomLeft.y)
		return true;
	return false;
}

bool Button::isClicked(Input* input) {
	if (input->getMouseLButton() && isHovered(input)) {
		pressed = true;
		return true;
	}
	return false;
}

bool Button::isReleased(Input* input) {
	if (!active)
		return false;
	if (input->getMouseLButton()) {
		pressed = true;
		return false;
	} else if (pressed && !input->getMouseLButton() && isHovered(input)) {
		pressed = false;
		return true;
	}
	return false; 
}

void Button::update(float frameTime) {
	Entity::update(frameTime);
}

int Button::getID() {
	return id;
}

bool Button::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM) {
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}
