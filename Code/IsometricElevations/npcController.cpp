#include "npcController.h"

NPCController::NPCController() {}

NPCController::NPCController(Graphics *graphics) {
	// item texture initialize
	npcTexture = new TextureManager();
	npcs = list<NPC*>();
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
};

NPC* NPCController::spawnNPCs(int level, Game *gamePtr, float x, float y) {
	NPC* npc = new NPC();
	npc->initialize(gamePtr, npcNS::NPC_WIDTH, npcNS::NPC_HEIGHT, npcNS::TEXTURE_COLS, npcTexture);
	npc->setX(x);
	npc->setY(y);
	npcs.push_back(npc);
	return npc;
}

void NPCController::update(float frameTime) {
	for (list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it)->update(frameTime);
	}
}
void NPCController::render() {
	for (list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it)->draw();
	}
}
void NPCController::collisions(LevelController* lc) {
	D3DXVECTOR2 collisionVector = D3DXVECTOR2();
	//list<Crate*>* crateList = iController->getCrateList();
	list<NPC*>::iterator npcIter;
	list<NPC*>::iterator selectedNPC;
	list<Projectile*>::iterator projectileIter = lc->projectiles.begin(); //how to get projectiles from whereever
	//NPC** selectedNPC;
	bool removed = false;
	while (!lc->projectiles.empty() && projectileIter != lc->projectiles.end()) {
		npcIter = npcs.begin();
		removed = false;
		while (!npcs.empty() && npcIter != npcs.end() && !removed) {
			if ((*projectileIter)->collidesWith(**npcIter, collisionVector)) {
				// TODO: Handle health reduction & check if health < 0
				// health reduction code
								
				(*npcIter)->damage(1);
				//(*npcIter)->healthUpdate();
				if((*npcIter)->isDying())
				{ 
					npcIter = npcs.erase(npcIter); // remove npc
				}
				projectileIter = lc->projectiles.erase(projectileIter); //remove projectile
				removed = true;
			}
			else {
				++npcIter;
			}
		}
		if (!removed)
			++projectileIter;
	}
}