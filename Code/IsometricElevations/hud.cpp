#include "hud.h"

HUD::HUD(Graphics*& g) {
	graphics = g;
	itemTexture = new TextureManager();
	gunHUDTexture = new TextureManager();
	hpHUDTexture = new TextureManager();
	hpTexture = new TextureManager();
	//Load and set up gun HUD texture
	if (!gunHUDTexture->initialize(graphics, TEXTURE_HUD_GUN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun hud texture"));
	gunHud = new Image();
	gunHud->initialize(graphics, hudNS::GUN_HUD_WIDTH, hudNS::GUN_HUD_HEIGHT, 1, gunHUDTexture);
	gunHud->setCurrentFrame(0);
	gunHud->setX(GAME_WIDTH / 2);
	gunHud->setY(50);
	//Load and set up item HUD texture
	if (!itemTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	currentItemImage = new Image();
	currentItemImage->initialize(graphics, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, itemTexture);
	currentItemImage->setX(gunHud->getX());
	currentItemImage->setY(gunHud->getY() + 10);
	currentItemImage->setScale(0.8);
	//Load and set up hp HUD texture
	if(!hpHUDTexture->initialize(graphics, TEXTURE_HUD_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp hud texture"));
	hpHUD = new Image();
	hpHUD->initialize(graphics, hudNS::HP_HUD_WIDTH, hudNS::HP_HUD_HEIGHT, 1, hpHUDTexture);
	hpHUD->setCurrentFrame(0);
	hpHUD->setX(GAME_WIDTH / 2 - 200);
	hpHUD->setY(50);
	if (!hpTexture->initialize(graphics, TEXTURE_HUD_HP_RED))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp texture"));
	hp = new Image();
	hp->initialize(graphics, hudNS::HP_WIDTH, hudNS::HP_HEIGHT, 1, hpTexture);
	hp->setCurrentFrame(0);
	hp->setX(hpHUD->getX() + 30);
	hp->setY(hpHUD->getY());
	//set up font 
	ammoFont = new TextDX();
	ammoFont->initialize(graphics, 20, false, false, "Courier New");
	ammoFont->setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	currentItem = nullptr;
}

HUD::~HUD()
{
	SAFE_DELETE(itemTexture);
	SAFE_DELETE(hpHUDTexture);
	SAFE_DELETE(gunHUDTexture);
	SAFE_DELETE(currentItemImage);
	SAFE_DELETE(hpHUD);
	SAFE_DELETE(gunHud);
	SAFE_DELETE(ammoFont);
	SAFE_DELETE(currentItem);
}

void HUD::update(float frameTime, InventoryItem* const &item, Player* player)
{
	currentItem = item->getItem();
	Gun* gun = dynamic_cast<Gun*>(currentItem);
	if (gun != 0)
	{
		if (gun->getGunId() == Gun::ItemType::pistol)
		{
			currentItemImage->setCurrentFrame(gunNS::PISTOL_FRAME);
		}
		else if (gun->getGunId() == Gun::ItemType::machineGun)
		{
			currentItemImage->setCurrentFrame(gunNS::MACHINEGUN_FRAME);
		}
		else if (gun->getGunId() == Gun::ItemType::shotGun)
		{
			currentItemImage->setCurrentFrame(gunNS::SHOTGUN_FRAME);
		}
		else // to be taken out, for testing purposes
		{
			currentItemImage->setCurrentFrame(10);
		}
	}
	
	RECT r = hp->getSpriteDataRect();
	//percentage of player hp / width of image
	r.right = player->getHP() / player->getMaxHP() * hp->getWidth();
	hp->setSpriteDataRect(r);
	currentItemImage->update(frameTime);
	gunHud->update(frameTime);
	hpHUD->update(frameTime);
	hp->update(frameTime);
}

void HUD::draw()
{
	
	gunHud->draw();
	currentItemImage->draw();
	hpHUD->draw();
	hp->draw();
	if (currentItem != nullptr && currentItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)currentItem;
		ammoFont->print("X (" + gun->getAmmoDisplay() + ") ", currentItemImage->getX() + 100, currentItemImage->getY() + 8);
	}
}
