#pragma once
#ifndef _SHOTGUN_H                 // Prevent multiple definitions if this 
#define _SHOTGUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "item.h"
#include "gun.h"

using namespace std;

namespace shotgunNS
{

}

class Shotgun : Gun
{
private:

public:
	//explict
	Shotgun();
	~Shotgun();
	bool Shoot();
};
#endif