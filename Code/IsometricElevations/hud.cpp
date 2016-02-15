//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "hud.h"

HUD::HUD(Graphics*& g) {
	graphics = g;
	itemTexture = new TextureManager();
	gunHUDTexture = new TextureManager();
	hpHUDTexture = new TextureManager();
	hpTexture = new TextureManager();

	//Load and set up hp HUD texture
	if (!hpHUDTexture->initialize(graphics, TEXTURE_HUD_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp hud texture"));
	hpHUD = new Image();
	hpHUD->initialize(graphics, hudNS::HP_HUD_WIDTH, hudNS::HP_HUD_HEIGHT, 1, hpHUDTexture);
	hpHUD->setCurrentFrame(0);
	hpHUD->setX(50);
	hpHUD->setY(60);
	if (!hpTexture->initialize(graphics, TEXTURE_HUD_HP_RED))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp texture"));
	hp = new Image();
	hp->initialize(graphics, hudNS::HP_WIDTH, hudNS::HP_HEIGHT, 1, hpTexture);
	hp->setCurrentFrame(0);
	hp->setX(hpHUD->getX() + 30);
	hp->setY(hpHUD->getY());

	//Load and set up gun HUD texture
	if (!gunHUDTexture->initialize(graphics, TEXTURE_HUD_GUN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun hud texture"));
	gunHud = new Image();
	gunHud->initialize(graphics, hudNS::GUN_HUD_WIDTH, hudNS::GUN_HUD_HEIGHT, 1, gunHUDTexture);
	gunHud->setCurrentFrame(0);
	gunHud->setX(hpHUD->getX() + hpHUD->getWidth() + 50);
	gunHud->setY(50);

	//Load and set up item HUD texture
	if (!itemTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	currentItemImage = new Image();
	currentItemImage->initialize(graphics, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, itemTexture);
	currentItemImage->setX(gunHud->getX());
	currentItemImage->setY(gunHud->getY() + 10);
	currentItemImage->setScale(0.8);

	//Load and set up Points HUD texture
	pointHud = new Image();
	pointHud->initialize(graphics, hudNS::GUN_HUD_WIDTH, hudNS::GUN_HUD_HEIGHT, 1, gunHUDTexture);
	pointHud->setCurrentFrame(0);
	pointHud->setX(gunHud->getX() + gunHud->getWidth() + 50);
	pointHud->setY(50);

	//set up font 
	ammoFont = new TextDX();
	ammoFont->initialize(graphics, 20, false, false, "Courier New");
	ammoFont->setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	currentItem = nullptr;
	currentPlayer = nullptr;
}

HUD::~HUD() {
	SAFE_DELETE(itemTexture);
	SAFE_DELETE(hpHUDTexture);
	SAFE_DELETE(gunHUDTexture);
	SAFE_DELETE(currentItemImage);
	SAFE_DELETE(hpHUD);
	SAFE_DELETE(gunHud);
	SAFE_DELETE(ammoFont);
	SAFE_DELETE(currentItem);
	SAFE_DELETE(pointHud);
}

void HUD::update(float frameTime, InventoryItem* const &item, Player* player) {
	currentItem = item->getItem();
	currentPlayer = player;
	Gun* gun = dynamic_cast<Gun*>(currentItem);
	if (gun != 0) {
		if (gun->getGunId() == Gun::ItemType::pistol) {
			currentItemImage->setCurrentFrame(gunNS::PISTOL_FRAME);
		} else if (gun->getGunId() == Gun::ItemType::machineGun) {
			currentItemImage->setCurrentFrame(gunNS::MACHINEGUN_FRAME);
		} else if (gun->getGunId() == Gun::ItemType::shotGun) {
			currentItemImage->setCurrentFrame(gunNS::SHOTGUN_FRAME);
		} else { // For testing purposes
			currentItemImage->setCurrentFrame(10);
		}
	}
	RECT r = hp->getSpriteDataRect();
	//percentage of player hp / width of image
	r.right = player->getHealth() / player->getMaxHP() * hp->getWidth();
	hp->setSpriteDataRect(r);
	currentItemImage->update(frameTime);
	gunHud->update(frameTime);
	hpHUD->update(frameTime);
	hp->update(frameTime);
	pointHud->update(frameTime);
}

void HUD::draw() {
	gunHud->draw();
	currentItemImage->draw();
	hpHUD->draw();
	hp->draw();
	pointHud->draw();
	if (currentItem != nullptr && currentItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)currentItem;
		ammoFont->print("X (" + gun->getAmmoDisplay() + ") ", currentItemImage->getX() + 100, currentItemImage->getY() + 8);
	}
	if (currentPlayer != nullptr) {
		ammoFont->print("Carnage: " + std::to_string(currentPlayer->getTotalPoints()), pointHud->getX() + 20, pointHud->getY() + 15);
	}
}
