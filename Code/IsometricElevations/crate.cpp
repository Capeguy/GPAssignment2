#include "crate.h"

Crate::Crate() : Entity()
{
	spriteData.x = crateNS::X;              // location on screen
	spriteData.y = crateNS::Y;
	startFrame = crateNS::START_FRAME;    // first frame of crate animation
	endFrame = crateNS::END_FRAME;      // last frame of crate animation
	setCurrentFrame(startFrame);
	spriteData.rect.bottom = crateNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = crateNS::WIDTH;
	radius = crateNS::COLLISION_RADIUS;
}

void Crate::spawnItem()
{
}