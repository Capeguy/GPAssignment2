#pragma once
#ifndef _ITEM_H                 // Prevent multiple definitions if this 
#define _ITEM_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "list.h"

using namespace std;

namespace itemNS
{

}

class Item // Abstract class
{
	
protected:
	enum ItemType { Equipable, Usable };
	int id;
	string name;
	string desc;
	int type;
public:
	Item();
	~Item();
};
#endif