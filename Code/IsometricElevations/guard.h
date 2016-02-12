#pragma once
#ifndef _GUARD_H                 // Prevent multiple definitions if this 
#define _GUARD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

namespace guardNS
{
	const float SPEED = 32 * 400 * 1.25;
	const float NPC_ATTACK_RANGE = npcNS::NPC_SHOOT_RANGE;
	const float NPC_CHASE_RANGE = npcNS::NPC_CHASE_RANGE;
	const float HP = 40;
	const float MAXHP = HP;
}

class Guard : public NPC 
{
private:
	Pistol* pistol;
	TextureManager* gunTexture;
public:
	Guard();	
	~Guard();
	void ai(float frameTime, Entity & ent, float mapX, LevelController* lc);
	void draw();
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
};
#endif