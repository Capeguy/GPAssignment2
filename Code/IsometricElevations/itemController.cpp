#include "itemController.h"

ItemController::ItemController() {}

ItemController::ItemController(Graphics *graphics) {
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = new list<Crate*>();
	itemList = vector<Item*>();
	levelCrateLoc[0] = new list<VECTOR2>();
	levelCrateLoc[0]->push_back(VECTOR2(321, 568));
	levelCrateLoc[0]->push_back(VECTOR2(1152, 250));
	levelCrateItemType[0] = new list<int>();
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);

	

	gunTexture = new TextureManager();
	if (!gunTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	gunImage = new Image();
	gunImage->initialize(graphics, itemControllerNS::GUN_TEXTURE_WIDTH, itemControllerNS::GUN_TEXTURE_HEIGHT, 1, gunTexture);
	//gunImage->setCurrentFrame(0);
}

ItemController::~ItemController() {}

void ItemController::spawnCrates(int level, Game *gamePtr) {
	list<VECTOR2>* crateLocations = levelCrateLoc[0];
	int locCounter = 0;
	for (list<VECTOR2>::iterator crateLocationIter = crateLocations->begin(); crateLocationIter != crateLocations->end(); ++crateLocationIter) {
		locCounter++;
		int itemCounter = 0;
		list<int>* crateItem = levelCrateItemType[0];
		for (list<int>::iterator crateItemTypeIter = crateItem->begin(); crateItemTypeIter!= crateItem->end(); ++crateItemTypeIter) {
			itemCounter++;
			if (locCounter == itemCounter)
			{
				Crate* c = new Crate();
				int itemtype = (*crateItemTypeIter);
				c->initialize(gamePtr, itemTexture, itemtype);
				c->setX((*crateLocationIter).x);
				c->setY((*crateLocationIter).y);
				crateList->push_back(c);
			}
		}
	}
}

void ItemController::spawnItem(Game *gamePtr, int x, int y) {
}

list<VECTOR2>* ItemController::getCrateLoc()
{
	return levelCrateLoc[0];
}

void ItemController::update(float frameTime) {
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		(*it)->update(frameTime);
	}
}

void ItemController::render(float mapX) {
	int count = 0;
	list<VECTOR2> *crateLocations = levelCrateLoc[0];
	list<VECTOR2>::iterator l_front = crateLocations->begin();
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		std::advance(l_front, count);
		(*it)->setX(float((*l_front).x + mapX));
		(*it)->draw();
		int itemid = (*it)->getItemId();
		gunImage->setCurrentFrame(getGunFrameByItemType(itemid));
		gunImage->setX((*it)->getX());
		gunImage->setY((*it)->getY()+18);
		gunImage->setScale(0.3);
		gunImage->draw();
		count++;
	}
}

list<Crate*>* ItemController::getCrateList() {
	return crateList;
}
int ItemController::getGunFrameByItemType(int i)
{
	switch (i)
	{
	case itemControllerNS::ItemType::machineGun:
		return itemControllerNS::GUN_MACHINEGUN_FRAME;
		break;
	case itemControllerNS::ItemType::shotGun:
		return itemControllerNS::GUN_SHOTGUN_FRAME;
		break;
	default:
		break;
	}
}
void ItemController::collisions() {

}
