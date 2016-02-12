#include "bossGun.h"

BossGun::BossGun()
{
	ammo = -1;
	maxAmmo = -1;
	cooldown = 0.4f;
	damage = 10;
	bullet_speed = 200.0f;
	Gun();
}

BossGun::~BossGun()
{
}

void BossGun::update(float frametime, int orientation, float x, float y, Input * input, LevelController * lc, float destX, float destY, bool shouldShoot)
{
	playerX = x;
	playerY = y;
	adjacent = destX - x;
	opposite = destY - y;
	angle = atan((opposite / adjacent));
	spriteData.angle = angle;
	if (adjacent < 0) // facing back
	{
		setX(x);
		setY(y+80);
		flipHorizontal(true);
	}
	else {
		setX(x + 50);
		setY(y+80);
		flipHorizontal(false);
	}
	angle = atan((destY - getY()) / (destX - getX()));
	//fire bullet
	if (shouldShoot) { // Cause AI calls this
		Projectile* p = shoot(lc, frametime);
		if (p != nullptr)
			p->setOwner(Projectile::NPC);
	}
	else {
		cooldowncurrent -= frametime;
	}
	Entity::update(frametime);
}

Projectile * BossGun::shoot(LevelController * lc, float frametime)
{
	if (cooldowncurrent <= 0 && hasAmmo()) {
		audio->playCue(PISTOLSHOT);
		if (ammo != -1)
			ammo--;
		gameptr->console->print("Remaining ammo: ");
		gameptr->console->print(std::to_string(ammo));
		cooldowncurrent = cooldown;
		bullet = new Projectile();
		bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
		bullet->setCurrentFrame(0);
		bullet->setSpeed(bullet_speed);
		bullet->setDamage(damage);
		bullet->spriteData.angle = angle;
		D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle)); // normalize the vector idk what but it works lol
		bullet->setX(getX() + mousePos.x * gunNS::PISTOL_OFFSET); // <---- the 32 should be the gun sprites width
		bullet->setY(getY());
		if (adjacent >= 0) {
			bullet->setVelocity(mousePos);
			bullet->spriteData.angle = angle;
		}
		else {
			bullet->setVelocity(-mousePos);
		}
		lc->addProjectile(bullet);
		bullets.push_back(bullet);
		return bullet;
	}
	else {
		cooldowncurrent -= frametime;
	}
	return nullptr;
}
