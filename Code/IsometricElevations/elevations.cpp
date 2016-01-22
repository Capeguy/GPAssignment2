// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Elevations.cpp Isometric Elevation Demo v1.0
// Elevations is the class we create.

#include "Elevations.h"
using namespace std;
using namespace elevationsNS;

//=============================================================================
// Constructor
//=============================================================================
Elevations::Elevations()
{
	
}

//=============================================================================
// Destructor
//=============================================================================
Elevations::~Elevations()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void Elevations::initialize(HWND hwnd)
{
    Game::initialize(hwnd);

    // map textures
    if (!textures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures"));

    // object textures
    if (!textures2.initialize(graphics,TEXTURES2_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing textures2"));
	//player texture
	if (!playerTexture.initialize(graphics, TEXTURE_PLAYER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	//player image
	player.setColorFilter(graphicsNS::MAGENTA);
	player.initialize(this, playerNS::PLAYER_WIDTH, playerNS::PLAYER_HEIGHT, 32, &playerTexture); // to change
	player.setFrames(952, 955);
	player.setCurrentFrame(952);
	player.setX(GAME_WIDTH / elevationsNS::TEXTURE_SIZE);
	player.setY(GAME_HEIGHT - GAME_HEIGHT / elevationsNS::TEXTURE_SIZE - 2 * elevationsNS::TEXTURE_SIZE);
	
    // map tile image
    mapTile.initialize(graphics, elevationsNS::TEXTURE_SIZE, elevationsNS::TEXTURE_SIZE, elevationsNS::TEXTURE_COLS,&textures);
    mapTile.setFrames(0, 0);
    mapTile.setCurrentFrame(0);

    //// Tree image
    tree.initialize(graphics, elevationsNS::TEXTURE2_SIZE, elevationsNS::TEXTURE2_SIZE, elevationsNS::TEXTURE2_COLS,&textures2);
    tree.setFrames(TREE0_FRAME, TREE0_FRAME);
    tree.setCurrentFrame(TREE0_FRAME);

	dxFont.initialize(graphics, 12, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
	levelController = new LevelController(graphics, this);
	levelController->loadTiles();
}

//=============================================================================
// Update all game items
//=============================================================================
void Elevations::update()
{

    //mapTile.update(frameTime);
	//levelController->update(frameTime);
	/*
	int playerBottomLeftX = player.getX();
	int playerBottomLeftY = player.getY() + playerNS::PLAYER_HEIGHT + 1;
	int playerBottomRightX = player.getX() + playerNS::PLAYER_WIDTH;
	int playerBottomRightY = player.getY() + playerNS::PLAYER_HEIGHT + 1;
	int bottomLeftRow = (int)(floor((double)playerBottomLeftX / TEXTURE_SIZE));
	int bottomLeftCol = (int)(floor((double)playerBottomLeftY / TEXTURE_SIZE));
	int bottomRightRow = (int)(floor((double)playerBottomRightX / TEXTURE_SIZE));
	int bottomRightCol = (int)(floor((double)playerBottomRightY / TEXTURE_SIZE));
	int tileAtPlayerBottomLeft = tileMap[bottomLeftCol - 1][bottomLeftRow];
	int tileAtPlayerBottomRight = tileMap[bottomRightCol - 1][bottomRightRow - 1];
	if (tileSolid[tileAtPlayerBottomLeft][1] == 0 && tileSolid[tileAtPlayerBottomRight][1] == 0) {
		player.setFalling(true);
	}
	*/
	player.update(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Elevations::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Elevations::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Elevations::render()
{
    graphics->spriteBegin();
	player.draw();
	string buffer;
    // Draw map in Isometric Diamond
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
				dxFont.print(buffer, row * levelControllerNS::TEXTURE2_SIZE, col * levelControllerNS::TEXTURE2_SIZE);
			}
        }
		/*
		for (int row = 0; row<levelControllerNS::MAP_SIZE_X; row++) {
			for (int col = 0; col < levelControllerNS::MAP_SIZE_Y; col++) {
				levelController->mapTile[col][row].draw();
			}
		}
		*/
    }
	
	/*
    // Draw Objects,  0=empty, 1=Tree0, 2=Tree1
    float treeX = 0, treeY = 0;
    for(int row=0; row<MAP_SIZE; row++)
    {
        for(int col=0; col<MAP_SIZE; col++)
        {
            switch(objectMap[row][col])
            {
            case 1:     // Tree0
                tree.setX((float)( SCREEN_X - (row*TEXTURE_SIZE/2) + (col*TEXTURE_SIZE/2) ) +
                                    TREE_OFFSET_X);
                tree.setY((float)( SCREEN_Y + (row*TEXTURE_SIZE/4) + (col*TEXTURE_SIZE/4) -
                                   heightMap[row][col] * HEIGHT_CHANGE) + TREE_OFFSET_Y);
                if(col%2)
                    tree.flipHorizontal(true);
                // draw shadow
                tree.setCurrentFrame(TREE0_SHADOW);
                tree.setDegrees(TREE_SHADOW_DEGREES);
                treeX = tree.getX();
                treeY = tree.getY();
                tree.setX(treeX + TREE_SHADOW_X);
                tree.setY(treeY + TREE_SHADOW_Y);
                tree.draw(graphicsNS::ALPHA25 & graphicsNS::BLACK);
                tree.setX(treeX);   // restore X
                tree.setY(treeY);   // restore Y
                // draw tree
                tree.setDegrees(0);
                tree.setCurrentFrame(TREE0_FRAME);
                tree.draw();
                tree.flipHorizontal(false);
                break;
            case 2:     // Tree1
                tree.setX((float)( SCREEN_X - (row*TEXTURE_SIZE/2) + (col*TEXTURE_SIZE/2) ) +
                                    TREE_OFFSET_X);
                tree.setY((float)( SCREEN_Y + (row*TEXTURE_SIZE/4) + (col*TEXTURE_SIZE/4) -
                                   heightMap[row][col] * HEIGHT_CHANGE) + TREE_OFFSET_Y);
                if(col%2)
                    tree.flipHorizontal(true);
                // draw shadow
                tree.setCurrentFrame(TREE1_SHADOW);
                tree.setDegrees(TREE_SHADOW_DEGREES);   // rotate shadow
                treeX = tree.getX();                    // save tree x,y
                treeY = tree.getY();
                tree.setX(treeX + TREE_SHADOW_X);       // position shadow
                tree.setY(treeY + TREE_SHADOW_Y);
                tree.draw(graphicsNS::ALPHA25 & graphicsNS::BLACK); // draw shadow
                tree.setX(treeX);                       // restore tree x,y
                tree.setY(treeY);
                // draw tree
                tree.setDegrees(0);
                tree.setCurrentFrame(TREE1_FRAME);
                tree.draw();
                tree.flipHorizontal(false);
                break;
            }
        }
    }
	*/
    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Elevations::releaseAll()
{
    textures.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Elevations::resetAll()
{
    textures.onResetDevice();

    Game::resetAll();
    return;
}
