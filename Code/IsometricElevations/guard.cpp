//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "guard.h"

Guard::Guard() : NPC() {
	chaseRange = npcNS::NPC_CHASE_RANGE;
	attackRange = npcNS::NPC_SHOOT_RANGE;
	hp = guardNS::HP;
	hpMax = guardNS::MAXHP;
	pistol = new Pistol();
	pistol->setCooldown(0.3f);
	gunTexture = new TextureManager();
	points = guardNS::POINT;
}

Guard::~Guard() {}

void Guard::ai(float frameTime, Entity &ent, float mapX, LevelController* lc) {
	OSD::instance()->addLine("AI Can | Left: " + std::to_string(canMoveLeft()) + " | Right: " + std::to_string(canMoveRight()) + " | Up: " + std::to_string(canMoveUp()) + " | Down: " + std::to_string(canMoveDown()));
	// derivedDest.y = spriteData.y; // Because we're not gonna climb mountains to chase Player
	switch (aiState) {
	case Patrol:
		if (currDest != VECTOR2(-1, -1)) {
			derivedDest = VECTOR2(currDest.x + offsetOld.x, currDest.y + offsetOld.y);
		}
		if (!canMoveLeft() && !canMoveRight() && !canMoveUp() && !canMoveDown()) {
			setX(derivedDest.x);
			setY(derivedDest.y);
		}
		if (pathList.size() == 0)
			return;
		if (currDest == VECTOR2(-1, -1) || spriteData.x == derivedDest.x) {
			pathCount++;
			if (pathCount >= pathList.size())
				pathCount = 0;
			currDest = pathList.at(pathCount);
		}
		if (spriteData.x > derivedDest.x) {
			if (velocity.x > 0 && spriteData.x - derivedDest.x < 1 && canMoveLeft()) {
				velocity.x = 0;
				setX(derivedDest.x);
			} else {
				orientation = Left;
				if (!moveLeft(frameTime)) {
					currDest = VECTOR2(-1, -1);
				}
			}
		} else if (spriteData.x < derivedDest.x) {
			if (velocity.x < 0 && derivedDest.x - spriteData.x < 1 && canMoveRight()) {
				velocity.x = 0;
				setX(derivedDest.x);
			} else {
				orientation = Right;
				if (!moveRight(frameTime)) {
					currDest = VECTOR2(-1, -1);
				}
			}
		} else {
			velocity.x = 0;
		}
		break;
	case Chase:
		if (currDest != VECTOR2(-1, -1)) {
			derivedDest = VECTOR2(currDest.x, currDest.y);
		}
		if (pathList.size() == 0)
			return;
		if (currDest == VECTOR2(-1, -1) || spriteData.x == derivedDest.x) {
			pathCount++;
			if (pathCount >= pathList.size())
				pathCount = 0;
			currDest = pathList.at(pathCount);
		}
		if (spriteData.x > derivedDest.x) {
			if (velocity.x > 0 && spriteData.x - derivedDest.x < 1) {
				velocity.x = 0;
				setX(derivedDest.x);
			} else {
				orientation = Left;
				if (!moveLeft(frameTime)) {
					currDest = VECTOR2(-1, -1);
					setAiState(Patrol);
				}
			}
		} else if (spriteData.x < derivedDest.x) {
			if (velocity.x < 0 && derivedDest.x - spriteData.x < 1) {
				velocity.x = 0;
				setX(derivedDest.x);
			} else {
				orientation = Right;
				if (!moveRight(frameTime)) {
					currDest = VECTOR2(-1, -1);
					setAiState(Patrol);
				}
			}
		} else {
			velocity.x = 0;
		}
		break;
	case Attack:
		velocity = VECTOR2(0, 0);
		if (currDest != VECTOR2(-1, -1)) {
			derivedDest = VECTOR2(currDest.x, currDest.y);
		}
		//OSD::instance()->addLine("NPC Shoot Orientation: " + std::to_string(derivedDest.x - getX()) + " (" + std::to_string((int)(derivedDest.x)) + " - " + std::to_string((int)getX()) + ")");
		VECTOR2 delta = VECTOR2(derivedDest.x - getX(), 0);
		if (delta.x < 0)
			orientation = Left;
		else if (delta.x > 0)
			orientation = Right;
		else
			orientation = Up;
		break;
	}
	pistol->update(frameTime, orientation, spriteData.x, spriteData.y, input, lc, derivedDest.x, derivedDest.y, aiState == Attack);
	//OSD::instance()->addLine("MapX: " + std::to_string(mapX));
	//OSD::instance()->addLine("NPC AI (" + std::to_string(aiState) + ") at (" + std::to_string(spriteData.x) + ", " + std::to_string(spriteData.y) + ") going to (" + std::to_string((derivedDest.x)) + ", " + std::to_string(derivedDest.y) + ") Moving at: (" + std::to_string((velocity.x)) + ", " + std::to_string(velocity.y) + ") ");
}

void Guard::draw(TextDX &dxFont) {
	NPC::draw(dxFont);
	pistol->draw();
}

void Guard::update(float frameTime, float mapX, float pVelo, LevelController * lc) {
	NPC::update(frameTime, mapX, pVelo, lc);
}


bool Guard::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM, int spriteNumber, LevelController * lc) {
	if (!gunTexture->initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	pistol->initialize(gamePtr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	pistol->setCurrentFrame(gunNS::PISTOL_FRAME);
	return NPC::initialize(gamePtr, width, height, ncols, textureM, spriteNumber, lc);
}
