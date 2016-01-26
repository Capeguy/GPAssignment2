#pragma once
#ifndef _MACHINEGUN_H                 // Prevent multiple definitions if this 
#define _MACHINEGUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "gun.h"

using namespace std;
/*
namespace machineGunNS
{
	int TEXTURE_WIDTH = 67;
	int TEXTURE_HEIGHT = 41;
	int TEXTURE_COLS = 2;
}
*/
class MachineGun : public Gun
{
private:

public:
	//explict
	MachineGun();
	~MachineGun();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void update(float frameTime, int orientation, float x, float y);
	void draw();
	bool Shoot();
};
#endif