#pragma once
#ifndef _INVENTORYITEM_H                 // Prevent multiple definitions if this 
#define _INVENTORYITEM_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "list.h"
#include "item.h"
#include "constants.h"


namespace inventoryItemNS
{

}

class InventoryItem
{
private:
	int count;
	Item* item;

public:
	InventoryItem();
	InventoryItem(Item* i);
	InventoryItem(Item*& i, int cnt);

	~InventoryItem();

	void update(float frameTime);
	Item* getItem();
};
#endif