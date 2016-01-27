
#include "BreakoutJack.h"
using namespace std;
using namespace breakoutJackNS;

//=============================================================================
// Constructor
//=============================================================================
BreakoutJack::BreakoutJack()
{}

//=============================================================================
// Destructor
//=============================================================================
BreakoutJack::~BreakoutJack()
{
    releaseAll();           // call onLostDevice() for every graphics item
}
//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void BreakoutJack::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
	tileTexture = new TextureManager();
    // map textures
    if (!textures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures"));

    // object textures
    if (!textures2.initialize(graphics,TEXTURES2_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures2"));
	//player texture
	if (!playerTexture.initialize(graphics, TEXTURE_PLAYER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	// item texture
	if (!itemTexture.initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	if (!tileTexture->initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));
	/*
	if(!gunTexture.initialize(graphics, TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	*/
	//player image
	player.setColorFilter(graphicsNS::MAGENTA);
	player.initialize(this, playerNS::PLAYER_WIDTH, playerNS::PLAYER_HEIGHT, 32, &playerTexture); // to change
	player.setFrames(952, 955);
	player.setCurrentFrame(952);
	player.setX(GAME_WIDTH / breakoutJackNS::TEXTURE_SIZE);
	player.setY(GAME_HEIGHT - GAME_HEIGHT / breakoutJackNS::TEXTURE_SIZE - 2 * breakoutJackNS::TEXTURE_SIZE);
	player.setVelocity(VECTOR2(playerNS::SPEED, playerNS::SPEED));
    // map tile image
    mapTile.initialize(graphics, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_COLS,&textures);
    mapTile.setFrames(0, 0);
    mapTile.setCurrentFrame(0);

    //// Tree image
    tree.initialize(graphics, breakoutJackNS::TEXTURE2_SIZE, breakoutJackNS::TEXTURE2_SIZE, breakoutJackNS::TEXTURE2_COLS,&textures2);
    tree.setFrames(TREE0_FRAME, TREE0_FRAME);
    tree.setCurrentFrame(TREE0_FRAME);
	
	// crate image
	if (!crate.initialize(this, crateNS::WIDTH, crateNS::HEIGHT, 2, &itemTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing crate"));

	dxFont.initialize(graphics, 20, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	//Load level controller
	levelController = new LevelController(graphics, this, tileTexture);
	levelController->loadTiles(tileTexture, this);

	//Test machine gun image
	/*
	machineGun.initialize(this, 136, 41, 2, &gunTexture);
	machineGun.setCurrentFrame(1);
	machineGun.setX(player.getX());
	machineGun.setY(player.getY());
	*/
}

//=============================================================================
// Update all game items
//=============================================================================
void BreakoutJack::update()
{

    //mapTile.update(frameTime);
	levelController->update(frameTime);
	
	int playerBottomLeftX = player.getX();
	int playerBottomLeftY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerBottomRightX = player.getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerBottomRightY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerTopLeftX = player.getX();
	int playerTopLeftY = player.getY();
	int playerTopRightX = player.getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerTopRightY = player.getY();

	/*
	if (!tileIsSolid(playerBottomLeftX, playerBottomLeftY + 1) && !tileIsSolid(playerBottomRightX, playerBottomRightY + 1)) {
		player.canMoveDown = true;
	}
	else {
		player.canMoveDown = false;
	}
	
	if (!tileIsSolid(playerTopLeftX, playerTopLeftY - 1) && !tileIsSolid(playerTopRightX, playerTopRightY - 1)) {
		player.canMoveUp = true;
	}
	else {
		player.canMoveUp = false;
	}
	
	if (!tileIsSolid(playerBottomLeftX - 1, playerBottomLeftY) && !tileIsSolid(playerTopLeftX - 1, playerTopRightY)) {
		player.canMoveLeft = true;
	}
	else {
		player.canMoveLeft = false;
	}
	
	if (!tileIsSolid(playerTopLeftX + 1, playerTopLeftY) && !tileIsSolid(playerBottomRightX + 1, playerBottomRightY)) {
		player.canMoveRight = true;
	}
	else {
		player.canMoveRight = false;
	}
	*/
	crate.update(frameTime);
	//machineGun.update(frameTime);
	player.update(frameTime);
}

bool BreakoutJack::tileIsSolid(int x, int y) {
	int tileX = (int)(floor((double)x / breakoutJackNS::TEXTURE_SIZE));
	int tileY = (int)(floor((double)y / breakoutJackNS::TEXTURE_SIZE));
	int tile = breakoutJackNS::tileMap[tileY][tileX];
	if (breakoutJackNS::tileSolid[tile][1] == 0) {
		return false;
	}
	return true;
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void BreakoutJack::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void BreakoutJack::collisions()
{
	VECTOR2 collisionVector;
	// collision between player and crate
	if (player.collidesWith(crate, collisionVector))
	{
		player.bounce(collisionVector, crate);
		//crate.setX(60.0);
		//crate.setY(60.0);
	}
}

//=============================================================================
// Render game items
//=============================================================================
void BreakoutJack::render()
{
    graphics->spriteBegin();
	player.draw();
	
	string buffer;
    // Draw map in Isometric Diamond
	/*
    for(int row=0; row<levelControllerNS::MAP_SIZE_X; row++)
    {
		for (int col = 0; col < levelControllerNS::MAP_SIZE_Y; col++)
        {
            mapTile.setCurrentFrame(levelControllerNS::tileMap[col][row]);
			mapTile.setX(row * levelControllerNS::TEXTURE2_SIZE);
			mapTile.setY(col * levelControllerNS::TEXTURE2_SIZE);
            mapTile.draw();
			player.setColorFilter(graphicsNS::MAGENTA);
			player.draw();
			if (drawTileNo) {
				buffer = "";
				buffer += to_string(levelControllerNS::tileMap[col][row]);
				buffer += ":";
				buffer += to_string(levelControllerNS::tileSolid[levelControllerNS::tileMap[col][row]][1]);
				//dxFont.print(buffer, row * levelControllerNS::TEXTURE2_SIZE, col * levelControllerNS::TEXTURE2_SIZE);
			}
        }
    }
	*/
	levelController->renderTiles(graphics);
	//machineGun.draw();
	//print player position
	int playerBottomLeftX = player.getX();
	int playerBottomLeftY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerBottomRightX = player.getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerBottomRightY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
	int playerTopLeftX = player.getX();
	int playerTopLeftY = player.getY();
	int playerTopRightX = player.getX() + playerNS::PLAYER_WIDTH * 0.5;
	int playerTopRightY = player.getY();
	string text = "Player is at (" + to_string(player.getX()) + ", " + to_string(player.getY()) + ")" + "\n";
	text += "(" + to_string(playerTopLeftX) + ", " + to_string(playerTopLeftY) + ") ---- (" + to_string(playerTopRightX) + ", " + to_string(playerTopRightY) + ")" + "\n";
	text += "  |   ----   |  \n";
	text += "(" + to_string(playerBottomLeftX) + ", " + to_string(playerBottomLeftY) + ") ---- (" + to_string(playerBottomRightX) + ", " + to_string(playerBottomRightY) + ")";
	dxFont.print(text, 0, 0);
	crate.draw();
    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void BreakoutJack::releaseAll()
{
    textures.onLostDevice();
	itemTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void BreakoutJack::resetAll()
{
    textures.onResetDevice();
	itemTexture.onResetDevice();
    Game::resetAll();
    return;
}
void BreakoutJack::consoleCommand()
{
	command = console->getCommand();    // get command from console
	if (command == "")                   // if no command
		return;

	if (command == "help")              // if "help" command
	{
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		return;
	}

	if (command == "fps")
	{
		fpsOn = !fpsOn;                 // toggle display of fps
		if (fpsOn)
			console->print("fps On");
		else
			console->print("fps Off");
	}
	else if (command == "tile") {
		drawTileNo = !drawTileNo;
	}
	else if (command == "p") {
		int playerBottomLeftX = player.getX();
		int playerBottomLeftY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
		int playerBottomRightX = player.getX() + playerNS::PLAYER_WIDTH * 0.5;
		int playerBottomRightY = player.getY() + playerNS::PLAYER_HEIGHT * 0.5;
		int playerTopLeftX = player.getX();
		int playerTopLeftY = player.getY();
		int playerTopRightX = player.getX() + playerNS::PLAYER_WIDTH;
		int playerTopRightY = player.getY();
		console->print("Player is at (" + to_string(player.getX()) + ", " + to_string(player.getY()) + ")");
		console->print("(" + to_string(playerTopLeftX) + ", " + to_string(playerTopLeftY) + ") ---- (" + to_string(playerTopRightX) + ", " + to_string(playerTopRightY) + ")");
		console->print("  |   ----   |  ");
		console->print("(" + to_string(playerBottomLeftX) + ", " + to_string(playerBottomLeftY) + ") ---- (" + to_string(playerBottomRightX) + ", " + to_string(playerBottomRightY) + ")");
	}
	else if (command == "mouse") {
		mouseOn = !mouseOn;                 // toggle display of fps
		if (mouseOn)
			console->print("mouse position On");
		else
			console->print("mouse position Off");
	}
}