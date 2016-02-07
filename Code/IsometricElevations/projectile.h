#pragma once
#ifndef _PROJECTILE_H                 // Prevent multiple definitions if this 
#define _PROJECTILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "list.h"
#include "constants.h"

namespace projectileNS
{
	const int PISTOL_BULLET_FRAME = 1;
	const int MACHINEGUN_BULLET_FRAME = 2;
	const int SHOTGUN_BULLET_FRAME = 4;
}

class Projectile : public Entity {
private:
	double damage;
	float speed;
	int owner;
public:
	enum Owners {Player, NPC};
	Projectile ();
	~Projectile ();
	virtual void draw ();
	virtual bool initialize (Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, double dmg = 0);
	void update (float frameTime);
	void collision();
	double getDamage();
	void setDamage(double d);
	float getSpeed();
	void setSpeed(float s);
	void setOwner(int o);
	int getOwner();
};
#endif
