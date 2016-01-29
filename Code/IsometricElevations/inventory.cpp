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
		if (input->isKeyDown(0x51) || input->isKeyDown(0x45)) {
			updating = true;
			if (input->isKeyDown(0x51)) // Q
				activeItemIndex--;
			else if (input->isKeyDown(0x45)) // E
				activeItemIndex++;
			if (activeItemIndex < 0)
				activeItemIndex = InventoryItems->size() - 1;
			if (activeItemIndex >= InventoryItems->size())
				activeItemIndex = 0;
			activeItem = InventoryItems->at(activeItemIndex);
		}
	} else {
		if (!input->isKeyDown(0x51) && !input->isKeyDown(0x45)) { // TODO: Softcode this keys into constants.h
			updating = false;
		}
	}
}

vector<InventoryItem*>* Inventory::getItems() {
	return InventoryItems;
}
bool Inventory::addItem(InventoryItem *item) {
	// TODO: Implement a max inventory size so we can actually return false for once
	InventoryItems->push_back(item);
	if (activeItem == nullptr)
		activeItem = item;
	return true;
}
bool Inventory::addItems(vector<InventoryItem> items) {
	for (vector<InventoryItem>::iterator it = items.begin(); it != items.end(); ++it) {
		addItem(&(*it));
	}
	return true;
}
InventoryItem* Inventory::getActiveItem() {
	return activeItem;
}