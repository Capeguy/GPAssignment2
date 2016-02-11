#include "item.h"


Item::Item () {
	textureManager = TextureManager ();
}

Item::~Item () {

}

bool Item::initialize (Game * gamePtr, int width, int height, int ncols, std::string file) {
	textureManager.initialize (gamePtr->getGraphics (), file.c_str ());
	return false;
}
void Item::update(float frametime, int orientation, float x, float y) {
	//Entity::update(frametime);
}
int Item::getItemType() {
	return type;
}

std::string Item::getItemName()
{
	return name;
}
