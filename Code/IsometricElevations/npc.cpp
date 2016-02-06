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
	//startFrame = npcControllerNS::npcSpriteMap[sprIndex][0];     // first frame of ship animation
	//endFrame = npcControllerNS::npcSpriteMap[sprIndex][3];     // last frame of ship animation
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
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int spriteNumber) {
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
	Image::draw();              // draw ship
	npcHealth->draw();
	npcHealthBack->draw();
}

void NPC::update(float frameTime, float mapX,float pVelo) {//, LevelController* lc) {
	RECT r;
	pVelocity = pVelo;
	npcHealthBack->setX(spriteData.x);
	npcHealthBack->setY(spriteData.y - 20);
	npcHealthBack->draw();
	npcHealth->setX(spriteData.x + 1);
	npcHealth->setY(spriteData.y - 21);
	r = npcHealth->getSpriteDataRect();
	r.right = npcHealth->getWidth() * (hp/hpMax);
	npcHealth->setSpriteDataRect(r);
	int test = sprIndex;
	ai(frameTime, *this, mapX);
	
	switch (orientation) {
		case Right:
			//currentFrame = 569;
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][1];
			//currentFrame = npcControllerNS::npcSpriteMap[1][sprIndex];
			spriteData.flipHorizontal = true;
			break;
		case Down:
			//currentFrame = 570;
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][2];
			//currentFrame = npcControllerNS::npcSpriteMap[2][sprIndex];
			break;
		case Left:
			//currentFrame = 569;
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][1];
			//currentFrame = npcControllerNS::npcSpriteMap[1][sprIndex];
			spriteData.flipHorizontal = false;
			break;
		case Up:
			//currentFrame = 568;
			currentFrame = npcControllerNS::npcSpriteMap[sprIndex][0];
			//currentFrame = npcControllerNS::npcSpriteMap[0][sprIndex];
			break;
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

void NPC::moveLeft(float frameTime, float mapX) {
	orientation = Left;
	if(pVelocity < 0)
		setVelocity(VECTOR2(-npcNS::SPEED * (frameTime / 2), 0));		
	else if(pVelocity > 0)
		setVelocity(VECTOR2(-npcNS::SPEED * 2 * frameTime, 0));
	else
		setVelocity(VECTOR2(-npcNS::SPEED * frameTime, 0));
}

void NPC::moveRight(float frameTime, float mapX) {
	orientation = Right;
	if(pVelocity > 0)
		setVelocity(VECTOR2(npcNS::SPEED * (frameTime / 2), 0));		
	else if(pVelocity < 0)
		setVelocity(VECTOR2(npcNS::SPEED * frameTime * 2, 0));
	else
		setVelocity(VECTOR2(npcNS::SPEED * frameTime, 0));
}

void NPC::moveUp(float frameTime) {
	orientation = Up;
	setVelocity(VECTOR2(-npcNS::JUMP_SPEED * frameTime, 0));
}

void NPC::moveDown(float frameTime) {
	orientation = Down;
	setVelocity(VECTOR2(npcNS::JUMP_SPEED * frameTime, 0));
}

void NPC::ai(float frameTime, Entity &ent, float mapX) {
	if (pathList.size() == 0)
		return;
	if (currDest == VECTOR2(-1, -1)) { // No destination
		pathCount++;
		if (pathCount >= pathList.size())
			pathCount = 0;
		startPoint = pathList.at(0);
		currDest = pathList.at(pathCount);
		//currDest.x += mapX;
	}
	OSD::instance()->addLine("AI at (" + to_string(spriteData.x) + ", " + to_string(spriteData.y) + ") going to (" + to_string((currDest.x + mapX)) + ", " + to_string(currDest.y) + ")");
	
	if (spriteData.x == currDest.x + mapX && spriteData.y == currDest.y) {
		currDest = VECTOR2(-1, -1);
	}
	else {
		if (orientation == Left)
		{
			if (spriteData.x > startPoint.x + mapX) {
				moveLeft(frameTime, mapX);
			}
			else {
				orientation = Right;
				//setVelocity(VECTOR2(0, 0));
			}
		}
		if (orientation == Right)
		{
			if (spriteData.x < currDest.x + mapX) {
				moveRight(frameTime, mapX);
			}
			else {
				orientation = Left;
				//setVelocity(VECTOR2(0, 0));
			}
		}

		if (spriteData.y > currDest.y) {
			moveUp(frameTime);
		}
		else if (spriteData.y < currDest.y) {
			moveDown(frameTime);
		}
	}
}
	
void NPC::addPath(VECTOR2 v) {
	pathList.push_back(v);
}

void NPC::setMapX(float x)
{
	mapX -= x;
}
