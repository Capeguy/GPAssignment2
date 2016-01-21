#pragma once
#ifndef _PISTOL_H                 // Prevent multiple definitions if this 
#define _PISTOL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "item.h"
#include "gun.h"

using namespace std;

namespace pistolNS
{

}

class Pistol : Gun
{
private:

public:
	//explict
	Pistol();
	~Pistol();
	bool Shoot();
};
#endif