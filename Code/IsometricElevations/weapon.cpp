#include "weapon.h"

using namespace std;
Weapon::Weapon () : Entity () {
	// spriteData.width = playerNS::WIDTH;           // size of player ship
	// spriteData.height = playerNS::HEIGHT;
	// spriteData.x = playerNS::X;                   // location on screen
	// spriteData.y = playerNS::Y;
	// spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	// spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	// frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	// startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
	// endFrame = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
}

Weapon::~Weapon () {

}

bool Weapon::initialize (Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	return(Entity::initialize (gamePtr, width, height, ncols, textureM));
}
void Weapon::draw () {
	//spriteData.scale = 0.5;
	Image::draw ();              // draw ship
}
void Weapon::update (float frameTime) {
	Entity::update (frameTime);
}