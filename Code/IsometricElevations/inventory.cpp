#include "inventory.h"
using namespace std;
Inventory::Inventory () {
	InventoryItems = new vector<InventoryItem> (); // new List<InventoryItem*>();
	//inventoryItems = List<InventoryItem>();
}
Inventory::~Inventory () {

}
void Inventory::update (float frameTime) {

}

vector<InventoryItem>* Inventory::getItems () {
	return InventoryItems;
}
bool Inventory::addItem (InventoryItem item) {
	InventoryItems->push_back (item);
	return true;
}
bool Inventory::addItems (vector<InventoryItem> items) {
	/*
	for each(InventoryItem* item in items) {
		InventoryItems->add(item);
	}
	*/
	return true;
}