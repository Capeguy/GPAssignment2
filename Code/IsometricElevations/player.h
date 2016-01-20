#pragma once
#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace playerNS
{
	const int X = 0;   // location on screen
	const int Y = 0;
	const float SPEED = 800;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const float JUMP_HEIGHT = 800.0;

	const int   TEXTURE_SIZE = 64;           // texture has 8 columns
	const int   TEXTURE_COLS = 32;           // texture has 8 columns
	const int   PLAYER_START_FRAME = 952;      // playership starts at frame 4
	const int   PLAYER_END_FRAME = 955;        // playership animation frames 4,5,6,7

	const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Player : public Entity
{
	enum PlayerOrientation { right, down, left, up};
private:
	bool jump = false;
	bool doubleJump = false;
	int orientation = right;

public:
	// constructor
	Player();
	~Player();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);

};
#endif