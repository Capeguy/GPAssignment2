//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "npcController.h"

NPCController::NPCController() {}

NPCController::NPCController(Graphics *graphics, TextureManager* iconTxt, Game* gp) {
	gameptr = gp;
	npcTexture = new TextureManager();
	iconTexture = iconTxt;
	npcs = std::list<NPC*>();
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing npc texture"));
	dxFont.initialize(graphics, 14, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
};

NPC* NPCController::spawnNPCs(int level, Game *gamePtr, float x, float y, int spriteNumber, LevelController* lc, Graphics* graphics) {
	NPC* npc = new NPC();
	npc->initialize(gamePtr, npcNS::NPC_WIDTH, npcNS::NPC_HEIGHT, npcNS::TEXTURE_COLS, npcTexture, spriteNumber, lc);
	npc->setX(x);
	npc->setY(y);
	npcs.push_back(npc);
	// Create NPC Icon for minimap
	Image* npcIco = new Image();
	npcIco->initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, 2, iconTexture);
	npcIco->setCurrentFrame(0);
	npcIco->setScale(0.5);
	npcIco->setX(GAME_WIDTH*0.6);
	npcIco->setY(50);
	npcIcon.push_back(npcIco);
	return npc;
}

void NPCController::update(float frameTime, LevelController* lc) {
	int npcCount = 0;
	std::list<Image*>::iterator npcIconIter = npcIcon.begin();
	for (std::list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it)->update(frameTime, mapX, pVelocity, lc);
		int npcIconCount = 0;
		for (std::list<Image*>::iterator npcIconIter = npcIcon.begin(); npcIconIter != npcIcon.end(); npcIconIter++) {
			if (npcCount == npcIconCount) {
				(*npcIconIter)->setX(((*it)->getX()*0.120) + (GAME_WIDTH*0.60 + 5) + (-mapX*0.125));
				(*npcIconIter)->setY((*it)->getY()*0.120 + 42);
			}
			npcIconCount++;
		}
		npcCount++;
	}

}
void NPCController::render() {
	for (std::list<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it)->draw(dxFont);

	}
	for (std::list<Image*>::iterator itr = npcIcon.begin(); itr != npcIcon.end(); ++itr) {
		(*itr)->draw();
	}
}

void NPCController::collisions(LevelController* lc, Player* p) {
	D3DXVECTOR2 collisionVector = D3DXVECTOR2();
	std::list<NPC*>::iterator npcIter;
	std::list<NPC*>::iterator selectedNPC;
	std::list<Projectile*>::iterator projectileIter = lc->projectiles.begin();
	std::list<Image*>::iterator iconIter = npcIcon.begin();
	bool removed = false;
	int count = 0;
	while (!lc->projectiles.empty() && projectileIter != lc->projectiles.end()) {
		npcIter = npcs.begin();
		removed = false;
		while (!npcs.empty() && npcIter != npcs.end() && !removed) {
			if ((*projectileIter)->collidesWith(**npcIter, collisionVector) && (*projectileIter)->getOwner() == Projectile::Player) {
				//++iconIter;
				std::advance(iconIter, count);
				(*npcIter)->damage((*projectileIter)->getDamage());
				if ((*npcIter)->isDying()) {
					if ((*npcIter)->bossDefeated()) {
						bossDead = true;
					}
					p->setTotalPoints((*npcIter)->getPoints()); // Add points to player
					npcIter = npcs.erase(npcIter); // remove npc
					iconIter = npcIcon.erase(iconIter); // remove icon from minimap
				}
				projectileIter = lc->projectiles.erase(projectileIter); //remove projectile
				removed = true;
			} else {
				++npcIter;
				count++;
			}
			if (count + 1 > npcIcon.size()) {
				count = 0;
			}
		}
		if (!removed)
			++projectileIter;
	}
}

void NPCController::setMapX(float x) {
	mapX -= x;
}

void NPCController::getPlayerVelocity(float v) {
	pVelocity = v;
}

std::list<NPC*> NPCController::getNPCs() {
	return npcs;
}
void NPCController::addNPC(NPC* npc, int type, LevelController* lc, Graphics* graphics) {
	if (!npc->initialized) {
		npc->initialize(gameptr, npcNS::NPC_WIDTH, npcNS::NPC_HEIGHT, npcNS::TEXTURE_COLS, npcTexture, type, lc);
	}
	npcs.push_back(npc);
	// Create Npc Icon for minimap
	Image* npcIco = new Image();
	npcIco->initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, 5, iconTexture);
	switch (type) {
	case 4: // Agent Jack
		npcIco->setCurrentFrame(4);
		break;
	case 6: // Friendly
		npcIco->setCurrentFrame(2);
		break;
	default:
		npcIco->setCurrentFrame(0);
		break;
	}
	npcIco->setScale(0.5);
	npcIco->setX(GAME_WIDTH*0.6);
	npcIco->setY(50);
	npcIcon.push_back(npcIco);
}

bool NPCController::getBossDeathStatus() {
	return bossDead;
}
