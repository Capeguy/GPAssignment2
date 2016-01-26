#pragma once
#ifndef _CRATE_H                 // Prevent multiple definitions if this 
#define _CRATE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "item.h"
#include "entity.h"

using namespace std;

namespace crateNS
{
	//const int	TEXTURE_COLS = 2;
	const int	WIDTH = 64;
	const int	HEIGHT = 64;
	const int   START_FRAME = 0;        // starts at frame 1
	const int   END_FRAME = 0;
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   COLLISION_RADIUS = 120 / 2;   // for circular collision
}

class Crate : public Entity
{
public:
	Crate();
	void spawnItem();
};
#endif