#include "dog.h"

Dog::Dog() : NPC() 
{
	attackRange = dogNS::NPC_ATTACK_RANGE;
	chaseRange = dogNS::NPC_CHASE_RANGE;
	hp = dogNS::HP;
	hpMax = dogNS::MAXHP;
}

void Dog::ai(float frameTime, Entity & ent, float mapX, LevelController* lc)
{
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
			}
			else {
				orientation = Left;
				if (!moveLeft(frameTime)) {
					currDest = VECTOR2(-1, -1);
				}
			}
		}
		else if (spriteData.x < derivedDest.x) {
			if (velocity.x < 0 && derivedDest.x - spriteData.x < 1 && canMoveRight()) {
				velocity.x = 0;
				setX(derivedDest.x);
			}
			else {
				orientation = Right;
				if (!moveRight(frameTime)) {
					currDest = VECTOR2(-1, -1);
				}
			}
		}
		else {
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
			}
			else {
				orientation = Left;
				if (!moveLeft(frameTime)) {
					currDest = VECTOR2(-1, -1);
					setAiState(Patrol);
				}
			}
		}
		else if (spriteData.x < derivedDest.x) {
			if (velocity.x < 0 && derivedDest.x - spriteData.x < 1) {
				velocity.x = 0;
				setX(derivedDest.x);
			}
			else {
				orientation = Right;
				if (!moveRight(frameTime)) {
					currDest = VECTOR2(-1, -1);
					setAiState(Patrol);
				}
			}
		}
		else {
			velocity.x = 0;
		}
		break;
	case Attack:
		velocity = VECTOR2(0, 0);
		if (currDest != VECTOR2(-1, -1)) {
			derivedDest = VECTOR2(currDest.x, currDest.y);
		}
		OSD::instance()->addLine("NPC Shoot Orientation: " + std::to_string(derivedDest.x - getX()) + " (" + std::to_string((int)(derivedDest.x)) + " - " + std::to_string((int)getX()) + ")");
		VECTOR2 delta = VECTOR2(derivedDest.x - getX(), 0);
		if (delta.x < 0)
			orientation = Left;
		else if (delta.x > 0)
			orientation = Right;
		else
			orientation = Up;
		break;
	}
	OSD::instance()->addLine("MapX: " + std::to_string(mapX));
	OSD::instance()->addLine("NPC AI (" + std::to_string(aiState) + ") at (" + std::to_string(spriteData.x) + ", " + std::to_string(spriteData.y) + ") going to (" + std::to_string((derivedDest.x)) + ", " + std::to_string(derivedDest.y) + ") Moving at: (" + std::to_string((velocity.x)) + ", " + std::to_string(velocity.y) + ") ");

}

void Dog::draw()
{
	NPC::draw();
}

void Dog::update(float frameTime, float mapX, float pVelo, LevelController * lc)
{
	if (aiState == Attack)
		bite();
	NPC::update(frameTime, mapX, pVelo, lc);
}

bool Dog::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM, int spriteNumber, LevelController * lc)
{
	return NPC::initialize(gamePtr, width, height, ncols, textureM, spriteNumber, lc);
}

bool Dog::moveLeft(float frameTime)
{
	if (!canMoveLeft())
		return false;
	orientation = Left;
	velocity.x = -dogNS::SPEED * frameTime;
	return true;
}

bool Dog::moveRight(float frameTime)
{
	if (!canMoveRight())
		return false;
	orientation = Right;
	velocity.x = dogNS::SPEED * frameTime;
	return true;
}

void Dog::bite()
{

}

Dog::~Dog() {}