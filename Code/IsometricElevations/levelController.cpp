#include "LevelController.h"

LevelController::LevelController()
{
}

LevelController::LevelController(Graphics* graphics, Game* gp)
{
	tileTexture = new TextureManager();
	if (!tileTexture->initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));
	gameptr = gp;
	//mapTile = std::vector<Tile>();
}

LevelController::~LevelController()
{
}

void LevelController::loadTiles()
{
	for (int row = 0; row<MAP_SIZE_X; row++)
	{
		for (int col = 0; col < MAP_SIZE_Y; col++)
		{
			Tile t = Tile(tileMap[col][row], tileSolid[row*col][2]);
			mapTile[col][row] = t;
			mapTile[col][row].initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tileTexture);
			mapTile[col][row].setCurrentFrame(tileMap[col][row]);
			mapTile[col][row].setX(row * TEXTURE2_SIZE);
			mapTile[col][row].setY(col * TEXTURE2_SIZE);
			//mapTile[col][row]->draw();
		}
	}

}
void LevelController :: renderTiles() {
	for (int row = 0; row<MAP_SIZE_X; row++)
	{
		for (int col = 0; col < MAP_SIZE_Y; col++)
		{
			mapTile[col][row].draw();
		}
	}
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
