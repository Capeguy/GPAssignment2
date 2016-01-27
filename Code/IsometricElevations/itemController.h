#pragma once
#ifndef _ITEMCONTROLLER_H                 // Prevent multiple definitions if this 
#define _ITEMCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "item.h"
#include "entity.h"
#include "crate.h"
#include <vector>
using namespace std;
namespace itemControllerNS
{
}

class ItemController : public Entity
{
private:
	vector<VECTOR2> levelCrateLoc[NUM_LEVEL];
	vector<Crate> crateList;
public:
	ItemController();
	void spawnCrates(int, Game*, TextureManager *itemTexture);
	void update(float);
	void render();
	
};
#endif