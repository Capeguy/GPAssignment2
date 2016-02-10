#include "npc.h"

using namespace std;
using namespace npcNS;
#include	<list>
NPC::NPC() : Entity() {
	//spriteData.width = playerNS::WIDTH;           // size of player ship
	//spriteData.height = playerNS::HEIGHT;
	spriteData.x = npcNS::X;                   // location on screen
	spriteData.y = npcNS::Y;
	//spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	//spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = npcNS::NPC_ANIMATION_DELAY;
	//startFrame = -1; //npcNS::NPC_START_FRAME;     // first frame of ship animation
	//endFrame = -1; // npcNS::NPC_END_FRAME;     // last frame of ship animation
	startFrame = npcControllerNS::npcSpriteMap[sprIndex][0];     // first frame of ship animation
	endFrame = npcControllerNS::npcSpriteMap[sprIndex][3];     // last frame of ship animation
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
	pathList = vector<VECTOR2>();

	npcHealthTexture = new TextureManager();
	npcHealthBackTexture = new TextureManager();
	gunTexture = new TextureManager();
}

NPC::~NPC() {}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber) {
	chaseRange = npcNS::NPC_CHASE_RANGE;
	shootRange = npcNS::NPC_SHOOT_RANGE;
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

	if (!gunTexture->initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));

	pistol = new Pistol();
	pistol->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	pistol->setCurrentFrame(gunNS::PISTOL_FRAME);

	defaultItem = new InventoryItem(pistol);
	inventory->addItem(defaultItem);

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void NPC::draw() {
	Image::draw();              // draw ship
	npcHealthBack->draw();
	npcHealth->draw();
	

	Item* activeItem = inventory->getActiveItem()->getItem();
	if (activeItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)activeItem;
		gun->draw();
	}
}

void NPC::update(float frameTime, float mapX, float pVelo, LevelController* lc) {
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
	OSD::instance()->addLine("NPC is at (" + to_string(getX()) + ", " + to_string(getY()) + ") | Update called with mapX: " + to_string(mapX));
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
	// TO DO: Die (HP <= 0)
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

void NPC::moveLeft(float frameTime) {
	orientation = Left;
	velocity.x = -npcNS::SPEED * frameTime;
	/*
	if (pVelocity < 0)
		setVelocity(VECTOR2(-npcNS::SPEED * (frameTime / 2), 0));
	else if (pVelocity > 0)
		setVelocity(VECTOR2(-npcNS::SPEED * 2 * frameTime, 0));
	else
		setVelocity(VECTOR2(-npcNS::SPEED * frameTime, 0));
	*/
}

void NPC::moveRight(float frameTime) {
	orientation = Right;
	velocity.x = npcNS::SPEED * frameTime;
	/*
	if (pVelocity > 0)
		setVelocity(VECTOR2(npcNS::SPEED * (frameTime / 2), 0));
	else if (pVelocity < 0)
		setVelocity(VECTOR2(npcNS::SPEED * frameTime * 2, 0));
	else
		setVelocity(VECTOR2(npcNS::SPEED * frameTime, 0));
	*/
}

void NPC::moveUp(float frameTime) {
	orientation = Up;
	velocity.y = -npcNS::JUMP_SPEED * frameTime;
}

void NPC::moveDown(float frameTime) {
	orientation = Down;
	velocity.y = npcNS::JUMP_SPEED * frameTime;
}
void NPC::setAiState(int state) {
	aiState = state;
	switch (state) {
	case Patrol:
		bool found = false;
		for (vector<VECTOR2>::iterator pathIt = pathList.begin(); pathIt != pathList.end(); ++pathIt) {
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
	if (currDest != VECTOR2(-1, -1)) {
		derivedDest = VECTOR2(currDest.x + offsetOld.x, currDest.y + offsetOld.y);
	}
	// derivedDest.y = spriteData.y; // Because we're not gonna climb mountains to chase Player
	switch (aiState) {
	case Patrol:
	case Chase:
		if (pathList.size() == 0)
			return;
		if (currDest == VECTOR2(-1, -1) || spriteData.x == derivedDest.x) { // && spriteData.y == derivedDest.y) { // No destination
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
				moveLeft(frameTime);
			}
		} else if (spriteData.x < derivedDest.x) {
			if (velocity.x < 0 && derivedDest.x - spriteData.x < 1) {
				velocity.x = 0;
				setX(derivedDest.x);
			} else {
				orientation = Right;
				moveRight(frameTime);
			}
		} else {
			velocity.x = 0;
		}
		/* I probably shouldn't need to go up and down
		if (spriteData.y > derivedDest.y) {
			if (velocity.y > 0 && spriteData.y - derivedDest.y < 1) {
				velocity.y = 0;
				setY(derivedDest.y);
			} else {
				orientation = Down;
				moveUp(frameTime);
			}
		} else if (spriteData.y < derivedDest.y) {
			if (velocity.y < 0 && derivedDest.y - spriteData.y < 1) {
				velocity.y = 0;
				setY(derivedDest.y);
			} else {
				orientation = Up;
				moveDown(frameTime);
			}
		} else {
			velocity.y = 0;
		}
		*/
		//setY(derivedDest.y);
		/*
		if (spriteData.y > currDest.y) {
		if (orientation == Down) {
		velocity.y = 0;
		setY(currDest.y);
		} else {
		orientation = Up;
		moveUp(frameTime);
		}
		} else if (spriteData.y < currDest.y) {
		if (orientation == Up) {
		velocity.y = 0;
		setY(currDest.y);
		} else {
		orientation = Down;
		moveDown(frameTime);
		}
		} else {
		velocity.y = 0;
		}
		*/
		break;
	case Shoot:
		velocity = VECTOR2(0, 0);
		VECTOR2 delta = VECTOR2(derivedDest.x - getX(), 0);
		if (delta.x < 0)
			orientation = Left;
		else if (delta.x > 0)
			orientation = Right;
		else
			orientation = Up;
		break;
	}
	
	OSD::instance()->addLine("MapX: " + to_string(mapX));
	OSD::instance()->addLine("NPC AI (" + to_string(aiState) + ") at (" + to_string(spriteData.x) + ", " + to_string(spriteData.y) + ") going to (" + to_string((derivedDest.x)) + ", " + to_string(derivedDest.y) + ") Moving at: (" + to_string((velocity.x)) + ", " + to_string(velocity.y) + ") ");
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