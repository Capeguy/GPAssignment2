#include "projectile.h"

using namespace std;
Projectile::Projectile() : Entity() {
	//spriteData.width = playerNS::WIDTH;           // size of player ship
	//spriteData.height = playerNS::HEIGHT;
	//spriteData.x = playerNS::X;                   // location on screen
	//spriteData.y = playerNS::Y;
	//spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	//spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	//frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	//startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
	//endFrame = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
	startFrame = 0;
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
}

Projectile::~Projectile() {

}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, double dmg) {
	damage = dmg;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Projectile::draw() {
	Image::draw();              // draw ship
}
void Projectile::update(float frameTime) {
	if (getX() < 0 || getY() < 0 || getX() > GAME_WIDTH || getY() > GAME_HEIGHT) {
		// delete this; // If only it was that easy.
	} else {
		Entity::update(frameTime);
	}
}
void Projectile::collision() {

}
double Projectile::getDamage() {
	return damage;
}