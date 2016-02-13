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
	RECT e;
	e.right = npcNS::NPC_WIDTH / 2;
	e.left = -npcNS::NPC_WIDTH / 2;
	e.bottom = npcNS::NPC_HEIGHT / 2;
	e.top = -npcNS::NPC_HEIGHT / 2;
	setEdge(e);
	pathList = std::vector<VECTOR2>();
	npcHealthTexture = new TextureManager();
	npcHealthBackTexture = new TextureManager();
}

NPC::~NPC() {}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber, LevelController* lc) {
	levelController = lc;
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
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void NPC::draw() {
	Image::draw();
	npcHealthBack->draw();
	npcHealth->draw();
	/*
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (activeItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)activeItem;
		gun->draw();
	}
	*/
}

void NPC::draw(TextDX &dxFont) { //TextDX &dxFont
	//NPC::draw();
	Image::draw();
	npcHealthBack->draw();
	npcHealth->draw();

	//std::string buffer;
	//buffer = "kappa";
	//buffer = std::to_string((int)getX());
	//buffer += ", ";
	//buffer += std::to_string((int)getY());
	//dxFont.print(buffer, spriteData.x, spriteData.y - 16);
}
void NPC::stateChange() {
	// Start of state change
	VECTOR2 v = VECTOR2(gameptr->getPlayer()->getX(), gameptr->getPlayer()->getY());
	float y2 = v.y;
	float x2 = v.x;
	float y1 = getY();
	float x1 = getX();
	float distance = sqrt(pow(y2 - y1, 2) + (pow(x2 - x1, 2)));
	if (distance > getChaseRange()) {
		setAiState(NPC::Patrol);
	} else if (distance > getAttackRange()) {
		setAiState(NPC::Chase);
		setDest(v);
	} else {
		setAiState(NPC::Attack);
		setDest(v);
	}
	// End of state change
}

void NPC::update(float frameTime, float mapX, float pVelo, LevelController* lc) {
	// OSD::instance()->addLine("NPC is at (" + std::to_string(getX()) + ", " + std::to_string(getY()) + ") | Update called with mapX: " + std::to_string(mapX));
	stateChange();
	pVelocity = pVelo;
	offsetNew.x = mapX;
	renderHealthbar();
	bool flip = false;
	ai(frameTime, *this, mapX, lc);
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

void NPC::renderHealthbar()
{
	npcHealth->setX(spriteData.x + 2 * getScale());
	npcHealth->setY(spriteData.y - 19);
	RECT r = npcHealth->getSpriteDataRect();
	r.right = npcHealth->getWidth() * (hp / hpMax);
	npcHealth->setSpriteDataRect(r);
	npcHealthBack->setX(spriteData.x);
	npcHealthBack->setY(spriteData.y - 20);
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
float NPC::getAttackRange() {
	return attackRange;
}
void NPC::setDest(VECTOR2 d) {
	currDest = d;
}
bool NPC::canMoveUp() {
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0, topLeft.y - 1)->isSolid() || levelController->getTile(topRight.x + levelController->getMapX() * -1.0, topRight.y - 1)->isSolid());
}
bool NPC::canMoveDown() {
	return !(levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0, bottomLeft.y + 1)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0, bottomRight.y + 1)->isSolid());
}
bool NPC::canMoveLeft() {
	return (!(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0 - 1, topLeft.y)->isSolid() || levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0 - 1, bottomLeft.y)->isSolid())) && (levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0, bottomLeft.y + 1)->isSolid());
}
bool NPC::canMoveRight() {
	return (!(levelController->getTile(topRight.x + levelController->getMapX() * -1.0 + 1, topRight.y)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0 + 1, bottomRight.y)->isSolid())) && (levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0, bottomRight.y + 1)->isSolid());
}