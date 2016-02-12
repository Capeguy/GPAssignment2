#pragma once
#ifndef _WARDEN_H                 // Prevent multiple definitions if this 
#define _WARDEN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

namespace wardenNS
{
	const float SPEED = 32 * 400;
	const float NPC_ATTACK_RANGE = 1000;
	const float NPC_CHASE_RANGE = 500;
	const float HP = 1000;
	const float MAXHP = HP;
}
class Warden : public NPC
{
private:
	int point = 1000;
	float cooldown = 0.4f;
	float cooldownCurrent = 0;
	BossGun* gun;
	TextureManager* gunTexture;
public:
	Warden();
	~Warden();
	void ai(float frameTime, Entity & ent, float mapX, LevelController* lc);
	void draw();
	void update(float frameTime, float mapX, float pVelo, LevelController* lc);
	int	 getPoints();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc);
	bool moveLeft(float frameTime);
	bool moveRight(float frameTime);
	void renderHealthbar();
};
#endif