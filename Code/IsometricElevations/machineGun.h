#pragma once
#ifndef _MACHINEGUN_H                 // Prevent multiple definitions if this 
#define _MACHINEGUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "item.h"
#include "gun.h"

using namespace std;

namespace machineGunNS
{

}

class MachineGun : Gun
{
private:

public:
	//explict
	MachineGun();
	~MachineGun();
	bool Shoot();
};
#endif