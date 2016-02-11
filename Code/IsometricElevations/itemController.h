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
using namespace std;
namespace itemControllerNS
{
	const int GUN_TEXTURE_WIDTH = 136;
	const int GUN_TEXTURE_HEIGHT = 41;
	const int GUN_TEXTURE_COLS = 2;
	const int GUN_PISTOL_FRAME = 8;
	const int GUN_MACHINEGUN_FRAME = 0;
	const int GUN_SHOTGUN_FRAME = 3;
	const enum ItemType { machineGun, shotGun, pistol };
}

class ItemController : public Entity
{
private:
	list<VECTOR2>* levelCrateLoc[NUM_LEVEL];
	list<int>* levelCrateItemType[NUM_LEVEL];
	list<Crate*>* crateList;
	vector<Item*> itemList;
	TextureManager* itemTexture;
	enum ItemType{healthPack};
public:
	ItemController();
	ItemController(Graphics*);
	virtual ~ItemController();
	void spawnCrates(int, Game*);
	void spawnItem(Game*, int x, int y);
	list<VECTOR2>* getCrateLoc();
	void update(float);
	void render(float);
	void collisions();
	list<Crate*>* getCrateList();
	int getGunFrameByItemType(int i);
protected:
	TextureManager* gunTexture;
	Image* gunImage;
};
#endif