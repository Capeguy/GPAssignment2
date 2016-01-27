#include "healthPack.h"

HealthPack::HealthPack() : Item()
{
	spriteData.x = healthPackNS::X;              // location on screen
	spriteData.y = healthPackNS::Y;
	startFrame = healthPackNS::START_FRAME;    // first frame of crate animation
	endFrame = healthPackNS::END_FRAME;      // last frame of crate animation
	setCurrentFrame(startFrame);
	spriteData.rect.bottom = healthPackNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = healthPackNS::WIDTH;
	radius = healthPackNS::COLLISION_RADIUS;
}
