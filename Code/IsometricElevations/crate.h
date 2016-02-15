//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _CRATE_H                 // Prevent multiple definitions if this 
#define _CRATE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC
#include "constants.h"
#include "item.h"
#include "inventory.h"
#include "inventoryItem.h"
#include "entity.h"
#include <vector>

namespace crateNS {
	const int	TEXTURE_COLS = 2;
	const int	WIDTH = 32;
	const int	HEIGHT = 41;
	const int   START_FRAME = 13;        // starts at frame 1
	const int   END_FRAME = 13;
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const enum ItemType { machineGun, shotGun, pistol };
}

class Crate : public Entity
{
private:
	int itemId;
	std::vector<Entity> itemList;
public:
	enum item { pistol, machineGun, shotGun, healthPack };
	Crate();
	bool	initialize(Game *gamePtr, TextureManager* itemTexture, int itemtype);
	int		getItemId();
	void	setItemId(int i);
};
#endif