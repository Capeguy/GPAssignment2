//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

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
InventoryItem::~InventoryItem() {}

void InventoryItem::update(float frameTime) {

}
Item* InventoryItem::getItem() {
	return item;
}