#include "prisonEscape.h"

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
	return;
}
LRESULT PrisonEscape::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized)     // do not process messages if not initialized
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);        //tell Windows to kill this program
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
			input->keyDown(wParam);
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:        // key up
			input->keyUp(wParam);
			return 0;
		case WM_CHAR:                           // character entered
			input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE:                      // mouse moved
			input->mouseIn(lParam);
			return 0;
		case WM_INPUT:                          // raw mouse data in
			input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN:                    // left mouse button down
			input->setMouseLButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_LBUTTONUP:                      // left mouse button up
			input->setMouseLButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_MBUTTONDOWN:                    // middle mouse button down
			input->setMouseMButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_MBUTTONUP:                      // middle mouse button up
			input->setMouseMButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_RBUTTONDOWN:                    // right mouse button down
			input->setMouseRButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_RBUTTONUP:                      // right mouse button up
			input->setMouseRButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP: // mouse X button down/up
			input->setMouseXButton(wParam);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_DEVICECHANGE:                   // check for controller insert
			input->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);    // let Windows handle it
}
//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void PrisonEscape::initialize(HWND hwnd)
{
	//Game::initialize(hwnd); // throws GameError

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
	//ui->onLostDevice();

	//Game::releaseAll();
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
	//ui->onResetDevice();

	//Game::resetAll();
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
/*
void PrisonEscape::attemptQuestCompletions()
{
	
}

Entity* PrisonEscape::dropEasterEgg()
{
	return new Entity();
}

void PrisonEscape::saveAnalyticsData()
{
	
}
*/
void PrisonEscape::run(HWND x) {

}
void PrisonEscape::deleteAll() {

}

// Render game items.
void PrisonEscape::renderGame() {

}

// Handle lost graphics device
void PrisonEscape::handleLostGraphicsDevice() {

}
void PrisonEscape::deleteEntity(Entity* e) {

}