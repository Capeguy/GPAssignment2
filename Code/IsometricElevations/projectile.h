#pragma once
#ifndef _PROJECTILE_H                 // Prevent multiple definitions if this 
#define _PROJECTILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "list.h"
#include "constants.h"

namespace projectileNS
{

}

class Projectile : public Entity {
private:

public:
	Projectile ();
	~Projectile ();
	virtual void draw ();
	virtual bool initialize (Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update (float frameTime);
	void collision();
};
#endif