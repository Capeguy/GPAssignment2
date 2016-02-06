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
	startFrame = npcNS::NPC_START_FRAME;     // first frame of ship animation
	endFrame = npcNS::NPC_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	inventory = Inventory();

	RECT e;
	e.right = npcNS::NPC_WIDTH / 2;
	e.left = -npcNS::NPC_WIDTH / 2;
	e.bottom = npcNS::NPC_HEIGHT / 2;
	e.top = -npcNS::NPC_HEIGHT / 2;
	setEdge(e);
	pathList = vector<VECTOR2>();

	npcHealthTexture = new TextureManager();
	npcHealthBackTexture = new TextureManager();
}

NPC::~NPC() {
}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	gameptr = gamePtr;
	//spriteNumber = spriteNo;
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

	currDest = VECTOR2(-1, -1);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void NPC::draw() {

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
	npcHealth->draw();
	npcHealthBack->draw();
	pistol.draw();
}
void NPC::update(float frameTime) {//, LevelController* lc) {
	RECT r;
	npcHealthBack->setX(spriteData.x);
	npcHealthBack->setY(spriteData.y - 20);
	npcHealthBack->draw();
	npcHealth->setX(spriteData.x + 1);
	npcHealth->setY(spriteData.y - 21);
	r = npcHealth->getSpriteDataRect();
	r.right = npcHealth->getWidth() * (hp/hpMax);
	npcHealth->setSpriteDataRect(r);

	ai(frameTime, *this);
	/*
	Tile* leftTile = lc->getTile(bottomLeft.x, bottomLeft.y + 1);
	Tile* rightTile = lc->getTile(bottomRight.x, bottomRight.y + 1);
	if (leftTile->isSolid() || rightTile->isSolid()) {
		if (!input->isKeyDown(NPC_UP) && !input->isKeyDown(NPC_JUMP))
			canJump = true;
		canFall = false;
		falling = false;
	} else {
		canFall;
		falling = true;
	}
	if (input->isKeyDown(NPC_RIGHT) && canMoveRight) {
		spriteData.x += frameTime * npcNS::SPEED;
		while (lc->getTile(spriteData.x + 31, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y + 31)->isSolid()) {
			spriteData.x -= frameTime * npcNS::FALLING_SPEED;
		}
		orientation = Right;
	}
	if (input->isKeyDown(NPC_LEFT) && canMoveLeft) {
		spriteData.x -= frameTime * npcNS::SPEED;
		while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x, spriteData.y + 31)->isSolid()) {
			spriteData.x += frameTime * npcNS::FALLING_SPEED;
		}
		orientation = Left;
	}
	if (jumping || ((input->isKeyDown(NPC_JUMP) || input->isKeyDown(NPC_UP)) && canMoveUp && canJump)) {
		if (!jumping && canJump)
			jumpdistance = 0;
		if (jumpdistance > npcNS::JUMP_HEIGHT) {
			jumping = false;
			canJump = false;
			falling = true;
		} else {
			jumping = true;
			canJump = false;
			jumpdistance += frameTime * npcNS::JUMP_SPEED;
			spriteData.y -= frameTime * npcNS::JUMP_SPEED;
			while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y)->isSolid()) {
				spriteData.y += frameTime * npcNS::FALLING_SPEED;
			}
			orientation = Up;
		}
	}
	if (falling && !jumping) {
		Tile* tileA = lc->getTile(bottomLeft.x, bottomLeft.y + 1);
		Tile* tileB = lc->getTile(bottomRight.x, bottomRight.y + 1);
		if (!tileA->isSolid() && !tileB->isSolid()) {
			spriteData.y += frameTime * npcNS::FALLING_SPEED; // Use trajectory
		}
		tileA = lc->getTile(bottomLeft.x, bottomLeft.y + 1);
		tileB = lc->getTile(bottomRight.x, bottomRight.y + 1);
		while (tileA->isSolid() || tileB->isSolid()) {
			spriteData.y--;
		}
	}
	*/
	switch (orientation) {
		case Right:
			currentFrame = 569;
			//currentFrame = npcControllerNS::npcSpriteMap[4][spriteNo]
			spriteData.flipHorizontal = true;
			break;
		case Down:
			currentFrame = 570;
			break;
		case Left:
			currentFrame = 569;
			spriteData.flipHorizontal = false;
			break;
		case Up:
			currentFrame = 568;
			break;
	}
	
	//if (lc->collidedWithCrate() == 1)
	//{

	//}

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

void NPC::setDying(bool d)
{
	dying = d;
}

bool NPC::isDying()
{
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
	spriteData.x -= frameTime * npcNS::SPEED;
}

void NPC::moveRight(float frameTime) {
	orientation = Right;
	spriteData.x += frameTime * npcNS::SPEED;
}

void NPC::moveUp(float frameTime) {
	orientation = Up;
	spriteData.y -= frameTime * npcNS::SPEED;
}

void NPC::moveDown(float frameTime) {
	orientation = Down;
	spriteData.y += frameTime * npcNS::SPEED;
}

void NPC::ai(float frameTime, Entity &ent) {
	if (pathList.size() == 0)
		return;
	//pathList.push_back(VECTOR2(25, 25));
	if (currDest == VECTOR2(-1, -1)) { // No destination
		pathCount++;
		if (pathCount >= pathList.size())
			pathCount = 0;
		currDest = pathList.at(pathCount);
	}
	if ((int)spriteData.x == (int)currDest.x && (int)spriteData.y == (int)currDest.y) {
		currDest = VECTOR2(-1, -1);
	} else {
		if ((int)spriteData.x > (int)currDest.x) {
			moveLeft(frameTime);
		} else if ((int)spriteData.x < (int)currDest.x) {
			moveRight(frameTime);
		}
		if ((int)spriteData.y >(int)currDest.y) {
			moveUp(frameTime);
		} else if ((int)spriteData.y < (int)currDest.y) {
			moveDown(frameTime);
		}
	}
}
void NPC::addPath(VECTOR2 v) {
	pathList.push_back(v);
}