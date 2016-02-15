//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "healthPack.h"

HealthPack::HealthPack() : Item() {
	type = Usable;
	spriteData.x = healthPackNS::X;              // location on screen
	spriteData.y = healthPackNS::Y;
	startFrame = healthPackNS::START_FRAME;    // first frame of crate animation
	endFrame = healthPackNS::END_FRAME;      // last frame of crate animation
	setCurrentFrame(startFrame);
	spriteData.rect.bottom = healthPackNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = healthPackNS::WIDTH;
	RECT e;
	e.right = healthPackNS::WIDTH / 2;
	e.left = -healthPackNS::WIDTH / 2;
	e.bottom = healthPackNS::HEIGHT / 2;
	e.top = -healthPackNS::HEIGHT / 2;
	setEdge(e);
}

bool HealthPack::initialize(Game *gamePtr, TextureManager* itemTexture) {
	return Entity::initialize(gamePtr, healthPackNS::WIDTH, healthPackNS::HEIGHT, healthPackNS::TEXTURE_COLS, itemTexture);
}
