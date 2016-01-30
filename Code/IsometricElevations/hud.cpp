#include "hud.h"

HUD::HUD(Graphics*& graphics)
{
	itemTexture = new TextureManager();
	gunHUDTexture = new TextureManager();
	if(!gunHUDTexture->initialize(graphics, TEXTURE_HUD_GUN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun hud texture"));
	gunHud = new Image();
	gunHud->initialize(graphics, 200, 50, 1, gunHUDTexture);
	gunHud->setCurrentFrame(0);
	gunHud->setX(GAME_WIDTH / 2);
	gunHud->setY(50);
	if(!itemTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	currentItem = new Image();
	currentItem->initialize(graphics, 136, 41, 2, itemTexture);
	currentItem->setX(gunHud->getX());
	currentItem->setY(gunHud->getY() + 10);
	currentItem->setScale(0.8);
	ammoFont = new TextDX();
	ammoFont->initialize(graphics, 20, false, false, "Courier New");
	ammoFont->setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));


}

HUD::~HUD()
{
	SAFE_DELETE(currentItem);
	SAFE_DELETE(itemTexture);
	SAFE_DELETE(ammoFont);
}

void HUD::update(float frameTime, InventoryItem* const &item)
{
	string itemName = item->getItem()->getItemName();
	if (itemName == "pistol")
	{
		currentItem->setCurrentFrame(8);
	}
	else if(itemName == "shotgun")
	{
		currentItem->setCurrentFrame(6);
	}
	else if (itemName == "machineGun")
	{
		currentItem->setCurrentFrame(0);
	}
	else // to be taken out, for testing purposes
	{
		currentItem->setCurrentFrame(10);
	}
	currentItem->update(frameTime);
	gunHud->update(frameTime);
	
}

void HUD::draw()
{
	gunHud->draw();
	currentItem->draw();
	ammoFont->print("X (Some number) ", currentItem->getX() + 100, currentItem->getY() + 8);
}
