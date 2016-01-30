#pragma once
#ifndef _ITEM_H                 // Prevent multiple definitions if this 
#define _ITEM_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "list.h"

using namespace std;

namespace itemNS
{

}

class Item : public Entity // Abstract class
{
	
protected:
	
	int id;
	string name;
	string desc;
	int type;
	TextureManager textureManager;
public:
	enum ItemType { Equipable, Usable };
	Item();
	virtual ~Item();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, string);
	virtual void update(float frametime, int orientation, float x, float y);
	int getItemType();
	string getItemName();

};
#endif