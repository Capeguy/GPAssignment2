#pragma once
#ifndef _WEAPON_H                 // Prevent multiple definitions if this 
#define _WEAPON_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace weaponNS
{

}

class Weapon : public Entity
{
	enum PlayerOrientation { right, down, left, up };
	enum PlayerHealthStatus { Alive, Dead };
private:

public:
	Weapon();
	~Weapon();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
};
#endif