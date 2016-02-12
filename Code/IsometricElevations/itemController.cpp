#include "itemController.h"

ItemController::ItemController() {}

ItemController::ItemController(Graphics *graphics, TextureManager* iTxt) {
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = new std::list<Crate*>();
	itemList = std::vector<Item*>();
	//init crate location first
	levelCrateLoc[0] = new std::list<VECTOR2>();
	levelCrateLoc[0]->push_back(VECTOR2(321, 568));		// crate 1.1
	levelCrateLoc[0]->push_back(VECTOR2(1152, 250));	// crate 2.1
	
	levelCrateLoc[0]->push_back(VECTOR2(2447, 250));	//crate 2.5.1
	levelCrateLoc[0]->push_back(VECTOR2(2688, 668));	// crate 3.1 
	levelCrateLoc[0]->push_back(VECTOR2(2815, 602));	// crate 3.2

	
	//init crate item second
	levelCrateItemType[0] = new std::list<int>();
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);	// crate 1.1
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);		// crate 2.1
	
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);	// craet 2.5.1
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::machineGun);	// crate 3.1
	levelCrateItemType[0]->push_back(itemControllerNS::ItemType::shotGun);		// crate 3.2
	
	itemIconTexture = iTxt;
	

	gunTexture = new TextureManager();
	if (!gunTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	gunImage = new Image();
	gunImage->initialize(graphics, itemControllerNS::GUN_TEXTURE_WIDTH, itemControllerNS::GUN_TEXTURE_HEIGHT, 1, gunTexture);
	//gunImage->setCurrentFrame(0);

	if (!gunTexture->initialize(graphics, ITEMICON_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item icon texture"));
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

				//Create Crate Icon
				Image* itemIco = new Image();
				itemIco->initialize(graphics, itemControllerNS::ICO_TEXTURE_SIZE, itemControllerNS::ICO_TEXTURE_SIZE, 5, itemIconTexture);
				itemIco->setCurrentFrame(1);
				itemIco->setScale(0.5);
				itemIco->setX(GAME_WIDTH*0.6);
				itemIco->setY(50);
				crateIcons.push_back(itemIco);
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

void ItemController::update(float frameTime, float mapX) {
	int crateCount = 0;
	for (std::list<Crate*>::iterator crateIter = crateList->begin(); crateIter != crateList->end(); ++crateIter) {
		(*crateIter)->update(frameTime);
		int crateIconCount = 0;
		for (std::list<Image*>::iterator crateIcoIter = crateIcons.begin(); crateIcoIter != crateIcons.end(); ++crateIcoIter) {
			if (crateCount == crateIconCount)
			{
				float testX = ((*crateIter)->getX()*0.120) + (GAME_WIDTH*0.60 + 5) + (-mapX*0.125);
				float testY = (*crateIter)->getY()*0.120 + 42;
				(*crateIcoIter)->setX(((*crateIter)->getX()*0.120) + (GAME_WIDTH*0.60 + 5) + (-mapX*0.125));
				(*crateIcoIter)->setY((*crateIter)->getY()*0.120 + 42);
			}
			crateIconCount++;
		}
		crateCount++;
	}
}

void ItemController::render(float mapX) {
	int crateCount = 0;
	std::list<VECTOR2> *crateLocations = levelCrateLoc[0];
	//std::list<VECTOR2>::iterator l_front = crateLocations->begin();
	for (std::list<Crate*>::iterator crateIter = crateList->begin(); crateIter != crateList->end(); ++crateIter) {
		int crateLocCount = 0;
		for (std::list<VECTOR2>::iterator crateLocationIter = crateLocations->begin(); crateLocationIter != crateLocations->end(); ++crateLocationIter) {
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
	for (std::list<Image*>::iterator itr = crateIcons.begin(); itr != crateIcons.end(); ++itr) {
		(*itr)->draw();
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
