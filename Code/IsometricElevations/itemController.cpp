#include "itemController.h"

ItemController::ItemController() {}

ItemController::ItemController(Graphics *graphics) {
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = new list<Crate*>();
	itemList = vector<Item*>();
	levelCrateLoc[0].push_back(VECTOR2(321, 568));
	levelCrateLoc[0].push_back(VECTOR2(1152, 250));
}

ItemController::~ItemController() {}

void ItemController::spawnCrates(int level, Game *gamePtr) {
	list<VECTOR2> crateLocations = levelCrateLoc[level - 1];
	for (list<VECTOR2>::iterator crateLocationIter = crateLocations.begin(); crateLocationIter != crateLocations.end(); ++crateLocationIter) {
		Crate* c = new Crate();
		c->initialize(gamePtr, itemTexture);
		c->setX((*crateLocationIter).x);
		c->setY((*crateLocationIter).y);
		crateList->push_back(c);
	}
}

void ItemController::spawnItem(Game *gamePtr, int x, int y) {
}

void ItemController::update(float frameTime) {
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		(*it)->update(frameTime);
	}
}

void ItemController::render(float mapX) {
	int count = 0;
	list<VECTOR2> crateLocations = levelCrateLoc[0];
	list<VECTOR2>::iterator l_front = crateLocations.begin();
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		std::advance(l_front, count);
		(*it)->setX(float((*l_front).x + mapX));
		(*it)->draw();
		count++;
	}
}

list<Crate*>* ItemController::getCrateList() {
	return crateList;
}
void ItemController::collisions() {

}