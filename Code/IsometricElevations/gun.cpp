#include "gun.h"

using namespace std;
Gun::Gun() {
	type = Equipable;
	spriteData.x = 0;                   // location on screen
	spriteData.y = 0;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = 0.2f;
	startFrame = 0;     // first frame of ship animation
	endFrame = 0;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	bullets = vector<Projectile*>();
}

Gun::~Gun() {

}
bool Gun::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM) {
	gameptr = gamePtr;
	bulletTexture = new TextureManager();
	if (!bulletTexture->initialize(gamePtr->getGraphics(), TEXTURE_BULLETS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}
bool Gun::Shoot() {
	return false;
}
void Gun::update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc) {
	if (input->isKeyDown(VK_SHIFT)) {
		if (cooldowncurrent <= 0 && hasAmmo()) {
			if (ammo != -1)
				ammo--;
			gameptr->console->print("Remaining ammo: ");
			gameptr->console->print(to_string(ammo));
			cooldowncurrent = cooldown;
			bullet = new Projectile();
			bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
			bullet->setCurrentFrame(1);
			bullet->setX(getX());
			bullet->setY(getY());
			if (orientation == 0) {
				bullet->setVelocity(D3DXVECTOR2(100, 0));
			} else {
				bullet->setVelocity(D3DXVECTOR2(-100, 0));
			}
			lc->addProjectile(bullet);
			bullets.push_back(bullet);
		} else {
			cooldowncurrent -= frametime;
		}
	} else {
		cooldowncurrent -= frametime;
	}
	/* Hmm
	for (int i = 0; i < bullets.size(); i++) {
		bullet = bullets.at(i);
		bullet->setX(bullet->getX() + bullet->getVelocity().x * frametime);
		bullet->setY(bullet->getY() + bullet->getVelocity().y * frametime);
		bullet->update(frametime);
	}
	*/
	if (orientation == 0) // right
	{
		flipHorizontal(false);
		setX(x + 16);
		setY(y);
		spriteData.flipHorizontal = false;
		spriteData.x = x + 16;
		spriteData.y = y;
	}
	if (orientation == 1) {

	}
	if (orientation == 2) //left 
	{
		flipHorizontal(false);
		setX(x - 48);
		setY(y);
		spriteData.flipHorizontal = true;
		spriteData.x = x - 48;
		spriteData.y = y;
	}
	if (orientation == 3) {
		spriteData.x = x;
		spriteData.y = y;
		setX(x);
		setY(y);
	}
	Entity::update(frametime);
}
void Gun::draw() {
	Entity::draw();
}
void Gun::collision() {
	for (int i = 0; i < bullets.size(); i++) {
		bullet = bullets.at(i);
		bullet->collision();
	}
}
bool Gun::hasAmmo() {
	return ammo > 0 || ammo == -1;
}
string Gun::getAmmoDisplay() {
	if (ammo == -1) {
		return "?";
	} else
		return to_string(ammo);
}