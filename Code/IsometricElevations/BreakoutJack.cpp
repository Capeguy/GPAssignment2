
#include "BreakoutJack.h"
using namespace std;
using namespace breakoutJackNS;

//=============================================================================
// Constructor
//=============================================================================
BreakoutJack::BreakoutJack() {}

//=============================================================================
// Destructor
//=============================================================================
BreakoutJack::~BreakoutJack() {
	releaseAll();           // call onLostDevice() for every graphics item
}
//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void BreakoutJack::initialize(HWND hwnd) {
	Game::initialize(hwnd);
	player = new Player();
	tileTexture = new TextureManager();
	// map textures
	if (!textures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures"));

	// object textures
	if (!textures2.initialize(graphics, TEXTURES2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures2"));
	//player texture
	playerTexture = new TextureManager();
	if (!playerTexture->initialize(graphics, TEXTURE_PLAYER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	// item texture
	if (!itemTexture.initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	if (!tileTexture->initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));
	//player image
	player->setColorFilter(graphicsNS::MAGENTA);
	player->initialize(this, playerNS::PLAYER_WIDTH, playerNS::PLAYER_HEIGHT, 32, playerTexture); // to change
	player->setFrames(952, 955);
	player->setCurrentFrame(952);
	player->setX(GAME_WIDTH / breakoutJackNS::TEXTURE_SIZE);
	player->setY((GAME_HEIGHT - GAME_HEIGHT / breakoutJackNS::TEXTURE_SIZE - 2 * breakoutJackNS::TEXTURE_SIZE) - 100);
	player->setVelocity(VECTOR2(playerNS::SPEED, playerNS::SPEED));
	// map tile image
	mapTile.initialize(graphics, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_COLS, &textures);
	mapTile.setFrames(0, 0);
	mapTile.setCurrentFrame(0);

	// crate image
	// if (!crate.initialize(this, &itemTexture))  // Fuck you isaac. You commented out the next line, making my dxFont to not initialize. - Ben
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing crate"));

	dxFont.initialize(graphics, 20, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	//Load level controller
	levelController = new LevelController(graphics, this, tileTexture);
	levelController->loadTiles(tileTexture, this);
	hud = new HUD(graphics);

}

//=============================================================================
// Update all game items
//=============================================================================
void BreakoutJack::update() {

	//mapTile.update(frameTime);
	levelController->update(frameTime);

	int playerBottomLeftX = player->getX();
	int playerBottomLeftY = player->getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerBottomRightX = player->getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerBottomRightY = player->getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerTopLeftX = player->getX();
	int playerTopLeftY = player->getY();
	int playerTopRightX = player->getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerTopRightY = player->getY();

	/*
	if (!tileIsSolid(playerBottomLeftX, playerBottomLeftY + 1) && !tileIsSolid(playerBottomRightX, playerBottomRightY + 1)) {
		player->canMoveDown = true;
	}
	else {
		player->canMoveDown = false;
	}

	if (!tileIsSolid(playerTopLeftX, playerTopLeftY - 1) && !tileIsSolid(playerTopRightX, playerTopRightY - 1)) {
		player->canMoveUp = true;
	}
	else {
		player->canMoveUp = false;
	}

	if (!tileIsSolid(playerBottomLeftX - 1, playerBottomLeftY) && !tileIsSolid(playerTopLeftX - 1, playerTopRightY)) {
		player->canMoveLeft = true;
	}
	else {
		player->canMoveLeft = false;
	}

	if (!tileIsSolid(playerTopLeftX + 1, playerTopLeftY) && !tileIsSolid(playerBottomRightX + 1, playerBottomRightY)) {
		player->canMoveRight = true;
	}
	else {
		player->canMoveRight = false;
	}
	*/
	crate.update(frameTime);
	player->update (frameTime, levelController);
	hud->update(frameTime, player->getInventory()->getActiveItem());
	crate.update(frameTime);
	player->update(frameTime, levelController);
}

bool BreakoutJack::tileIsSolid(int x, int y) {
	int tileX = (int)(floor((double)x / breakoutJackNS::TEXTURE_SIZE));
	int tileY = (int)(floor((double)y / breakoutJackNS::TEXTURE_SIZE));
	int tile = levelControllerNS::tileMap[tileY][tileX];
	if (levelControllerNS::tileSolid[tile][1] == 0) {
		return false;
	}
	return true;
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void BreakoutJack::ai() {}

//=============================================================================
// Handle collisions
//=============================================================================
void BreakoutJack::collisions() {
	VECTOR2 collisionVector;

	// Collision between player and crates
	/*
	ItemController* iController = levelController->getIController();
	list<Crate*>* crateList = iController->getCrateList();
	for (list<Crate*>::iterator it = crateList->begin(); it != crateList->end(); ++it) {
		if (player->collidesWith(*(*it), collisionVector)) {
			//c->spawnItem();
			//player.setX(playerNS::X * frameTime);
			//player.setVelocity(-collisionVector);
			//player.bounce(collisionVector, crate);

		}
	}
	*/
	levelController->collisions();
}

//=============================================================================
// Render game items
//=============================================================================
void BreakoutJack::render() {
	graphics->spriteBegin();
	levelController->render(graphics);
	player->draw();
	//print player position
	int playerBottomLeftX = player->getX();
	int playerBottomLeftY = player->getY() - 1 + playerNS::PLAYER_HEIGHT * 0.5;
	int playerBottomRightX = player->getX() - 1 + playerNS::PLAYER_WIDTH * 0.5;
	int playerBottomRightY = player->getY() - 1 + playerNS::PLAYER_HEIGHT * 0.5;
	int playerTopLeftX = player->getX();
	int playerTopLeftY = player->getY();
	int playerTopRightX = player->getX() - 1 + playerNS::PLAYER_WIDTH * 0.5;
	int playerTopRightY = player->getY();
	string text = "Player is at (" + to_string(player->getX()) + ", " + to_string(player->getY()) + ") Can Jump: " + to_string(player->canJump) + " | Can Fall: " + to_string(player->canFall) + " | Jumping: " + to_string(player->jumping) + " | Falling: " + to_string(player->falling) + "\n";
	text += "(" + to_string(playerTopLeftX) + ", " + to_string(playerTopLeftY) + ") ---- (" + to_string(playerTopRightX) + ", " + to_string(playerTopRightY) + ")" + "\n";
	text += "  |   ----   |  \n";
	text += "(" + to_string(playerBottomLeftX) + ", " + to_string(playerBottomLeftY) + ") ---- (" + to_string(playerBottomRightX) + ", " + to_string(playerBottomRightY) + ")";
	dxFont.print(text, 0, 0);
	crate.draw();
	hud->draw();
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void BreakoutJack::releaseAll() {
	textures.onLostDevice();
	itemTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void BreakoutJack::resetAll() {
	textures.onResetDevice();
	itemTexture.onResetDevice();
	Game::resetAll();
	return;
}
void BreakoutJack::consoleCommand() {
	command = console->getCommand();    // get command from console
	if (command == "")                   // if no command
		return;

	if (command == "help")              // if "help" command
	{
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		return;
	}

	if (command == "fps") {
		fpsOn = !fpsOn;                 // toggle display of fps
		if (fpsOn)
			console->print("fps On");
		else
			console->print("fps Off");
	} else if (command == "tile") {
		levelController->debugInfo = !levelController->debugInfo;
	} else if (command == "p") {
		int playerBottomLeftX = player->getX();
		int playerBottomLeftY = player->getY() + playerNS::PLAYER_HEIGHT * 0.5;
		int playerBottomRightX = player->getX() + playerNS::PLAYER_WIDTH * 0.5;
		int playerBottomRightY = player->getY() + playerNS::PLAYER_HEIGHT * 0.5;
		int playerTopLeftX = player->getX();
		int playerTopLeftY = player->getY();
		int playerTopRightX = player->getX() + playerNS::PLAYER_WIDTH;
		int playerTopRightY = player->getY();
		console->print("Player is at (" + to_string(player->getX()) + ", " + to_string(player->getY()) + ")");
		console->print("(" + to_string(playerTopLeftX) + ", " + to_string(playerTopLeftY) + ") ---- (" + to_string(playerTopRightX) + ", " + to_string(playerTopRightY) + ")");
		console->print("  |   ----   |  ");
		console->print("(" + to_string(playerBottomLeftX) + ", " + to_string(playerBottomLeftY) + ") ---- (" + to_string(playerBottomRightX) + ", " + to_string(playerBottomRightY) + ")");
	} else if (command == "mouse") {
		mouseOn = !mouseOn;                 // toggle display of fps
		if (mouseOn)
			console->print("mouse position On");
		else
			console->print("mouse position Off");
	}
}