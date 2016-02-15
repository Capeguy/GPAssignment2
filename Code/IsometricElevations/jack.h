//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _JACK_H                 // Prevent multiple definitions if this 
#define _JACK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

namespace JackNS {
	const float HEAL_SPEED = 10;
	const float SPEED = 32 * 400;
	const float NPC_ATTACK_RANGE = 64;
	const float NPC_CHASE_RANGE = 32 * 100;
}
class Jack : public NPC
{
public:
	Jack();
	Jack(Graphics*& g);
	void ai(float frameTime, Entity & ent, float mapX, LevelController* lc);
	void draw(TextDX&); //TextDX&
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
	void stateChange();
	~Jack();
private:
	TextDX dxFont;
};
#endif