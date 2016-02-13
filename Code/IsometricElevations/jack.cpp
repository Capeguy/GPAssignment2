#include "jack.h"

Jack::Jack() {
}
Jack::Jack(Graphics*& graphics) {
	chaseRange = JackNS::NPC_CHASE_RANGE;
	attackRange = JackNS::NPC_ATTACK_RANGE;

	//dxFont.initialize(graphics, 12, false, false, "Courier New");
	//dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
}

void Jack::stateChange() {
	// Start of state change
	VECTOR2 v = VECTOR2(gameptr->getPlayer()->getX(), gameptr->getPlayer()->getY());
	float y2 = v.y;
	float x2 = v.x;
	float y1 = getY();
	float x1 = getX();
	float distance = sqrt(pow(y2 - y1, 2) + (pow(x2 - x1, 2)));
	if (distance < getAttackRange()) {
		setAiState(NPC::Attack); // Jump up and down
		setDest(v);
	}
	// End of state change
}

void Jack::ai(float frameTime, Entity & ent, float mapX, LevelController* lc) {
	OSD::instance()->addLine("AI Can | Left: " + std::to_string(canMoveLeft()) + " | Right: " + std::to_string(canMoveRight()) + " | Up: " + std::to_string(canMoveUp()) + " | Down: " + std::to_string(canMoveDown()));
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
			derivedDest = VECTOR2(gameptr->getPlayer()->getX(), gameptr->getPlayer()->getY());
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
	//OSD::instance()->addLine("MapX: " + std::to_string(mapX));
	//OSD::instance()->addLine("NPC AI (" + std::to_string(aiState) + ") at (" + std::to_string(spriteData.x) + ", " + std::to_string(spriteData.y) + ") going to (" + std::to_string((derivedDest.x)) + ", " + std::to_string(derivedDest.y) + ") Moving at: (" + std::to_string((velocity.x)) + ", " + std::to_string(velocity.y) + ") ");

}

void Jack::draw(TextDX &dxFont) { //TextDX &dxFont
	std::string buffer;
	buffer = "SAVE ME PLEASE!";
	dxFont.print(buffer, spriteData.x, spriteData.y - 43);
	NPC::draw(dxFont);

	
}

void Jack::update(float frameTime, float mapX, float pVelo, LevelController * lc) {
	NPC::update(frameTime, mapX, pVelo, lc);
}

bool Jack::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM, int spriteNumber, LevelController * lc) {
	return NPC::initialize(gamePtr, width, height, ncols, textureM, spriteNumber, lc);
}

Jack::~Jack() {}