#include "inventory.h"
using namespace std;
Inventory::Inventory() {
	InventoryItems = new vector<InventoryItem*>();
	activeItem = nullptr;
	activeItemIndex = 0;
}
Inventory::~Inventory() {

}
void Inventory::update(float frameTime, Input* input) {
	if (!updating) {
<<<<<<< HEAD
		if (input->isKeyDown(PLAYER_SWITCH_ITEM_BACK) || input->isKeyDown(PLAYER_SWITCH_ITEM_FORWARD)) {
			updating = true;
			if (input->isKeyDown(PLAYER_SWITCH_ITEM_BACK)) // Q
				activeItemIndex--;
			else if (input->isKeyDown(PLAYER_SWITCH_ITEM_FORWARD)) // E
=======
		if (input->isKeyDown(PLAYER_INVENT_CYCLE_LEFT) || input->isKeyDown(PLAYER_INVENT_CYCLE_RIGHT)) {
			updating = true;
			if (input->isKeyDown(PLAYER_INVENT_CYCLE_LEFT))
				activeItemIndex--;
			else if (input->isKeyDown(PLAYER_INVENT_CYCLE_RIGHT))
>>>>>>> 3eaf24dac7fa302c3734884001eae0069dd8eb66
				activeItemIndex++;
			if (activeItemIndex < 0)
				activeItemIndex = InventoryItems->size() - 1;
			if (activeItemIndex >= InventoryItems->size())
				activeItemIndex = 0;
			activeItem = InventoryItems->at(activeItemIndex);
		}
	} else {
<<<<<<< HEAD
		if (!input->isKeyDown(PLAYER_SWITCH_ITEM_BACK) && !input->isKeyDown(PLAYER_SWITCH_ITEM_FORWARD)) { // TODO: Softcode this keys into constants.h - Done
=======
		if (!input->isKeyDown(PLAYER_INVENT_CYCLE_LEFT) && !input->isKeyDown(PLAYER_INVENT_CYCLE_RIGHT)) {
>>>>>>> 3eaf24dac7fa302c3734884001eae0069dd8eb66
			updating = false;
		}
	}
}

vector<InventoryItem*>* Inventory::getItems() {
	return InventoryItems;
}
bool Inventory::addItem(InventoryItem *item) {
	if (InventoryItems->size() >= inventoryControllerNS::MAX_INVENTORY_SIZE)
		return false;
	InventoryItems->push_back(item);
	if (activeItem == nullptr)
		activeItem = item;
	return true;
}
bool Inventory::addItems(vector<InventoryItem> items) {
	for (vector<InventoryItem>::iterator it = items.begin(); it != items.end(); ++it) {
		if (!addItem(&(*it)))
			return false;
	}
	return true;
}
InventoryItem* Inventory::getActiveItem() {
	return activeItem;
}