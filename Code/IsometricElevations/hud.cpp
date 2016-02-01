#include "hud.h"

HUD::HUD(Graphics*& g) {
	graphics = g;
	itemTexture = new TextureManager();
	gunHUDTexture = new TextureManager();
	hpTexture = new TextureManager();
	//Load and set up gun HUD texture
	if (!gunHUDTexture->initialize(graphics, TEXTURE_HUD_GUN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun hud texture"));
	gunHud = new Image();
	gunHud->initialize(graphics, 200, 50, 1, gunHUDTexture);
	gunHud->setCurrentFrame(0);
	gunHud->setX(GAME_WIDTH / 2);
	gunHud->setY(50);
	//Load and set up item HUD texture
	if (!itemTexture->initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	currentItemImage = new Image();
	currentItemImage->initialize(graphics, 136, 41, 2, itemTexture);
	currentItemImage->setX(gunHud->getX());
	currentItemImage->setY(gunHud->getY() + 10);
	currentItemImage->setScale(0.8);
	//Load and set up hp HUD texture
	if(!hpTexture->initialize(graphics, TEXTURE_HUD_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp hud texture"));
	hp = new Image();
	hp->initialize(graphics, 200, 30, 1, hpTexture);
	hp->setCurrentFrame(0);
	hp->setX(GAME_WIDTH / 2 - 200);
	hp->setY(50);
	//set up font 
	ammoFont = new TextDX();
	ammoFont->initialize(graphics, 20, false, false, "Courier New");
	ammoFont->setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	currentItem = nullptr;

	//set up hp bar
	backColor = graphicsNS::RED;
	vertexBuffer = NULL;
	x = 0;
	y = 0;
	vtx[0].x = x;
	vtx[0].y = y;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = backColor;

	// top right
	vtx[1].x = x + consoleNS::WIDTH;
	vtx[1].y = y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = backColor;

	// bottom right
	vtx[2].x = x + consoleNS::WIDTH;
	vtx[2].y = y + consoleNS::HEIGHT;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = backColor;

	// bottom left
	vtx[3].x = x;
	vtx[3].y = y + consoleNS::HEIGHT;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = backColor;

	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
}

HUD::~HUD()
{
	SAFE_DELETE(itemTexture);
	SAFE_DELETE(hpTexture);
	SAFE_DELETE(gunHUDTexture);
	SAFE_DELETE(currentItemImage);
	SAFE_DELETE(hp);
	SAFE_DELETE(gunHud);
	SAFE_DELETE(ammoFont);
	SAFE_DELETE(currentItem);
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
	hp->update(frameTime);
	
}

void HUD::draw()
{
	
	gunHud->draw();
	currentItemImage->draw();
	hp->draw();
	if (currentItem != nullptr && currentItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)currentItem;
		ammoFont->print("X (" + gun->getAmmoDisplay() + ") ", currentItemImage->getX() + 100, currentItemImage->getY() + 8);
	}
	graphics->drawQuad(vertexBuffer);
	
}
