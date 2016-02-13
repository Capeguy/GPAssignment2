#pragma once
#pragma once
#ifndef _TILE_H                 // Prevent multiple definitions if this 
#define _TILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace tileNS {
	const int	X = 0;
	const int	Y = 0;
	const float SPEED = 64;
	const float FALLING_SPEED = 32;
	const float MASS = 300.0f;
	const float JUMP_HEIGHT = 64;
	const int   TEXTURE_SIZE = 64;
	const int   TEXTURE_COLS = 32;
	const int   PLAYER_START_FRAME = 952;
	const int   PLAYER_END_FRAME = 955;
	const float PLAYER_ANIMATION_DELAY = 0.2f;
	const float PLAYER_WIDTH = 64.0;
	const float PLAYER_HEIGHT = 64.0;
}

class Tile : public Entity
{
private:
	int id;
	bool solid;
	Game *gamePtr;
	int width;
	int height;
	int ncols;
	TextureManager *textureM;
	float stayTime = 0;

public:
	Tile();
	Tile(int id, bool solid);
	~Tile();
	int getId();
	void setId(int i);
	bool isSolid(bool skip = false);
	void refresh(float);
	virtual void draw();
	virtual bool initialize();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
};
#endif