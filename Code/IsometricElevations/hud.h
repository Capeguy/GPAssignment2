#ifndef _HUD_H            // Prevent multiple definitions if this 
#define _HUD_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "inventoryItem.h"
#include "gun.h"
#include "player.h"

namespace hudNS {
	const int GUN_HUD_WIDTH = 200;
	const int GUN_HUD_HEIGHT = 50;
	const int HP_HUD_WIDTH = 200;
	const int HP_HUD_HEIGHT = 30;
	const int HP_WIDTH = 170;
	const int HP_HEIGHT = 30;
}

class HUD
{
private:
	TextureManager* itemTexture;
	TextureManager* hpHUDTexture;
	TextureManager* gunHUDTexture;
	TextureManager* hpTexture;
	Image* currentItemImage;
	Image* hp;
	Image* hpHUD;
	Image* gunHud;
	Image* pointHud;
	TextDX* ammoFont;
	Item* currentItem;
	Player* currentPlayer;
	Graphics* graphics;

public:
	HUD(Graphics*& graphics);
	~HUD();
	void update(float frameTime, InventoryItem* const &item, Player* player);
	void draw();
};

#endif
