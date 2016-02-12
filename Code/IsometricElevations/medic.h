#pragma once
#ifndef _MEDIC_H                 // Prevent multiple definitions if this 
#define _MEDIC_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

namespace MedicNS {
	const float HEAL_SPEED = 10;
}
class Medic : public NPC 
{
public:
	Medic();
	void ai(float frameTime, Entity & ent, float mapX);
	void draw();
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
	~Medic();
};
#endif