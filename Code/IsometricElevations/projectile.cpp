#include "projectile.h"


Projectile::Projectile() : Entity() {
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = 0;
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	speed = 100.0f;
}

Projectile::~Projectile() {}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, double dmg) {
	damage = dmg;
	owner = Player;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Projectile::draw(TextDX &dxFont) {
	if (velocity.x < 0)
		flipHorizontal(true);
	Image::draw();
}
void Projectile::update(float frameTime) {
	if (getX() < 0 || getY() < 0 || getX() > GAME_WIDTH || getY() > GAME_HEIGHT) {
		visible = false;
		// delete this; // If only it was that easy.
	} else {
		//setX(getX() - offsetOld.x);
		Entity::update(frameTime);
		//setX(getX() + offsetOld.x);
	}
}
void Projectile::collision() {}
double Projectile::getDamage() {
	return damage;
}

void Projectile::setDamage(double d) {
	damage = d;
}

float Projectile::getSpeed() {
	return speed;
}

void Projectile::setSpeed(float s) {
	speed = s;
}
