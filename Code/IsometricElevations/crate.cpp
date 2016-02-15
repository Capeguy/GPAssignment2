#include "crate.h"

Crate::Crate() : Entity() {
	spriteData.x = crateNS::X;              // location on screen
	spriteData.y = crateNS::Y;
	startFrame = crateNS::START_FRAME;		// first frame of crate animation
	endFrame = crateNS::END_FRAME;			// last frame of crate animation
	setCurrentFrame(startFrame);
	spriteData.rect.bottom = crateNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = crateNS::WIDTH;
	collisionType = entityNS::BOX;
	itemList = std::vector<Entity>();
	RECT e;
	e.right = crateNS::WIDTH / 2;
	e.left = -crateNS::WIDTH / 2;
	e.bottom = crateNS::HEIGHT / 2;
	e.top = -crateNS::HEIGHT / 2;
	setEdge(e);
	itemId = -1; //default itemID
}

bool Crate::initialize(Game *gamePtr, TextureManager* itemTexture, int itemtype) {
	setItemId(itemtype);
	return Entity::initialize(gamePtr, crateNS::WIDTH, crateNS::HEIGHT, crateNS::TEXTURE_COLS, itemTexture);
}
int Crate::getItemId() {
	return itemId;
}

void Crate::setItemId(int i) {
	itemId = i;
}