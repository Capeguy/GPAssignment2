#include "PrisonEscape.h"

//#include "drawManager.h"
//#include "mapLoader.h"
#include "tile.h"
//#include "PersonLoader.h"
#include <sstream>
#include <random>
//#include "ChatData.h"
//#include "InventoryBoost.h"
//#include "Aidil.h"
//#include "NoiseManager.h"
//#include "RiftData.h"


#include <iostream>
#include <fstream>

//=============================================================================
// Constructor
//=============================================================================
PrisonEscape::PrisonEscape()
{//Mem leak free
	dragonfireTexture = new TextureManager();
	uiFont = new TextDX();
	easterEggCounter = 0;
}

//=============================================================================
// Destructor
//=============================================================================
PrisonEscape::~PrisonEscape()
{
	
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void PrisonEscape::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

							/* initialize random seed: */
	srand(time(NULL));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void PrisonEscape::update()
{
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void PrisonEscape::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void PrisonEscape::collisions()
{
	VECTOR2 collisionVector;
}

//=============================================================================
// Render game items
//=============================================================================
void PrisonEscape::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	

	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void PrisonEscape::releaseAll()
{
	//drawManager->releaseAll();
	uiFont->onLostDevice();
	//UI is their own class as well, and needs to be told to release their inner children's
	//textures and text (The entity manager only does it for the texture)
	ui->onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void PrisonEscape::resetAll()
{
	//drawManager->resetAll();
	uiFont->onResetDevice();
	//UI is their own class as well, and needs to be told to release their inner children's
	//textures and text (The entity manager only does it for the texture)
	ui->onResetDevice();

	Game::resetAll();
	return;
}


//=============================================================================
// Processes the command entered, performing different actions depending on the command
// Returns true if command was processed, false on no processing
//=============================================================================
bool PrisonEscape::processCommand(std::string command)
{
	return true;
}

void PrisonEscape::attemptQuestCompletions()
{
	
}

Entity* PrisonEscape::dropEasterEgg()
{
	
}

void PrisonEscape::saveAnalyticsData()
{
	
}