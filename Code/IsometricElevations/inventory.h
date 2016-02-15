//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _INVENTORY_H                 // Prevent multiple definitions if this 
#define _INVENTORY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include "constants.h"
#include "list.h"
#include <vector>
#include "inventoryItem.h"

namespace inventoryControllerNS {
	const int MAX_INVENTORY_SIZE = 5;
}

class Inventory
{
private:
	std::vector<InventoryItem*>	*InventoryItems;
	InventoryItem* activeItem;
	int activeItemIndex;
	bool updating = false;
public:
	Inventory();
	~Inventory();
	void update(float frameTime, Input* input);
	std::vector<InventoryItem*>* getItems();
	bool addItem(InventoryItem *item);
	bool addItems(std::vector<InventoryItem> items);
	InventoryItem* getActiveItem();
};
#endif