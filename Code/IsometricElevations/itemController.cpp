#include "itemController.h"

ItemController::ItemController() {}

ItemController::ItemController(Graphics *graphics) {
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = new list<Crate*>();
	levelCrateLoc[0].push_back(VECTOR2(321, 508));
	levelCrateLoc[0].push_back(VECTOR2(652, 704));
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
	//int itemId = 0 + (std::rand() % (2 - 0 + 1));
	int itemId = 0;
	Item item;
	switch (itemId) {
		case healthPack:
			HealthPack* hp = new HealthPack();
			hp->initialize(gamePtr, itemTexture);
			hp->setX(x);
			hp->setY(y);
	}
}

void ItemController::update(float frameTime) {
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		(*it)->update(frameTime);
	}
}

void ItemController::render() {
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		(*it)->draw();
	}
}

list<Crate*>* ItemController::getCrateList() {
	return crateList;
}
void ItemController::collisions() {

}