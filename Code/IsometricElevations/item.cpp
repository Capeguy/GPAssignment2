//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "item.h"

Item::Item() {
	textureManager = TextureManager();
}

Item::~Item() {}
bool Item::initialize(Game * gamePtr, int width, int height, int ncols, std::string file) {
	textureManager.initialize(gamePtr->getGraphics(), file.c_str());
	return false;
}
void Item::update(float frametime, int orientation, float x, float y) {
	//Entity::update(frametime);
}
int Item::getItemType() {
	return type;
}

std::string Item::getItemName() {
	return name;
}
