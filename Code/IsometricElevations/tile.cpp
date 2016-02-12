#include "Tile.h"

Tile::Tile () {}

Tile::Tile (int i, bool s) {
	id = i;
	solid = s;
}

Tile::~Tile () {}

bool Tile::initialize (Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	return(Entity::initialize (gamePtr, width, height, ncols, textureM));
}
void Tile::draw () {

	//spriteData.scale = 0.5;
	Entity::draw ();              // draw ship
}
int Tile::getId () {
	return id;
}
void Tile::setId(int i) {
	id = i;
	currentFrame = i;
}
bool Tile::isSolid () {
	if (this == nullptr)
		return true;
	return solid;
}