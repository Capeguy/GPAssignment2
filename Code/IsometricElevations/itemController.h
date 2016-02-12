#pragma once
#ifndef _ITEMCONTROLLER_H                 // Prevent multiple definitions if this 
#define _ITEMCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include "constants.h"
#include "item.h"
#include "healthPack.h"
#include "entity.h"
#include "crate.h"
#include <vector>
#include <list>

namespace itemControllerNS
{
	const int GUN_TEXTURE_WIDTH = 136;
	const int GUN_TEXTURE_HEIGHT = 41;
	const int GUN_TEXTURE_COLS = 2;
	const int GUN_PISTOL_FRAME = 8;
	const int GUN_MACHINEGUN_FRAME = 0;
	const int GUN_SHOTGUN_FRAME = 3;
	const enum ItemType { machineGun, shotGun, pistol };
	const int ICO_TEXTURE_SIZE = 32;
}

class ItemController : public Entity
{
private:
	std::list<VECTOR2>* levelCrateLoc[NUM_LEVEL];
	std::list<int>* levelCrateItemType[NUM_LEVEL];
	std::list<Crate*>* crateList;
	std::list<Image*> crateIcons;
	std::vector<Item*> itemList;
	TextureManager* itemTexture;
	TextureManager* itemIconTexture;
	enum ItemType{healthPack};
public:
	ItemController();
	ItemController(Graphics*, TextureManager*);
	virtual ~ItemController();
	void spawnCrates(int, Game*);
	void spawnItem(Game*, int x, int y);
	std::list<VECTOR2>* getCrateLoc();
	void update(float, float);
	void render(float);
	void collisions();
	std::list<Crate*>* getCrateList();
	int getGunFrameByItemType(int i);
protected:
	TextureManager* gunTexture;
	Image* gunImage;
};
#endif