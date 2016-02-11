#include "inventoryItem.h"


InventoryItem::InventoryItem() {}
InventoryItem::InventoryItem(Item* i) {
	item = i;
	count = 1;
}
InventoryItem::InventoryItem(Item*& i, int cnt) {
	item = i;
	count = cnt;
}
InventoryItem::~InventoryItem() {

}

void InventoryItem::update(float frameTime) {

}
Item* InventoryItem::getItem() {
	return item;
}