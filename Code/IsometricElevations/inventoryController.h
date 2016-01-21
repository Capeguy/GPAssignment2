#pragma once
#ifndef _INVENTORYCONTROLLER_H                 // Prevent multiple definitions if this 
#define _INVENTORYCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "player.h"
#include "constants.h"
#include "list.h"
#include <vector>
#include "inventoryItem.h"

namespace inventoryControllerNS
{

}

class InventoryController
{
private:
	Player player;
	vector<InventoryItem> inventoryItems;

public:
	InventoryController(Player p);
	~InventoryController();

	void update(float frameTime);

	vector<InventoryItem> getItems();
	bool addItem();
	bool addItems();

};
#endif