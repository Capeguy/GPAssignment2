#include "itemController.h"

ItemController::ItemController() {}

ItemController::ItemController(Graphics *graphics) {
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = new std::list<Crate*>();
	itemList = std::vector<Item*>();
	//init crate location first
	levelCrateLoc[0] = new std::list<VECTOR2>();
	levelCrateLoc[0]->push_back(VECTOR2(321, 568));
	levelCrateLoc[0]->push_back(VECTOR2(1152, 250));
	/*
	levelCrateLoc[0]->push_back(VECTOR2(2462, 256));
	levelCrateLoc[0]->push_back(VECTOR2(2815, 608));
	levelCrateLoc[0]->push_back(VECTOR2(2758, 608));
	*/
	//init crate item second
	levelCrateItemType[0] = new std::list<int>();
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);
	/*
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);
	*/
	

	gunTexture = new TextureManager();
	if (!gunTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	gunImage = new Image();
	gunImage->initialize(graphics, itemControllerNS::GUN_TEXTURE_WIDTH, itemControllerNS::GUN_TEXTURE_HEIGHT, 1, gunTexture);
	//gunImage->setCurrentFrame(0);
}

ItemController::~ItemController() {}

void ItemController::spawnCrates(int level, Game *gamePtr) {
	std::list<VECTOR2>* crateLocations = levelCrateLoc[0];
	int locCounter = 0;
	for (std::list<VECTOR2>::iterator crateLocationIter = crateLocations->begin(); crateLocationIter != crateLocations->end(); ++crateLocationIter) {
		locCounter++;
		int itemCounter = 0;
		std::list<int>* crateItem = levelCrateItemType[0];
		for (std::list<int>::iterator crateItemTypeIter = crateItem->begin(); crateItemTypeIter!= crateItem->end(); ++crateItemTypeIter) {
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

std::list<VECTOR2>* ItemController::getCrateLoc()
{
	return levelCrateLoc[0];
}

void ItemController::update(float frameTime) {
	for (std::list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		(*it)->update(frameTime);
	}
}

void ItemController::render(float mapX) {
	int crateCount = 0;
	std::list<VECTOR2> *crateLocations = levelCrateLoc[0];
	//std::list<VECTOR2>::iterator l_front = crateLocations->begin();
	for (std::list<Crate*>::iterator crateIter = crateList->begin(); crateIter != crateList->end(); ++crateIter) {
		int crateLocCount = 0;
		for (std::list<VECTOR2>::iterator crateLocationIter = crateLocations->begin(); crateLocationIter != crateLocations->end(); ++crateLocationIter) {
			// do shit
			if (crateCount == crateLocCount) {
				(*crateIter)->setX(float((*crateLocationIter).x + mapX));
				(*crateIter)->draw();
				int itemid = (*crateIter)->getItemId();
				gunImage->setCurrentFrame(getGunFrameByItemType(itemid));
				gunImage->setX((*crateIter)->getX());
				gunImage->setY((*crateIter)->getY() + 18);
				gunImage->setScale(0.3);
				gunImage->draw();
			}
			crateLocCount++;
		}
		crateCount++;
	}
}

std::list<Crate*>* ItemController::getCrateList() {
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
