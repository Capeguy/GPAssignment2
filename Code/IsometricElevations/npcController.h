#pragma once
#ifndef _NPCCONTROLLER_H                 // Prevent multiple definitions if this 
#define _NPCCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
class NPC;
class Guard;
#include "entity.h"
#include "player.h"
#include <vector>
#include "npc.h"
class LevelController;
namespace npcControllerNS
{
	const int npcSpriteQty = 9;
	const int npcSpriteOrientationQty = 4;
	const int npcSpriteMap[npcSpriteQty][npcSpriteOrientationQty] = {
		568, 569, 570, 571,
		504, 505, 506, 507,
		472, 473, 474, 475,
		312, 313, 314, 315,
		856, 857, 858, 859, 
		408, 409, 410, 411,
		344, 345, 346, 347,
		376, 377, 378, 379,
		760, 761, 762, 763
	};

	const std::string npcSpriteNameList[npcSpriteQty] = {
		"Black Police",
		"White Police",
		"Armoured Police",
		"Firefighter",
		"Prisoner Jack",
		"My Name is Dog",
		"Medic",
		"Doctor",
		"Warden"
	};
}

class NPCController
{
private:
	Game* gameptr;
	TextureManager* npcTexture;
	TextureManager* iconTexture;
	std::list<NPC*> npcs;
	std::list<Image*> npcIcon;
	float mapX = 0;
	float pVelocity = 0;
	int totalPoints = 0;
public:
	NPCController();
	NPCController(Graphics*, TextureManager*, Game*);
	NPC* spawnNPCs(int, Game*, float, float, int, LevelController*, Graphics*);
	void update(float, LevelController*);
	void render();
	void collisions(LevelController*, Player* p);
	void setMapX(float x);
	void getPlayerVelocity(float v);
	void chaseIfInRange(VECTOR2);
	std::list<NPC*> getNPCs();
	void addNPC(NPC* npc, int type, LevelController* lc, Graphics* graphics);

};
#endif
