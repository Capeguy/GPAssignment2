#pragma once
#ifndef _ITEM_H                 // Prevent multiple definitions if this 
#define _ITEM_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC
#include "entity.h"
#include "constants.h"
#include "list.h"



namespace itemNS
{

}

class Item : public Entity // Abstract class
{
	
protected:
	
	int id;
	std::string name;
	std::string desc;
	int type;
	TextureManager textureManager;
public:
	enum ItemType { Equipable, Usable };
	Item();
	virtual ~Item();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, std::string);
	virtual void update(float frametime, int orientation, float x, float y);
	int getItemType();
	std::string getItemName();

};
#endif