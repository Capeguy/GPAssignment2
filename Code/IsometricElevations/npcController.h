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

class NPCController: public Entity
{
private:
	//vector<VECTOR2> levelCrateLoc[NUM_LEVEL];
	//vector<Crate*> crateList;
	TextureManager* npcTexture;
public:
	NPCController();
	NPCController(Graphics*);
	void spawnNPCs(int, Game*);
	void update(float);
	void render();
	//void collisions();
};
#endif