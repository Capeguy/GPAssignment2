#pragma once
#ifndef _GUN_H                 // Prevent multiple definitions if this 
#define _GUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "item.h"

using namespace std;

namespace gunNS
{

}

class Gun : Item // Still an abstract class
{
protected:
	int ammo = 10;
	int maxAmmo = 10;
	float cooldown = 0.2f;
public:
	//explicit
	Gun();
	~Gun();
	bool Shoot();
};
#endif