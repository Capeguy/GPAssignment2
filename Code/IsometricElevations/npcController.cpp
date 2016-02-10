#include "npcController.h"

NPCController::NPCController() {}

NPCController::NPCController(Graphics *graphics) {
	// item texture initialize
	npcTexture = new TextureManager();
	npcs = list<NPC*>();
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
};

NPC* NPCController::spawnNPCs(int level, Game *gamePtr, float x, float y, int spriteNumber) {
	NPC* npc = new NPC();
	npc->initialize(gamePtr, npcNS::NPC_WIDTH, npcNS::NPC_HEIGHT, npcNS::TEXTURE_COLS, npcTexture, spriteNumber);
	npc->setX(x);
	npc->setY(y);
	npcs.push_back(npc);
	return npc;
}

void NPCController::update(float frameTime, LevelController* lc) {
	for (list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it)->update(frameTime, mapX, pVelocity, lc);
	}
}
void NPCController::render() {
	//int count = 0;
	//list<VECTOR2>::iterator l_front = NPCSpawnLoc.begin();
	for (list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		//std::advance(l_front, count);
		//(*it)->setX(float((*l_front).x + mapX));
		(*it)->draw();
		//count++;
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
			if ((*projectileIter)->collidesWith(**npcIter, collisionVector) && (*projectileIter)->getOwner() == Projectile::Player) {
				// TODO: Handle health reduction & check if health < 0
				// health reduction code

				(*npcIter)->damage((*projectileIter)->getDamage());
				//(*npcIter)->healthUpdate();
				if ((*npcIter)->isDying()) {
					npcIter = npcs.erase(npcIter); // remove npc
				}
				projectileIter = lc->projectiles.erase(projectileIter); //remove projectile
				removed = true;
			} else {
				++npcIter;
			}
		}
		if (!removed)
			++projectileIter;
	}
}

void NPCController::setMapX(float x) {
	mapX -= x;
}

void NPCController::addSpawnLoc(float x, float y) {
	NPCSpawnLoc.push_back(VECTOR2(x, y));
}

void NPCController::getPlayerVelocity(float v) {
	pVelocity = v;
}

void NPCController::chaseIfInRange(VECTOR2 v) {
	for (list<NPC*>::iterator npcIt = npcs.begin(); npcIt != npcs.end(); ++npcIt) {
		float y2 = v.y;
		float x2 = v.x;
		float y1 = (*npcIt)->getY();
		float x1 = (*npcIt)->getX();
		float distance = sqrt(pow(y2 - y1, 2) + (pow(x2 - x1, 2)));
		if (distance > (*npcIt)->getChaseRange()) {
			(*npcIt)->setAiState(NPC::Patrol); 
		} else if (distance > (*npcIt)->getShootRange()) {
			(*npcIt)->setAiState(NPC::Chase);
			(*npcIt)->setDest(v);
		} else {
			(*npcIt)->setAiState(NPC::Shoot);
			(*npcIt)->setDest(v);
		}
	}
}
