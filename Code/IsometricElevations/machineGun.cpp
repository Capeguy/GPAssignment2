#include "machineGun.h"

using namespace std;
MachineGun::MachineGun () : Gun () {
	ammo = 100;
	maxAmmo = 150;
	id = machineGun;
	cooldown = 0.2f;
	damage = 10;
	bullet_speed = 200.0f;
	Gun ();
}

MachineGun::~MachineGun () {

}
void MachineGun::shoot(LevelController* lc, float frametime)
{
	if (cooldowncurrent <= 0 && hasAmmo())
	{
		if (ammo != -1)
			ammo--;
		gameptr->console->print("Remaining ammo: ");
		gameptr->console->print(to_string(ammo));
		cooldowncurrent = cooldown;
		bullet = new Projectile();
		bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
		bullet->setCurrentFrame(projectileNS::MACHINEGUN_BULLET_FRAME);
		bullet->setSpeed(bullet_speed);
		bullet->setDamage(damage);
		bullet->spriteData.angle = angle;
		D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle)); // normalize the vector idk what but it works lol
		bullet->setX(getX() + mousePos.x * 48); // <---- the 32 should be the gun sprites width
		bullet->setY(getY());
		if (adjacent >= 0)
		{
			bullet->setVelocity(mousePos);
			bullet->spriteData.angle = angle;
		}
		else
		{
			bullet->setVelocity(-mousePos);
		}
		lc->addProjectile(bullet);
		bullets.push_back(bullet);
	}
	else
	{
		cooldowncurrent -= frametime;
	}
}
void MachineGun::draw() {
	
}