#pragma once
#ifndef _MACHINEGUN_H                 // Prevent multiple definitions if this 
#define _MACHINEGUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "gun.h"
#include "OSD.h"

using namespace std;

class MachineGun : public Gun {
private:

public:
	//explict
	MachineGun ();
	~MachineGun ();
	void draw();
};
#endif