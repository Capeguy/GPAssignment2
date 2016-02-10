
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
//#include "machineGun.h"
namespace breakoutJackNS {
	// Map textures
	const int TEXTURE_COLS = 19;
	const int TEXTURE_SIZE = 32;
	const int TILE_COUNT = 600;
	// size of height change in pixels for current tile set
	const int HEIGHT_CHANGE = 64;
	//const int HEIGHT_CHANGE = 32;     
	const int MAP_SIZE_X = 40;
	const int MAP_SIZE_Y = 25;
	const int SCREEN_X = GAME_WIDTH / 2 - TEXTURE_SIZE / 2;
	const int SCREEN_Y = GAME_HEIGHT / 8;

	// Object textures
	const int TEXTURE2_COLS = 32;
	const int TEXTURE2_SIZE = 32;
	const int TREE0_FRAME = 0;
	const int TREE1_FRAME = 1;
	const int TREE_OFFSET_X = -32;  // add to map X to get tree X
	const int TREE_OFFSET_Y = -96;  // add to map Y to get tree Y
	const int TREE0_SHADOW = 2;
	const int TREE1_SHADOW = 3;
	const float TREE_SHADOW_DEGREES = 335;
	const float TREE_SHADOW_X = -21;  // offset after rotation
	const float TREE_SHADOW_Y = 5;


}

// BreakoutJack is the class we create, it inherits from the Game class
class BreakoutJack : public Game
{
private:
	// game items
	TextureManager textures;    // textures
	TextureManager textures2;   // object texture
	TextureManager* playerTexture; // player texture
	TextureManager* tileTexture;
	TextureManager itemTexture;		// item texture
	TextureManager* menuTexture;
	TextureManager* buttonTexture;
	TextureManager* pauseMenuTexture;
	TextureManager* pauseMenuButtonTexture;
	TextureManager* creditsTexture;
	TextureManager* instructionsTexture;
	TextureManager* iconTexture;
	Image* instructions;
	Image* menu;
	Image* pauseMenu;
	Image   mapTile;
	Image* credits;
	Crate crate;
	TextDX	dxFont;
	COLOR_ARGB fontColor;
	RECT	textRect;
	Player* player;
	HUD* hud;
	NPCController* npcController;
	int room = Menu;
	list<Button*>* buttonList;
	list<Button*>* pauseMenuButtonList;
	bool pause = false;
	bool skipFirstClick = false;

public:
	LevelController* levelController;
	// Constructor
	BreakoutJack();
	// Destructor
	virtual ~BreakoutJack();
	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
	bool tileIsSolid(int x, int y);
	void consoleCommand();
	void resetGame();
	enum Room { Menu, Start, Instructions, Credits, Exit };
	enum PauseMenu { Resume, Restart, MainMenu };
};

#endif
// TODO: Ensure all classes have proper memory deallocation in destructor