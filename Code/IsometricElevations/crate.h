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

// TODO: Handle collision between Crate and Player --> Should give item in crate to player
// TODO: Get ItemController / LevelController to spawn the crates
namespace crateNS
{
	const int	TEXTURE_COLS = 2;
	const int	WIDTH = 32;
	const int	HEIGHT = 41;
	const int   START_FRAME = 13;        // starts at frame 1
	const int   END_FRAME = 13;
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const enum ItemType { machineGun, shotGun, pistol };
}

class Crate : public Entity {
private:
	//HealthPack* hp;
	int itemId;
	std::vector<Entity> itemList;
public:
	Crate();
	void spawnItem(Crate* c);
	//void addItem(Inventory* i, Game* gameptr, TextureManager* gunTexture, int id);
	bool initialize(Game *gamePtr, TextureManager* itemTexture, int itemtype);
	enum item { pistol, machineGun, shotGun, healthPack };
	int getItemId();
	void setItemId(int i);
};
#endif