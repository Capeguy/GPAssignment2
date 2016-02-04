#pragma once
#ifndef _NPCCONTROLLER_H                 // Prevent multiple definitions if this 
#define _NPCCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "npc.h"
#include "entity.h"
#include <vector>
using namespace std;
namespace npcControllerNS
{
}

class NPCController
{
private:
	TextureManager* npcTexture;
	list<NPC*> npcs;
	list<VECTOR2> NPCSpawnLoc;
	float mapX = 0;
public:
	NPCController();
	NPCController(Graphics*);
	NPC* spawnNPCs(int, Game*, float, float);
	void update(float);
	void render();
	void collisions(LevelController*);
	void setMapX(float x);
	void addSpawnLoc(float x, float y);
	void removeSpawnLoc(int);
};
#endif