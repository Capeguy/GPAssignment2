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
void NPCController::collisions() {}