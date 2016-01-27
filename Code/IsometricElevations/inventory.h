#pragma once
#ifndef _INVENTORY_H                 // Prevent multiple definitions if this 
#define _INVENTORY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include "constants.h"
#include "list.h"
#include <vector>
#include "inventoryItem.h"

namespace inventoryControllerNS
{

}

class Inventory {
private:
	vector<InventoryItem>	*InventoryItems;
public:
	Inventory ();
	~Inventory ();

	void update (float frameTime);

	vector<InventoryItem>* getItems ();
	bool addItem (InventoryItem item);
	bool addItems (vector<InventoryItem> items);

};
#endif