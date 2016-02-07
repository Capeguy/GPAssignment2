#include "pistol.h"

using namespace std;
Pistol::Pistol() {
	ammo = -1;
	maxAmmo = -1;
	id = pistol;
	cooldown = 0.4f;
	damage = 10;
	bullet_speed = 80.0f;
	Gun();
}

Pistol::~Pistol() {

}
Projectile* Pistol::shoot(LevelController* lc, float frametime) {
	if (cooldowncurrent <= 0 && hasAmmo()) {
		if (ammo != -1)
			ammo--;
		gameptr->console->print("Remaining ammo: ");
		gameptr->console->print(to_string(ammo));
		cooldowncurrent = cooldown;
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
		cooldowncurrent -= frametime;
	}
	return nullptr;
}
void Projectile::setOwner(int o) {
	owner = o;
}
int Projectile::getOwner() {
	return owner;
}