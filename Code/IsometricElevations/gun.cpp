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
			if (orientation == Right) 
			{
				bullet->setVelocity(D3DXVECTOR2(100, 0));
			} 
			else if (orientation == Left)
			{
				bullet->setVelocity(D3DXVECTOR2(-100, 0));
			}
			else if (orientation == Up)
			{
				bullet->setVelocity(D3DXVECTOR2(0, -100));
				bullet->spriteData.angle = -PI / 2;
			}
			else if (orientation == Down)
			{
				bullet->setVelocity(D3DXVECTOR2(0, 100));
				bullet->spriteData.angle = PI / 2;
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
	if (orientation == Up) { // up
		//spriteData.x = x;
		//spriteData.y = y;
		setX(x- 16);
		setY(y- 16);
		if (previousOreintation == Right)
			spriteData.angle = -PI / 2;
		else if (previousOreintation == Left)
			spriteData.angle = PI / 2;
	}
	if (orientation == Right) // right
	{
		flipHorizontal(false);
		setX(x + 16);
		setY(y);
		spriteData.angle = 0;
	}
	if (orientation == Down) { //down
		setX(x - 16);
		setY(y + 16);
		if (previousOreintation == Right)
			spriteData.angle = -3 * PI / 2;
		else if (previousOreintation == Left)
			spriteData.angle = 3 * PI / 2;
	}
	if (orientation == Left) //left 
	{
		flipHorizontal(true);
		setX(x - 48);
		setY(y);
		spriteData.angle = 0;
	}
	
	previousOreintation = orientation;
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
void Gun::addAmmo()
{
	double a = (double(maxAmmo) / 100.0) * 20.0;
	int add = (int)(a);
	if (ammo < maxAmmo)
	{
		ammo += add;
	}
	if (ammo > maxAmmo)
	{
		ammo = maxAmmo;
	}
}

int Gun::getGunId()
{
	return id;
}
