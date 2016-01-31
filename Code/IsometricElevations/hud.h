#ifndef _HUD_H            // Prevent multiple definitions if this 
#define _HUD_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "inventoryItem.h"
#include "gun.h"

namespace hudNS
{

}

class HUD {
private:
	TextureManager* itemTexture;
	TextureManager* hpTexture;
	TextureManager* gunHUDTexture;
	Image* currentItemImage;
	Image* hp;
	Image* gunHud;
	TextDX* ammoFont;
	Item* currentItem;
	Graphics* graphics;
	COLOR_ARGB  backColor;              // background color (a,r,g,b)
	VertexC vtx[4];                     // vertex data for background
	LP_VERTEXBUFFER vertexBuffer;       // buffer to hold vertex data
	float x, y;
	
public:
	HUD(Graphics*& graphics);
	~HUD();
	void update(float frameTime, InventoryItem* const &item);
	void draw();

};

#endif
