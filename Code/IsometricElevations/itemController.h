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
}

class ItemController : public Entity
{
private:
	list<VECTOR2>* levelCrateLoc[NUM_LEVEL];
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
};
#endif