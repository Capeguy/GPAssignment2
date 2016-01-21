#include "inventoryController.h"

using namespace std;
InventoryController::InventoryController(Player p) {
	player = p;
	//inventoryItems = List<InventoryItem>();
}
InventoryController::~InventoryController() {

}
void InventoryController::update(float frameTime) {
	
}

vector<InventoryItem> InventoryController::getItems() {
	return inventoryItems;
}
bool InventoryController::addItem() {
	return false;
}
bool InventoryController::addItems() {
	return false;
}