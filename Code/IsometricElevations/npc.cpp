#include "npc.h"

using namespace npcNS;
#include	<list>
NPC::NPC() : Entity() {
	spriteData.x = npcNS::X;                   // location on screen
	spriteData.y = npcNS::Y;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = npcNS::NPC_ANIMATION_DELAY;
	startFrame = npcControllerNS::npcSpriteMap[sprIndex][0];     // first frame of animation
	endFrame = npcControllerNS::npcSpriteMap[sprIndex][3];     // last frame of animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	inventory = new Inventory();
	RECT e;
	e.right = npcNS::NPC_WIDTH / 2;
	e.left = -npcNS::NPC_WIDTH / 2;
	e.bottom = npcNS::NPC_HEIGHT / 2;
	e.top = -npcNS::NPC_HEIGHT / 2;
	setEdge(e);
	pathList = std::vector<VECTOR2>();
	npcHealthTexture = new TextureManager();
	npcHealthBackTexture = new TextureManager();
	gunTexture = new TextureManager();
}

NPC::~NPC() {}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc) {
	levelController = lc;
	chaseRange = npcNS::NPC_CHASE_RANGE;
	shootRange = npcNS::NPC_SHOOT_RANGE;
	pathCount = 0;
	gameptr = gamePtr;
	sprIndex = spriteNumber;
	startFrame = npcControllerNS::npcSpriteMap[sprIndex][0];
	endFrame = npcControllerNS::npcSpriteMap[sprIndex][3];
	if (!npcTexture.initialize(gamePtr->getGraphics(), TEXTURE_NPC))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing npc texture"));
	if (!npcHealthTexture->initialize(gamePtr->getGraphics(), TEXTURE_NPCHEALTH))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing npc health texture"));
	if (!npcHealthBackTexture->initialize(gamePtr->getGraphics(), TEXTURE_NPCHEALTHBACK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing npc health back texture"));
	if (!gunTexture->initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	npcHealth = new Image();
	npcHealth->initialize(gamePtr->getGraphics(), npcNS::NPC_HEALTH_WIDTH, npcNS::NPC_HEALTH_HEIGHT, 1, npcHealthTexture);
	npcHealth->setCurrentFrame(0);
	npcHealthBack = new Image();
	npcHealthBack->initialize(gamePtr->getGraphics(), npcNS::NPC_HEALTHBACK_WIDTH, npcNS::NPC_HEALTHBACK_HEIGHT, 1, npcHealthBackTexture);
	npcHealthBack->setCurrentFrame(0);
	setVelocity(VECTOR2(0, 0));
	currDest = VECTOR2(-1, -1);
	originX = getX();
	originY = getY();
	pistol = new Pistol();
	pistol->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	pistol->setCurrentFrame(gunNS::PISTOL_FRAME);
	defaultItem = new InventoryItem(pistol);
	inventory->addItem(defaultItem);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void NPC::draw() {
	Image::draw();
	npcHealthBack->draw();
	npcHealth->draw();
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (activeItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)activeItem;
		gun->draw();
	}
}

void NPC::update(float frameTime, float mapX, float pVelo, LevelController* lc) {
	OSD::instance()->addLine("NPC is at (" + std::to_string(getX()) + ", " + std::to_string(getY()) + ") | Update called with mapX: " + std::to_string(mapX));
	pVelocity = pVelo;
	offsetNew.x = mapX;
	npcHealth->setX(spriteData.x + 1);
	npcHealth->setY(spriteData.y - 19);
	RECT r = npcHealth->getSpriteDataRect();
	r.right = npcHealth->getWidth() * (hp / hpMax);
	npcHealth->setSpriteDataRect(r);
	npcHealthBack->setX(spriteData.x);
	npcHealthBack->setY(spriteData.y - 20);
	npcHealthBack->draw();
	bool flip = false;
	ai(frameTime, *this, mapX);
	switch (orientation) {
		case Right:
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][1];
			spriteData.flipHorizontal = true;
			flip = false;
			break;
		case Down:
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][2];
			break;
		case Left:
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][1];
			spriteData.flipHorizontal = false;
			flip = true;
			break;
		case Up:
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][0];
			break;
	}
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (inventory->getActiveItem()->getItem()->getItemType() == Item::Equipable) {
		Gun* gun = dynamic_cast<Gun*>(activeItem);
		if (gun != 0) {
			bool shoot = aiState == Shoot;
			gun->update(frameTime, orientation, spriteData.x, spriteData.y, input, lc, derivedDest.x, derivedDest.y, shoot);
		}
	}
	if (velocity.x < 0 && !canMoveLeft() || velocity.x > 0 && !canMoveRight())
		velocity.x = 0;
	Entity::update(frameTime);
}
void NPC::setFalling(bool f) {
	falling = f;
}
void NPC::damage(float amt) {
	hp -= amt;
	healthUpdate();
}
void NPC::damage(Weapon w) {

}
void NPC::damage() {
	hp--;
	healthUpdate();
}
void NPC::healthUpdate() {
	if (hp <= 0) {
		healthStatus = Dead;
		setDying(true);
	}
}
void NPC::die() {

}

void NPC::setDying(bool d) {
	dying = d;
}

bool NPC::isDying() {
	return dying;
}

int NPC::getHP() {
	return hp;
}

int NPC::getMaxHP() {
	return hpMax;
}

bool NPC::moveLeft(float frameTime) {
	if (!canMoveLeft())
		return false;
	orientation = Left;
	velocity.x = -npcNS::SPEED * frameTime;
	return true;
}

bool NPC::moveRight(float frameTime) {
	if (!canMoveRight())
		return false;
	orientation = Right;
	velocity.x = npcNS::SPEED * frameTime;
	return true;
}

bool NPC::moveUp(float frameTime) {
	if (!canMoveUp())
		return false;
	orientation = Up;
	velocity.y = -npcNS::JUMP_SPEED * frameTime;
	return true;
}

bool NPC::moveDown(float frameTime) {
	if (!canMoveDown())
		return false;
	orientation = Down;
	velocity.y = npcNS::JUMP_SPEED * frameTime;
	return true;
}
void NPC::setAiState(int state) {
	aiState = state;
	switch (state) {
		case Patrol:
			bool found = false;
			for (std::vector<VECTOR2>::iterator pathIt = pathList.begin(); pathIt != pathList.end(); ++pathIt) {
				if ((*pathIt).x == currDest.x && (*pathIt).y == currDest.y) {
					found = true;
					break;
				}
			}
			if (!found) {
				currDest = pathList.at(pathCount);
			}
	}
}
void NPC::ai(float frameTime, Entity &ent, float mapX) {
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
		case Shoot:
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

void NPC::addPath(VECTOR2 v) {
	pathList.push_back(v);
}

void NPC::setMapX(float x) {
	mapX -= x;
}
float NPC::getChaseRange() {
	return chaseRange;
}
float NPC::getShootRange() {
	return shootRange;
}
void NPC::setDest(VECTOR2 d) {
	currDest = d;
}
bool NPC::canMoveUp() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0, topLeft.y - 1)->isSolid() || levelController->getTile(topRight.x + levelController->getMapX() * -1.0, topRight.y - 1)->isSolid());
}
bool NPC::canMoveDown() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0, bottomLeft.y + 1)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0, bottomRight.y + 1)->isSolid());
}
bool NPC::canMoveLeft() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0 - 1, topLeft.y)->isSolid() || levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0 - 1, bottomLeft.y)->isSolid());
}
bool NPC::canMoveRight() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topRight.x + levelController->getMapX() * -1.0 + 1, topRight.y)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0 + 1, bottomRight.y)->isSolid());
}