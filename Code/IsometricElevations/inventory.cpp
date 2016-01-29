#include "inventory.h"
using namespace std;
Inventory::Inventory() {
	InventoryItems = new vector<InventoryItem*>(); // new List<InventoryItem*>();
	activeItem = nullptr;
	activeItemIndex = 0;
	//inventoryItems = List<InventoryItem>();
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

			//MessageBox(NULL, to_string(activeItemIndex).c_str(), NULL, NULL);
			activeItem = InventoryItems->at(activeItemIndex);
		}
	} else {
		if (!input->isKeyDown(0x51) && !input->isKeyDown(0x45)) {
			updating = false;
		}
	}
	
}

vector<InventoryItem*>* Inventory::getItems() {
	return InventoryItems;
}
bool Inventory::addItem(InventoryItem *item) {
	InventoryItems->push_back(item);
	if (activeItem == nullptr)
		activeItem = item;
	return true;
}
bool Inventory::addItems(vector<InventoryItem> items) {
	/*
	for each(InventoryItem item in items) {
		InventoryItems->add(item);
	}
	*/
	return true;
}
InventoryItem* Inventory::getActiveItem() {
	return activeItem;
}