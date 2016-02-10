
#include "BreakoutJack.h"
using namespace std;
using namespace breakoutJackNS;

//=============================================================================
// Constructor
//=============================================================================
BreakoutJack::BreakoutJack() {

}

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
	menuTexture = new TextureManager();
	buttonTexture = new TextureManager();
	playerTexture = new TextureManager();
	pauseMenuTexture = new TextureManager();
	pauseMenuButtonTexture = new TextureManager();
	creditsTexture = new TextureManager();
	instructionsTexture = new TextureManager();
	iconTexture = new TextureManager();
	// map textures
	if (!textures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures"));

	// object textures
	if (!textures2.initialize(graphics, TEXTURES2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures2"));
	//player texture

	if (!playerTexture->initialize(graphics, TEXTURE_PLAYER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	// item texture
	if (!itemTexture.initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	//tile texture
	if (!tileTexture->initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));
	//menu texture
	if (!menuTexture->initialize(graphics, TEXTURE_MENU))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	//button texture
	if (!buttonTexture->initialize(graphics, TEXTURE_BUTTONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu button texture"));
	//pause menu texture
	if (!pauseMenuTexture->initialize(graphics, TEXTURE_PAUSE_MENU))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause menu texture"));
	//pause menu button texture
	if (!pauseMenuButtonTexture->initialize(graphics, TEXTURE_PAUSE_MENU_BUTTONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause menu button texture"));
	//credits texture
	if (!creditsTexture->initialize(graphics, TEXTURE_CREDITS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credits texture"));
	if (!instructionsTexture->initialize(graphics, TEXTURE_INSTRUCTIONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credits texture"));
	if (!iconTexture->initialize(graphics, TEXTURE_ICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing  icon texture"));

	//player image
	player->setColorFilter(graphicsNS::MAGENTA);
	player->initialize(this, playerNS::PLAYER_WIDTH, playerNS::PLAYER_HEIGHT, 32, playerTexture); // to change
	player->setFrames(952, 955);
	player->setCurrentFrame(952);
	//player->setX(GAME_WIDTH / breakoutJackNS::TEXTURE_SIZE);
	//player->setY((GAME_HEIGHT - GAME_HEIGHT / breakoutJackNS::TEXTURE_SIZE - 2 * breakoutJackNS::TEXTURE_SIZE) - 100);
	// Need to spawn player in the middle for scrolling
	player->setX(GAME_WIDTH / 2);
	player->setY(100);
	player->setVelocity(VECTOR2(0, playerNS::FALLING_SPEED));
	// map tile image
	mapTile.initialize(graphics, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_SIZE, breakoutJackNS::TEXTURE_COLS, &textures);
	mapTile.setFrames(0, 0);
	mapTile.setCurrentFrame(0);

	dxFont.initialize(graphics, 20, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));

	loseFont = new TextDX();
	loseFont->initialize(graphics, 40, false, false, "Courier New");
	loseFont->setFontColor(SETCOLOR_ARGB(192, 255, 0, 0));

	//Load level controller
	levelController = new LevelController(graphics, this, tileTexture , iconTexture);
	levelController->loadTiles(tileTexture, this);
	hud = new HUD(graphics);
	OSD::instance()->setGraphics(graphics);
	npcController = new NPCController(graphics);
	NPC* npc;
	
	npc = npcController->spawnNPCs(1, this, 725, 544, 3, levelController);
	npc->addPath(VECTOR2(725, 544));
	npc->addPath(VECTOR2(1200, 544));
	npcController->addSpawnLoc(725, 544);
	
	npc = npcController->spawnNPCs(1, this, 325, 320, 4, levelController);
	npc->addPath(VECTOR2(325, 320));
	npc->addPath(VECTOR2(900, 320));
	npcController->addSpawnLoc(325, 320);
	
	menu = new Image();
	menu->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, menuTexture);
	menu->setX(0);
	menu->setY(0);
	buttonList = new list<Button*>();
	for (int i = 0; i < NUM_BUTTONS; i++) {
		Button* b = new Button(i + 1);
		b->initialize(this, buttonNS::width, buttonNS::height, buttonNS::cols, buttonTexture);
		b->setCurrentFrame(i);
		b->setX(GAME_WIDTH / 2 - 180);
		b->setY((GAME_HEIGHT + i* buttonNS::spacing - 400));
		buttonList->push_back(b);
	}
	pauseMenu = new Image();
	pauseMenu->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, pauseMenuTexture);
	pauseMenu->setX(0);
	pauseMenu->setY(0);
	pauseMenuButtonList = new list<Button*>();
	for (int i = 0; i < 3; i++) {
		Button* b = new Button(i);
		b->initialize(this, buttonNS::pMenu_width, buttonNS::pMenu_height, buttonNS::pMenu_cols, pauseMenuButtonTexture);
		b->setCurrentFrame(i);
		b->setX(GAME_WIDTH / 2 - 100);
		b->setY((GAME_HEIGHT + i* buttonNS::spacing - 500));
		pauseMenuButtonList->push_back(b);
	}
	credits = new Image();
	credits->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, creditsTexture);
	credits->setX(0);
	credits->setY(0);
	instructions = new Image();
	instructions->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, instructionsTexture);
	instructions->setX(0);
	instructions->setY(0);
}

//=============================================================================
// Update all game items
//=============================================================================
void BreakoutJack::update() {
	if (room == Menu) {
		menu->update(frameTime);
		if (skipFirstClick) {
			if (input->getMouseLButton()) {
				skipFirstClick = false;
			}
		} else {
			for (list<Button*>::iterator bList = buttonList->begin(); bList != buttonList->end(); ++bList) {
				(*bList)->active = true;
				if ((*bList)->isReleased(input)) {
					room = (*bList)->getID();
				}
				(*bList)->update(frameTime);
			}
		}
	} else if (room == Start) {
		//if pause button is pressed, display menu 
		if (input->isKeyDown(PAUSE))
			pause = true;
		if (pause) {
			pauseMenu->update(frameTime);
			for (list<Button*>::iterator bList = pauseMenuButtonList->begin(); bList != pauseMenuButtonList->end(); ++bList) {
				int i = -1;
				if ((*bList)->isReleased(input)) {
					i = (*bList)->getID();
				}
				if (i == Resume) {
					pause = false;
				} else if (i == Restart) {
					//restart level
					resetGame();
					pause = false;
					return;
				} else if (i == MainMenu) {
					pause = false;
					room = Menu;
					skipFirstClick = true;
				}
				(*bList)->update(frameTime);
			}
		} else {
			//if player loses (dies)
			if (player->getHealthStatus() == Player::PlayerHealthStatus::Dead)
			{
				if (input->anyKeyPressed() || input->getMouseLButton())
					resetGame();
			}
			//if player wins
			if (npcController->getNPCs().empty())
			{
				if (input->anyKeyPressed() || input->getMouseLButton())
				{
					room = Menu;
					resetGame();
				}		
			}
			// Variables for scrolling
			float playerX;
			float mapX = 0;
			// Boundaries
			float bndR = (GAME_WIDTH / 2) + (1 * playerNS::WIDTH);
			float bndL = (GAME_WIDTH / 2) - (1 * playerNS::WIDTH);
			//levelController->update(frameTime);

			crate.update(frameTime);
			player->update(frameTime, levelController);
			hud->update(frameTime, player->getInventory()->getActiveItem(), player);
			crate.update(frameTime);
			player->update(frameTime, levelController);
			//Scrolling code
			playerX = player->getX();
			float mapXCor = levelController->getMapX();
			// Check map is at the end in right direction
			if (levelController->getMapX() < float((2 * GAME_WIDTH - 5.0) * -1.0)) {
				mapX = 0;//float(GAME_WIDTH * -1.0);
				bndR = GAME_WIDTH;
				//player->setVelocityX(0);
			}
			// Check if map is at end in the left direction
			if (levelController->getMapX() > 0) {
				mapX = 0;
				bndL = 0;
				//player->setVelocityX(0);
			}
			// Adjust map to the right if player exceeds boundary to the left
			if (playerX < bndL) {
				mapX = (player->getVelocity().x * frameTime);
				bndR = (GAME_WIDTH / 2) + (1 * playerNS::WIDTH);
				player->setX(bndL);
			}
			// Adjust map to the left if player exceeds boundary to the Right
			else if (playerX > bndR) {
				mapX = (player->getVelocity().x * frameTime);
				bndL = (GAME_WIDTH / 2) - (1 * playerNS::WIDTH);
				player->setX(bndR);
			}
			levelController->setMapX(mapX);
			levelController->update(frameTime, VECTOR2(player->getX(),player->getY()));
			npcController->setMapX(mapX);
			npcController->chaseIfInRange(VECTOR2(player->getX(), player->getY()));
			npcController->update(frameTime, levelController);

		}
	} else if (room == Instructions) {
		//display instructions or whatever
		if (input->isKeyDown(VK_BACK))
		{
			skipFirstClick = true;
			room = Menu;
		}
		instructions->update(frameTime);
	} else if (room == Credits) {
		if (input->isKeyDown(VK_BACK))
		{
			skipFirstClick = true;
			room = Menu;
		}	
		credits->update(frameTime);
	}
	else if (room == Exit) {
		//Quit game
		exitGame();
	}
	//levelController->setMapX(mapX);
	//levelController->update(frameTime);

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
	if (room == Start) {
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
		npcController->collisions(levelController);
		levelController->collisions();
		//player collision with projectile
		list<Projectile*>::iterator projectileIter = levelController->projectiles.begin();
		bool removed = false;
		while (!levelController->projectiles.empty() && projectileIter != levelController->projectiles.end())
		{
			removed = false;
			if ((*projectileIter)->collidesWith(*player, collisionVector) && (*projectileIter)->getOwner() != Projectile::Player)
			{
				player->damage((*projectileIter)->getDamage());
				projectileIter = levelController->projectiles.erase(projectileIter);
				removed = true;
			}
			if(!removed)
				++projectileIter;
		}
	}

}
//=============================================================================
// Render game items
//=============================================================================
void BreakoutJack::render() {
	graphics->spriteBegin();
	if (room == Menu) {
		menu->draw();
		for (list<Button*>::iterator bList = buttonList->begin(); bList != buttonList->end(); ++bList) {
			(*bList)->draw();
		}
	} else if (room == Start) {
		if (pause) {
			levelController->render(graphics);
			npcController->render();
			player->draw();
			crate.draw();
			hud->draw();
			OSD::instance()->draw();
			pauseMenu->draw();
			for (list<Button*>::iterator bList = pauseMenuButtonList->begin(); bList != pauseMenuButtonList->end(); ++bList) {
				(*bList)->draw();
			}
		} else {
			levelController->render(graphics);
			npcController->render();
			player->draw();
			crate.draw();
			hud->draw();
			OSD::instance()->draw();
			string text;
			if (player->getHealthStatus() == Player::PlayerHealthStatus::Dead)
			{
				text = "         YOU LOSE\nPress any button to restart";
				loseFont->print(text, GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2);
			}
			if (npcController->getNPCs().empty())
			{
				text = "        YOU WIN\nPress any button to continue";
				loseFont->print(text, GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2);
			}
			
		}
	} else if (room == Instructions) {
		//draw instructions stuff
		instructions->draw();
	} else if (room == Credits) {
		//draw credits stuff
		credits->draw();
	}
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

void BreakoutJack::resetGame()
{
	initialize(hwnd);
}

