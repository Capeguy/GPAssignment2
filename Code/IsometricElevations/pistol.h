#pragma once
#ifndef _PISTOL_H                 // Prevent multiple definitions if this 
#define _PISTOL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "gun.h"

using namespace std;

namespace pistolNS
{

}

class Pistol : public Gun
{
private:

public:
	//explict
	Pistol();
	~Pistol();
	bool Shoot();
};
#endif