//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "pistol.h"


Pistol::Pistol() {
	ammo = -1;
	maxAmmo = -1;
	id = pistol;
	cooldown = 0.3f;
	damage = 4;
	bullet_speed = 400.0f;
	Gun();
}

Pistol::~Pistol() {}
Projectile* Pistol::shoot(LevelController* lc, float frametime) {
	if (cooldownCurrent <= 0 && hasAmmo()) {
		audio->playCue(PISTOL_SHOT);
		if (ammo != -1)
			ammo--;
		cooldownCurrent = cooldown;
		bullet = new Projectile();
		bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
		bullet->setCurrentFrame(projectileNS::PISTOL_BULLET_FRAME);
		bullet->setSpeed(bullet_speed);
		bullet->setDamage(damage);
		bullet->spriteData.angle = angle;
		D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle)); // normalize the vector idk what but it works lol
		bullet->setX(getX() + mousePos.x * gunNS::PISTOL_OFFSET); // <---- the 32 should be the gun sprites width
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
void Pistol::setCooldown(float c) {
	cooldown = c;
}
void Projectile::setOwner(int o) {
	owner = o;
}
int Projectile::getOwner() {
	return owner;
}