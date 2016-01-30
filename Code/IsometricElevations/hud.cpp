#include "hud.h"

HUD::HUD(Graphics*& graphics) {
	itemTexture = new TextureManager();
	gunHUDTexture = new TextureManager();
	if (!gunHUDTexture->initialize(graphics, TEXTURE_HUD_GUN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun hud texture"));
	gunHud = new Image();
	gunHud->initialize(graphics, 200, 50, 1, gunHUDTexture);
	gunHud->setCurrentFrame(0);
	gunHud->setX(GAME_WIDTH / 2);
	gunHud->setY(50);
	if (!itemTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	currentItemImage = new Image();
	currentItemImage->initialize(graphics, 136, 41, 2, itemTexture);
	currentItemImage->setX(gunHud->getX());
	currentItemImage->setY(gunHud->getY() + 10);
	currentItemImage->setScale(0.8);
	ammoFont = new TextDX();
	ammoFont->initialize(graphics, 20, false, false, "Courier New");
	ammoFont->setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	currentItem = nullptr;
}

HUD::~HUD()
{
	SAFE_DELETE(currentItemImage);
	SAFE_DELETE(itemTexture);
	SAFE_DELETE(ammoFont);
}

void HUD::update(float frameTime, InventoryItem* const &item)
{
	currentItem = item->getItem();
	string itemName = item->getItem()->getItemName();
	if (itemName == "pistol")
	{
		currentItemImage->setCurrentFrame(8);
	}
	else if(itemName == "shotgun")
	{
		currentItemImage->setCurrentFrame(6);
	}
	else if (itemName == "machineGun")
	{
		currentItemImage->setCurrentFrame(0);
	}
	else // to be taken out, for testing purposes
	{
		currentItemImage->setCurrentFrame(10);
	}
	currentItemImage->update(frameTime);
	gunHud->update(frameTime);
	
}

void HUD::draw()
{
	gunHud->draw();
	currentItemImage->draw();
	if (currentItem != nullptr && currentItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)currentItem;
		ammoFont->print("X (" + gun->getAmmoDisplay() + ") ", currentItemImage->getX() + 100, currentItemImage->getY() + 8);
	}
	
}
