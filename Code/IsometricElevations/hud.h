#ifndef _HUD_H            // Prevent multiple definitions if this 
#define _HUD_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "inventoryItem.h"

namespace hudNS
{

}

class HUD {
private:
	TextureManager* itemTexture;
	TextureManager* hpTexture;
	TextureManager* gunHUDTexture;
	Image* currentItem;
	Image* hp;
	Image* gunHud;
	TextDX* ammoFont;
	
public:
	HUD(Graphics*& graphics);
	~HUD();
	void update(float frameTime, InventoryItem* const &item);
	void draw();

};

#endif
