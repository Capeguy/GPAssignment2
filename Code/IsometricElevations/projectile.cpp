#include "projectile.h"


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
	speed = 100.0f;
}

Projectile::~Projectile() {

}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, double dmg) {
	damage = dmg;
	owner = Player;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Projectile::draw(TextDX &dxFont) {
	if (velocity.x < 0)
		flipHorizontal(true);
	/*
	string buffer;
	buffer = std::to_string((int)getX());
	buffer += ", ";
	buffer += std::to_string((int)getY());
	dxFont.print(buffer, getX(), getY() - 16);
	*/
	Image::draw();              // draw ship
}
void Projectile::update(float frameTime) {
	if (getX() < 0 || getY() < 0 || getX() > GAME_WIDTH || getY() > GAME_HEIGHT) {
		// delete this; // If only it was that easy.
	} else {
		//setX(getX() - offsetOld.x);
		Entity::update(frameTime);
		//setX(getX() + offsetOld.x);
	}
}
void Projectile::collision() {

}
double Projectile::getDamage() {
	return damage;
}

void Projectile::setDamage(double d)
{
	damage = d;
}

float Projectile::getSpeed()
{
	return speed;
}

void Projectile::setSpeed(float s)
{
	speed = s;
}
