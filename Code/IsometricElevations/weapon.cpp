#include "weapon.h"

Weapon::Weapon() : Entity() {
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
}

Weapon::~Weapon() {}

bool Weapon::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Weapon::draw() {
	Image::draw();
}
void Weapon::update(float frameTime) {
	Entity::update(frameTime);
}