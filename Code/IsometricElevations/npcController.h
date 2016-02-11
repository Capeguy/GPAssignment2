#pragma once
#ifndef _NPCCONTROLLER_H                 // Prevent multiple definitions if this 
#define _NPCCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "npc.h"
#include "entity.h"
#include "player.h"
#include <vector>

using namespace std;
class NPC;
class LevelController;
namespace npcControllerNS
{
	const int npcSpriteQty = 8;
	const int npcSpriteOrientationQty = 4;
	const int npcSpriteMap[npcSpriteQty][npcSpriteOrientationQty] = {
		568, 569, 570, 571,
		504, 505, 506, 507,
		472, 473, 474, 475,
		312, 313, 314, 315,
		856, 857, 858, 859, 
		408, 409, 410, 411,
		344, 345, 346, 347,
		376, 377, 378, 379
	};

	const string npcSpriteNameList[npcSpriteQty] = {
		"Black Police",
		"White Police",
		"Armoured Police",
		"Firefighter",
		"Prisoner Jack",
		"My Name is Dog",
		"Medic",
		"Doctor"
	};
}

class NPCController
{
private:
	TextureManager* npcTexture;
	TextureManager* iconTexture;
	list<NPC*> npcs;
	list<Image*> npcIcon;
	list<VECTOR2> NPCSpawnLoc;
	float mapX = 0;
	float pVelocity = 0;
public:
	NPCController();
	NPCController(Graphics*, TextureManager*);
	NPC* spawnNPCs(int, Game*, float, float, int, LevelController*, Graphics*);
	void update(float, LevelController*);
	void render();
	void collisions(LevelController*);
	void setMapX(float x);
	void addSpawnLoc(float x, float y);
	void removeSpawnLoc(int);
	void getPlayerVelocity(float v);
	void chaseIfInRange(VECTOR2);
	list<NPC*> getNPCs();

};
#endif
