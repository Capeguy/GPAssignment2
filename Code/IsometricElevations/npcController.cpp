#include "npcController.h"

NPCController::NPCController() {}

NPCController::NPCController(Graphics *graphics) {
	// item texture initialize
	npcTexture = new TextureManager();
	//npcs = list<Entity*>();
	if (!npcTexture->initialize(graphics, TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
};

void NPCController::spawnNPCs(int level, Game *gamePtr) {
	NPC* npc = new NPC();
	npc->initialize(gamePtr, npcNS::NPC_WIDTH, npcNS::NPC_HEIGHT, npcNS::TEXTURE_COLS, npcTexture);
	npc->setX(GAME_WIDTH / 2);
	npc->setY(GAME_HEIGHT / 2);
}

void NPCController::update(float frameTime) {}
void NPCController::render() {}
void NPCController::collisions() {}