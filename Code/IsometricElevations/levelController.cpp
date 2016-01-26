#include "LevelController.h"

LevelController::LevelController()
{
}

LevelController::LevelController(Graphics*& graphics, Game* gp, TextureManager*& tt)
{
	tileTexture = tt;
	gameptr = gp;
	//mapTile = std::vector<Tile>();
}

LevelController::~LevelController()
{
}

void LevelController::loadTiles(TextureManager*& tt, Game* gameptr)
{
	for (int row = 0; row<MAP_SIZE_X; row++)
	{
		for (int col = 0; col < MAP_SIZE_Y; col++)
		{
			Tile t = Tile(tileMap[col][row], tileSolid[row*col][2]);
			mapTile[col][row] = t;
			mapTile[col][row].initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tt);
			mapTile[col][row].setCurrentFrame(tileMap[col][row]);
			mapTile[col][row].setX(row * TEXTURE2_SIZE);
			mapTile[col][row].setY(col * TEXTURE2_SIZE);
			//mapTile[col][row]->draw();
		}
	}

}
void LevelController :: renderTiles(Graphics*& graphics) {
	
	for (int row = 0; row<MAP_SIZE_X; row++)
	{
		for (int col = 0; col < MAP_SIZE_Y; col++)
		{
			mapTile[col][row].draw();
		}
	}
	string text = "This is sample text";
	dxFont.print(text, 200, 0);
}

void LevelController::update(float frameTime) {
	for (int row = 0; row<MAP_SIZE_X; row++)
	{
		for (int col = 0; col < MAP_SIZE_Y; col++)
		{
			mapTile[col][row].update(frameTime);
		}
	}
}
