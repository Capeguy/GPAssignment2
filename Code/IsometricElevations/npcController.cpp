#include "npcController.h"

NPCController::NPCController()
{
}

NPCController::NPCController(Graphics *graphics)
{
	// item texture initialize
	npcTexture = new TextureManager();
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	//crateList = vector<Crate*>();
	//levelCrateLoc[0].push_back(VECTOR2(321, 508));
	//levelCrateLoc[0].push_back(VECTOR2(652, 704));
};

void NPCController::spawnNPCs(int level, Game *gamePtr)
{	
	/*
	vector<VECTOR2> crateLoc = levelCrateLoc[level - 1];
	for (int i = 0; i < crateLoc.size(); i++)
	{
		Crate* c = new Crate();
		c->initialize(gamePtr, itemTexture);
		c->setX(crateLoc.at(i).x);
		c->setY(crateLoc.at(i).y);
		crateList.push_back(c);
	}
	*/
}

void NPCController::update(float frameTime)
{
	/*
	for (int i = 0; i < crateList.size(); i++)
	{
		crateList.at(i)->update(frameTime);
	}
	*/
}

void NPCController::render()
{
	/*
	for (int i = 0; i < crateList.size(); i++)
	{
		Crate* c = crateList.at(i);
		c->draw();
	}
	*/
}

