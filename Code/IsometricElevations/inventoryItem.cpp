#include "inventoryItem.h"

using namespace std;
InventoryItem::InventoryItem (Item i) {
	item = i;
	count = 1;
}
InventoryItem::InventoryItem (Item i, int cnt) {
	item = i;
	count = cnt;
}
InventoryItem::~InventoryItem () {

}

void InventoryItem::update (float frameTime) {

}
