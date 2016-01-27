#include "LevelController.h"

LevelController::LevelController()
{
}

LevelController::LevelController(Graphics*& graphics, Game* gp, TextureManager* tt)
{
	tileTexture = tt;
	gameptr = gp;

	dxFont.initialize(graphics, 12, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
}

LevelController::~LevelController()
{
}

Tile* LevelController::getTile(float x, float y) {
	int tileX = (int)(floor(x / levelControllerNS::TEXTURE_SIZE));
	int tileY = (int)(floor(y / levelControllerNS::TEXTURE_SIZE));
	return mapTile[tileY][tileX];
}
void LevelController::loadTiles(TextureManager* tt, Game* gameptr)
{
	for (int col = 0; col < MAP_SIZE_Y; col++)
	{
		for (int row = 0; row < MAP_SIZE_X; row++)
		{
			//Tile* t = new Tile(118, 1);
			Tile* t = new Tile(levelControllerNS::tileMap[col][row], levelControllerNS::tileSolid[tileMap[col][row]][1]);
			mapTile[col][row] = t;
			mapTile[col][row]->initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tt);
			mapTile[col][row]->spriteData.height = 32;
			mapTile[col][row]->spriteData.width = 32;
			mapTile[col][row]->setCurrentFrame(tileMap[col][row]);
			mapTile[col][row]->setX(row * TEXTURE2_SIZE);
			mapTile[col][row]->setY(col * TEXTURE2_SIZE);
			//mapTile[col][row]->draw();
		}
	}

}
void LevelController::draw(Graphics* graphics) {
	renderTiles(graphics);
}

void LevelController :: renderTiles(Graphics* graphics) {
	string buffer;
	for (int col = 0; col < MAP_SIZE_Y; col++)
	{
		for (int row = 0; row < MAP_SIZE_X; row++)
		{
			mapTile[col][row]->draw();
			buffer = "";
			buffer += to_string(mapTile[col][row]->getId());
			buffer += ":";
			buffer += to_string(mapTile[col][row]->isSolid());
			dxFont.print(buffer, row * levelControllerNS::TEXTURE2_SIZE, col * levelControllerNS::TEXTURE2_SIZE);
			buffer = "(" + to_string(row);
			buffer += "," + to_string(col);
			buffer += ")";
			dxFont.print(buffer, row * levelControllerNS::TEXTURE2_SIZE, col * levelControllerNS::TEXTURE2_SIZE + 14);

		}
	}
}

void LevelController::update(float frameTime) {
	for (int col = 0; col < MAP_SIZE_Y; col++)
	{
		for (int row = 0; row < MAP_SIZE_X; row++)
		{
			mapTile[col][row]->update(frameTime);
		}
	}
}
