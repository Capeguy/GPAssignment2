#pragma once
#ifndef _PISTOL_H                 // Prevent multiple definitions if this 
#define _PISTOL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "gun.h"

namespace pistolNS {
	const int spacing = 32;
}

class Pistol : public Gun
{
private:

public:
	Pistol();
	~Pistol();
	Projectile* shoot(LevelController* lc, float frametime);
	void setCooldown(float);
};
#endif