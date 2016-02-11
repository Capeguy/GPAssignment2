#pragma once
#ifndef _GUARD_H                 // Prevent multiple definitions if this 
#define _GUARD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

class Guard : public NPC 
{
private:
	Pistol* pistol;
	TextureManager* gunTexture;
public:
	Guard();	
	~Guard();
	void ai(float frameTime, Entity & ent, float mapX);
	void draw();
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
};
#endif