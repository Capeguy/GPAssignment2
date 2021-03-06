//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _DOG_H                 // Prevent multiple definitions if this 
#define _DOG_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

namespace dogNS {
	const float SPEED = 32 * 400 * 1.25;
	const float NPC_ATTACK_RANGE = 16;
	const float NPC_CHASE_RANGE = 32.0 * 5;
	const float HP = 10;
	const float MAXHP = HP;
	const int POINT = 20;
}
class Dog : public NPC
{
private:
	float	biteDamage = 2;
	float	cooldown = 0.4f;
	float	cooldownCurrent = 0;
public:
	Dog();
	~Dog();
	void ai(float frameTime, Entity & ent, float mapX, LevelController* lc);
	void draw(TextDX&);
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
	bool moveLeft(float frameTime);
	bool moveRight(float frameTime);
	void bite(float frameTime);
};
#endif