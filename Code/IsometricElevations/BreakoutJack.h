
#ifndef _BREAKOUTJACK_H           // Prevent multiple definitions if this 
#define _BREAKOUTJACK_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <fstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"
#include "levelController.h"
#include "crate.h"
#include "itemController.h"
#include "hud.h"
#include "OSD.h"
#include "npcController.h"
#include "button.h"
#include "guard.h"
#include "medic.h"
#include "dog.h"
#include "jack.h"
#include "warden.h"

namespace breakoutJackNS {
	// Map textures
	const int TEXTURE_COLS = 19;
	const int TEXTURE_SIZE = 32;
	const int TILE_COUNT = 600;
	// size of height change in pixels for current tile set
	const int HEIGHT_CHANGE = 64; 
	const int MAP_SIZE_X = 40;
	const int MAP_SIZE_Y = 25;
	const int SCREEN_X = GAME_WIDTH / 2 - TEXTURE_SIZE / 2;
	const int SCREEN_Y = GAME_HEIGHT / 8;
}

// BreakoutJack is the class we create, it inherits from the Game class
class BreakoutJack : public Game
{
private:
	// game items
	TextureManager* textures;    
	TextureManager* playerTexture; 
	TextureManager* tileTexture;
	TextureManager* itemTexture;		
	TextureManager* menuTexture;
	TextureManager* buttonTexture;
	TextureManager* pauseMenuTexture;
	TextureManager* pauseMenuButtonTexture;
	TextureManager* creditsTexture;
	TextureManager* instructionsTexture;
	TextureManager* iconTexture;
	TextureManager* winLoseButtonTexture;
	TextureManager* npcTexture;
	NPCController*	npcController;
	Image* instructions;
	Image* menu;
	Image* pauseMenu;
	Image* credits;
	TextDX	dxFont;
	TextDX* loseFont;
	COLOR_ARGB fontColor;
	RECT	textRect;
	Player* player;
	HUD* hud;
	std::list<Button*>* buttonList;
	std::list<Button*>* pauseMenuButtonList;
	std::list<Button*>* winLoseButtonList;
	Guard*	guard;
	Medic*	medic;
	Jack*	jack;
	Dog*	dog;
	Warden* warden;
	bool	pause = false;
	bool	skipFirstClick = false;
	int		room = Menu;
public:
	enum Room { Menu, Start, Instructions, Credits, Exit };
	enum PauseMenu { Resume, Restart, MainMenu };
	enum WinLose { Redo, Main, QuitGame };
	LevelController* levelController;
	// Constructor
	BreakoutJack();
	// Destructor
	virtual ~BreakoutJack();
	// Initialize the game
	void initialize(HWND hwnd);
	void update();      
	void ai();          
	void collisions();  
	void render();      
	void releaseAll();
	void resetAll();
	void stopAllMusic();
	void consoleCommand();
	void resetGame();
	Player* getPlayer();
};
#endif