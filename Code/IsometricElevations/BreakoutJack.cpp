
#include "BreakoutJack.h"

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

	// Initialize Textures
	textures = new TextureManager();
	itemTexture = new TextureManager();
	tileTexture = new TextureManager();
	menuTexture = new TextureManager();
	buttonTexture = new TextureManager();
	playerTexture = new TextureManager();
	pauseMenuTexture = new TextureManager();
	pauseMenuButtonTexture = new TextureManager();
	creditsTexture = new TextureManager();
	instructionsTexture = new TextureManager();
	iconTexture = new TextureManager();
	winLoseButtonTexture = new TextureManager();
	npcTexture = new TextureManager();
	// map textures
	if (!textures->initialize(graphics, TEXTURE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures"));
	// player texture
	if (!playerTexture->initialize(graphics, TEXTURE_PLAYER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	// item texture
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	// tile texture
	if (!tileTexture->initialize(graphics, TEXTURE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));
	// menu texture
	if (!menuTexture->initialize(graphics, TEXTURE_MENU))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// button texture
	if (!buttonTexture->initialize(graphics, TEXTURE_BUTTONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu button texture"));
	// pause menu texture
	if (!pauseMenuTexture->initialize(graphics, TEXTURE_PAUSE_MENU))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause menu texture"));
	// pause menu button texture
	if (!pauseMenuButtonTexture->initialize(graphics, TEXTURE_PAUSE_MENU_BUTTONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause menu button texture"));
	// credits texture
	if (!creditsTexture->initialize(graphics, TEXTURE_CREDITS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credits texture"));
	// instructions texture
	if (!instructionsTexture->initialize(graphics, TEXTURE_INSTRUCTIONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions texture"));
	// icons texture
	if (!iconTexture->initialize(graphics, TEXTURE_ICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing icon texture"));
	// buttons texture
	if (!winLoseButtonTexture->initialize(graphics, TEXTURE_WINLOSE_BUTTON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing win lose button icon texture"));
	// npcs texture
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing npc texture"));

	// Initialize Player
	player = new Player();
	player->setColorFilter(graphicsNS::MAGENTA);
	player->initialize(this, playerNS::PLAYER_WIDTH, playerNS::PLAYER_HEIGHT, 32, playerTexture); // to change
	player->setFrames(952, 955);
	player->setCurrentFrame(952);

	// Initialize Fonts
	dxFont.initialize(graphics, 20, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	loseFont = new TextDX();
	loseFont->initialize(graphics, 40, false, false, "Courier New");
	loseFont->setFontColor(SETCOLOR_ARGB(192, 255, 0, 0));

	// Initialize level controller
	levelController = new LevelController(graphics, this, tileTexture, iconTexture);
	levelController->loadTiles(tileTexture, this);

	// Initialize HUD & OSD
	hud = new HUD(graphics);
	OSD::instance()->setGraphics(graphics);

	// Initialize NPCController and NPCs
	npcController = new NPCController(graphics, iconTexture, this);
	guard = new Guard();
	medic = new Medic();
	jack = new Jack();
	dog = new Dog();
	warden = new Warden();

	// Guard 1.1
	guard->addPath(VECTOR2(325, 320));
	guard->addPath(VECTOR2(900, 320));
	npcController->addNPC(guard, 0, levelController, graphics);

	// Guard 1.2
	dog = new Dog();
	dog->addPath(VECTOR2(725, 544));
	dog->addPath(VECTOR2(1200, 544));
	npcController->addNPC(dog, 5, levelController, graphics);

	//Guard 1.5
	guard = new Guard();
	guard->addPath(VECTOR2(1345, 352));
	guard->addPath(VECTOR2(1468, 352));
	npcController->addNPC(guard, 2, levelController, graphics);

	//Guard 2.1
	guard = new Guard();
	guard->addPath(VECTOR2(1569, 320));
	guard->addPath(VECTOR2(2200, 320));
	npcController->addNPC(guard, 1, levelController, graphics);

	// Guard 2.2
	guard = new Guard();
	guard->addPath(VECTOR2(1985, 544));
	guard->addPath(VECTOR2(2325, 544));
	npcController->addNPC(guard, 0, levelController, graphics);

	// Medic 1.1
	medic->addPath(VECTOR2(210, 608));
	npcController->addNPC(medic, 6, levelController, graphics);

	// Agent Jack
	jack->addPath(VECTOR2(2596, 320));
	jack->addPath(VECTOR2(2718, 320));
	npcController->addNPC(jack, 4, levelController, graphics);

	// Medic 3.1
	medic = new Medic();
	medic->addPath(VECTOR2(2463, 544));
	npcController->addNPC(medic, 6, levelController, graphics);

	// Warden
	warden->addPath(VECTOR2(3393, 390));
	warden->setScale(3);
	npcController->addNPC(warden, 8, levelController, graphics);
	// End of NPCs

	// Initialize Menus & Buttons
	menu = new Image();
	menu->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, menuTexture);
	menu->setX(0);
	menu->setY(0);
	buttonList = new std::list<Button*>();
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
	pauseMenuButtonList = new std::list<Button*>();
	for (int i = 0; i < 3; i++) {
		Button* b = new Button(i);
		b->initialize(this, buttonNS::pMenu_width, buttonNS::pMenu_height, buttonNS::pMenu_cols, pauseMenuButtonTexture);
		b->setCurrentFrame(i);
		b->setX(GAME_WIDTH / 2 - 100);
		b->setY((GAME_HEIGHT + i* buttonNS::spacing - 500));
		pauseMenuButtonList->push_back(b);
	}
	winLoseButtonList = new std::list<Button*>();
	for (int i = 0; i < 3; i++) {
		Button* b = new Button(i);
		b->initialize(this, buttonNS::winLose_width, buttonNS::winLose_height, buttonNS::winLose_cols, winLoseButtonTexture);
		b->setCurrentFrame(i);
		b->setX(GAME_WIDTH / 2 - 250 + (buttonNS::winLose_spacing * i));
		b->setY((GAME_HEIGHT - 300));
		winLoseButtonList->push_back(b);
	}
	credits = new Image();
	credits->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, creditsTexture);
	credits->setX(0);
	credits->setY(0);
	instructions = new Image();
	instructions->initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, instructionsTexture);
	instructions->setX(0);
	instructions->setY(0);

	// Set player starting position: Need to spawn player in the middle for scrolling
	player->setX(GAME_WIDTH / 2);
	player->setY(50);
	player->setVelocity(VECTOR2(0, 0));

	// Play BGM
	audio->playCue(BK_MUSIC);
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
			for (std::list<Button*>::iterator bList = buttonList->begin(); bList != buttonList->end(); ++bList) {
				(*bList)->active = true;
				if ((*bList)->isReleased(input)) {
					room = (*bList)->getID();
				}
				(*bList)->update(frameTime);
			}
		}
	} else if (room == Start) {
		// If pause button is pressed, display menu 
		if (input->isKeyDown(PAUSE))
			pause = true;
		if (pause) {
			pauseMenu->update(frameTime);
			for (std::list<Button*>::iterator bList = pauseMenuButtonList->begin(); bList != pauseMenuButtonList->end(); ++bList) {
				int i = -1;
				if ((*bList)->isReleased(input)) {
					i = (*bList)->getID();
				}
				if (i == Resume) {
					pause = false;
				} else if (i == Restart) { // Restart Level
					stopAllMusic();
					resetGame();
					pause = false;
					return;
				} else if (i == MainMenu) {
					audio->stopCue(BOSS_MUSIC);
					audio->stopCue(VICTORY_MUSIC);
					audio->stopCue(LOSE_MUSIC);
					pause = false;
					room = Menu;
					skipFirstClick = true;
				}
				(*bList)->update(frameTime);
			}
		} else {
			// If player loses or wins
			if (player->getHealthStatus() == Player::PlayerHealthStatus::Dead || npcController->getBossDeathStatus()) {
				for (std::list<Button*>::iterator bList = winLoseButtonList->begin(); bList != winLoseButtonList->end(); ++bList) {
					int i = -1;
					if ((*bList)->isClicked(input)) {
						i = (*bList)->getID();
					}
					if (i == Redo) { // Restart Level
						stopAllMusic();
						resetGame();
						return;
					} else if (i == Main) {
						stopAllMusic();
						pause = false;
						room = Menu;
						resetGame();
						return;
					} else if (i == QuitGame) {
						exitGame();
						return;
					}
					skipFirstClick = true;
					(*bList)->update(frameTime);
				}
			}
			// Scrolling code
			// Variables for scrolling
			float playerX;
			float mapX = 0;
			// Boundaries
			float bndR = (GAME_WIDTH / 2) + (1 * playerNS::WIDTH);
			float bndL = (GAME_WIDTH / 2) - (1 * playerNS::WIDTH);
			playerX = player->getX();
			// Check map is at the end in right direction
			if (levelController->getMapX() < float((2 * GAME_WIDTH - 5.0) * -1.0)) {
				mapX = 0;
				bndR = GAME_WIDTH;
			}
			// Check if map is at end in the left direction
			if (levelController->getMapX() > -5) {
				mapX = 0;
				bndL = 0;
			}
			// Adjust map to the right if player exceeds boundary to the left
			if (playerX < bndL) {
				mapX = (player->getVelocity().x * frameTime);
				bndR = (GAME_WIDTH / 2) + (1 * playerNS::WIDTH);
				player->setX(bndL);
			} else if (playerX > bndR) { // Adjust map to the left if player exceeds boundary to the Right
				float test = player->getVelocity().x;
				mapX = (player->getVelocity().x * frameTime);
				bndL = (GAME_WIDTH / 2) - (1 * playerNS::WIDTH);
				player->setX(bndR);
			}
			levelController->setMapX(mapX);
			npcController->setMapX(mapX);
			hud->update(frameTime, player->getInventory()->getActiveItem(), player);
			player->update(frameTime, levelController);
			levelController->update(frameTime, VECTOR2(player->getX(), player->getY()));
			npcController->update(frameTime, levelController);
		}
	} else if (room == Instructions) {
		// Display instructions
		if (input->isKeyDown(VK_BACK)) {
			skipFirstClick = true;
			room = Menu;
		}
		instructions->update(frameTime);
	} else if (room == Credits) {
		if (input->isKeyDown(VK_BACK)) {
			skipFirstClick = true;
			room = Menu;
		}
		credits->update(frameTime);
	} else if (room == Exit) {
		// Quit game
		exitGame();
	}
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
		npcController->collisions(levelController, player);
		levelController->collisions();
		// Player collision with projectile
		std::list<Projectile*>::iterator projectileIter = levelController->projectiles.begin();
		bool removed = false;
		while (!levelController->projectiles.empty() && projectileIter != levelController->projectiles.end()) {
			removed = false;
			if ((*projectileIter)->collidesWith(*player, collisionVector) && (*projectileIter)->getOwner() != Projectile::Player) {
				player->damage((*projectileIter)->getDamage());
				projectileIter = levelController->projectiles.erase(projectileIter);
				removed = true;
			}
			if (!removed)
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
		for (std::list<Button*>::iterator bIter = buttonList->begin(); bIter != buttonList->end(); ++bIter) {
			(*bIter)->draw();
		}
	} else if (room == Start) {
		if (pause) {
			levelController->render(graphics);
			npcController->render();
			player->draw();
			hud->draw();
			OSD::instance()->draw(drawOSD);
			pauseMenu->draw();
			for (std::list<Button*>::iterator bIter = pauseMenuButtonList->begin(); bIter != pauseMenuButtonList->end(); ++bIter) {
				(*bIter)->draw();
			}
		} else {
			levelController->render(graphics);
			npcController->render();
			player->draw();
			hud->draw();
			OSD::instance()->draw(drawOSD);
			std::string text;
			if (player->getHealthStatus() == Player::PlayerHealthStatus::Dead) {
				audio->stopCue(BK_MUSIC);
				audio->playCue(LOSE_MUSIC);
				text = "         YOU LOSE\nPress any button to restart";
				loseFont->print(text, GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2);
				for (std::list<Button*>::iterator bIter = winLoseButtonList->begin(); bIter != winLoseButtonList->end(); ++bIter) {
					(*bIter)->draw();
				}
			}
			if (npcController->getBossDeathStatus()) {
				audio->stopCue(BK_MUSIC);
				audio->stopCue(BOSS_MUSIC);
				audio->playCue(VICTORY_MUSIC);
				text = "        YOU WIN\nPress any button to continue";
				levelController->releaseJack();
				jack->setAiState(NPC::Chase);
				loseFont->print(text, GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2);
				for (std::list<Button*>::iterator bList = winLoseButtonList->begin(); bList != winLoseButtonList->end(); ++bList) {
					(*bList)->draw();
				}
			}
		}
	} else if (room == Instructions) {
		instructions->draw();
	} else if (room == Credits) {
		credits->draw();
	}
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void BreakoutJack::releaseAll() {
	textures->onLostDevice();
	playerTexture->onLostDevice();
	tileTexture->onLostDevice();
	itemTexture->onLostDevice();
	menuTexture->onLostDevice();
	buttonTexture->onLostDevice();
	pauseMenuTexture->onLostDevice();
	pauseMenuButtonTexture->onLostDevice();
	creditsTexture->onLostDevice();
	instructionsTexture->onLostDevice();
	iconTexture->onLostDevice();
	winLoseButtonTexture->onLostDevice();
	npcTexture->onLostDevice();
	Game::releaseAll();
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void BreakoutJack::resetAll() {
	textures->onResetDevice();
	playerTexture->onResetDevice();
	tileTexture->onResetDevice();
	itemTexture->onResetDevice();
	menuTexture->onResetDevice();
	buttonTexture->onResetDevice();
	pauseMenuTexture->onResetDevice();
	pauseMenuButtonTexture->onResetDevice();
	creditsTexture->onResetDevice();
	instructionsTexture->onResetDevice();
	iconTexture->onResetDevice();
	winLoseButtonTexture->onResetDevice();
	npcTexture->onResetDevice();
	Game::resetAll();
}
void BreakoutJack::stopAllMusic() {
	audio->stopCue(BOSS_MUSIC);
	audio->stopCue(VICTORY_MUSIC);
	audio->stopCue(LOSE_MUSIC);
	audio->stopCue(BK_MUSIC);
}
void BreakoutJack::consoleCommand() {
	command = console->getCommand();    // get command from console
	if (command == "") {
		return;
	} else if (command == "help") {
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		console->print("osd - toggle display of On-Screen Display");
		console->print("tile - toggle display of Tile Info");
		console->print("p - Display Player co-ordinates");
		console->print("mouse - toggle display of mouse position");
		console->print("noclip - toggle display of mouse position");
	} else if (command == "noclip") {
		player->noClip = !player->noClip;
	} else if (command == "osd") {
		drawOSD = !drawOSD;
	} else if (command == "fps") {
		fpsOn = !fpsOn;
	} else if (command == "tile") {
		levelController->debugInfo = !levelController->debugInfo;
	} else if (command == "p") {
		console->print("Player is at (" + std::to_string(player->getX()) + ", " + std::to_string(player->getY()) + ")");
		console->print("(" + std::to_string(player->topLeft.x) + ", " + std::to_string(player->topLeft.y) + ") ---- (" + std::to_string(player->topRight.x) + ", " + std::to_string(player->topRight.y) + ")");
		console->print("  |   ----   |  ");
		console->print("(" + std::to_string(player->bottomLeft.x) + ", " + std::to_string(player->bottomLeft.y) + ") ---- (" + std::to_string(player->bottomRight.x) + ", " + std::to_string(player->bottomRight.y) + ")");
	} else if (command == "mouse") {
		mouseOn = !mouseOn;
	}
}

void BreakoutJack::resetGame() {
	initialize(hwnd);
}

Player* BreakoutJack::getPlayer() {
	return player;
}
