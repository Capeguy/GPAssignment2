#include "shotgun.h"

Shotgun::Shotgun() {
	ammo = 10;
	maxAmmo = 10;
	id = shotGun;
	cooldown = 1.0f;
	damage = 20;
	bullet_speed = 800.0f;
	Gun();
}

Shotgun::~Shotgun() {

}
Projectile* Shotgun::shoot(LevelController* lc, float frametime) {
	if (cooldownCurrent <= 0 && hasAmmo()) {
		audio->playCue(SHOTGUN_SHOT);
		if (ammo != -1)
			ammo--;
		cooldownCurrent = cooldown;
		bullet = new Projectile();
		bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
		bullet->setCurrentFrame(projectileNS::SHOTGUN_BULLET_FRAME);
		bullet->setSpeed(bullet_speed);
		bullet->setDamage(damage);
		bullet->spriteData.angle = angle;
		D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle)); // normalize the vector idk what but it works lol
		bullet->setX(getX() + mousePos.x * gunNS::SHOTGUN_OFFSET); // <---- the 32 should be the gun sprites width
		bullet->setY(getY());
		if (adjacent >= 0) {
			bullet->setVelocity(mousePos);
			bullet->spriteData.angle = angle;
		} else {
			bullet->setVelocity(-mousePos);
		}
		lc->addProjectile(bullet);
		bullets.push_back(bullet);
		return bullet;
	} else {
		cooldownCurrent -= frametime;
	}
	return nullptr;
}
