//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "Tile.h"

Tile::Tile() {}

Tile::Tile(int i, bool s) {
	id = i;
	solid = s;
}

Tile::~Tile() {}

bool Tile::initialize() {
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

bool Tile::initialize(Game *gp, int w, int h, int n, TextureManager *t) {
	gamePtr = gp;
	width = w;
	height = h;
	ncols = n;
	textureM = t;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Tile::draw() {
	Entity::draw();              // draw ship
}
int Tile::getId() {
	return id;
}
void Tile::setId(int i) {
	id = i;
	currentFrame = i;
}
void Tile::refresh(float frameTime) {
	stayTime -= frameTime;
	if (stayTime <= 0) {
		currentFrame = id;
		initialize();
	}
}
bool Tile::isSolid(bool skip) {
	if (this == nullptr)
		return true;
	if (!skip && false) { // Remove false for debug
		stayTime = 0.2;
		if (solid) {
			currentFrame = 1;
			initialize();
		} else {
			currentFrame = 500;
			initialize();
		}
	}
	return solid;
}
void Tile::setSolid(bool s) {
	solid = s;
}