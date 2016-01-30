#include "npc.h"

using namespace std;
using namespace npcNS;
NPC::NPC() : Entity()
{
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

	npcBottomLeftX = getX();
	npcBottomLeftY = getY() - 1 + npcNS::NPC_HEIGHT * 0.5;
	npcBottomRightX = getX() - 1 + npcNS::NPC_WIDTH * 0.5;
	npcBottomRightY = getY() - 1 + npcNS::NPC_HEIGHT * 0.5;
	npcTopLeftX = getX();
	npcTopLeftY = getY();
	npcTopRightX = getX() - 1 + npcNS::NPC_WIDTH * 0.5;
	npcTopRightY = getY();
}

NPC::~NPC () {

}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	gameptr = gamePtr;
	startPoint = VECTOR2(spriteData.x, spriteData.y);
	endPoint = VECTOR2(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	if (!gunTexture.initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void NPC::draw()
{

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
	pistol.draw();
}
void NPC::update(float frameTime, LevelController* lc)
{
	ai(frameTime, *this);
	
	updateCoords();
	Tile* leftTile = lc->getTile(npcBottomLeftX, npcBottomLeftY + 1);
	Tile* rightTile = lc->getTile(npcBottomRightX, npcBottomRightY + 1);
	if (leftTile->isSolid() || rightTile->isSolid()) {
		if (!input->isKeyDown(NPC_UP) && !input->isKeyDown(NPC_JUMP))
			canJump = true;
		canFall = false;
		falling = false;
	}
	else {
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
		}
		else {
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
	/*
	if (spriteData.y > 0 && !input->isKeyDown(NPC_JUMP) && !input->isKeyDown(NPC_UP) && !input->isKeyDown(NPC_LEFT) && !input->isKeyDown(NPC_RIGHT)) {
		// Get Bottom left bottom right
		// Get Tile at that location y + 1 pixel
		// If Tile is not solid

		//orientation = down;
		machineGun.update(frameTime, orientation, spriteData.x, spriteData.y);
	}
	*/
	if (falling && !jumping) {
		Tile* tileA = lc->getTile(npcBottomLeftX, npcBottomLeftY + 1);
		Tile* tileB = lc->getTile(npcBottomRightX, npcBottomRightY + 1);
		if (!tileA->isSolid() && !tileB->isSolid()) {
			spriteData.y += frameTime * npcNS::FALLING_SPEED; // Use trajectory
		}
		tileA = lc->getTile(npcBottomLeftX, npcBottomLeftY + 1);
		tileB = lc->getTile(npcBottomRightX, npcBottomRightY + 1);
		while (tileA->isSolid() || tileB->isSolid()) {
			updateCoords();
			spriteData.y--;
		}
	}
	// spriteData.y = (int)spriteData.y;

	switch (orientation) {
	case Right:
		currentFrame = 953;
		spriteData.flipHorizontal = true;
		break;
	case Down:
		currentFrame = 954;
		break;
	case Left:
		currentFrame = 953;
		spriteData.flipHorizontal = false;
		break;
	case Up:
		currentFrame = 952;
		break;
	}
	//Console::getInstance()->print(buffer);
	/*
	if (spriteData.x < 32) // tileNS::TEXTURE_SIZE
	spriteData.x = 32;
	if (spriteData.x > GAME_WIDTH - playerNS::TEXTURE_SIZE)
	spriteData.x = GAME_WIDTH - playerNS::TEXTURE_SIZE;
	if (spriteData.y < 32)
	spriteData.y = 32;
	if (spriteData.y > GAME_HEIGHT - playerNS::TEXTURE_SIZE)
	spriteData.y = GAME_HEIGHT - playerNS::TEXTURE_SIZE;
	*/
	//pistol.update(frameTime, orientation, spriteData.x, spriteData.y);
	Entity::update(frameTime);
	//update gun
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
void NPC::damage(Projectile p) {

}
void NPC::healthUpdate() {
	if (hp < 0) {
		healthStatus = Dead;
		die();
	}
}
void NPC::die() {

}

/*void Entity::ai(float frameTime, Entity &ent){
	float startX = 0;
	float startY = 0;
	float endX = 0;
	float endY = 0;
}
*/

void NPC::moveLeft(float frameTime) {
	spriteData.x -= frameTime * npcNS::SPEED;
}

void NPC::moveRight(float frameTime) {
	spriteData.x += frameTime * npcNS::SPEED;
}

void NPC::moveUp(float frameTime) {
	spriteData.y -= frameTime * npcNS::SPEED;
}

void NPC::moveDown(float frameTime) {
	spriteData.y += frameTime * npcNS::SPEED;
}

void NPC::ai(float frameTime, Entity &ent) {
	// MAgic begins
	if ((int)spriteData.x == (int)endPoint.x && (int)spriteData.y == (int)endPoint.y) {
		// Awesome!
		// Popup
	}
	else {
		if (spriteData.x > endPoint.x) {
			moveLeft(frameTime);
		}
		else if (spriteData.x < endPoint.x) {
			moveRight(frameTime);
		} 
		if (spriteData.y > endPoint.y) {
			moveUp(frameTime);
		}
		else if (spriteData.y < endPoint.y) {
			moveDown(frameTime);
		}
	}
	/*int x = rand() % 4;
	switch (x) {
	case 0:
		moveUp(frameTime);
		break;
	case 1:
		moveDown(frameTime);
		break;
	case 2: 
		moveLeft(frameTime);
		break;
	case 3: 
		moveRight(frameTime);
		break;
	}
	*/
}

void NPC::updateCoords() {
	npcBottomLeftX = getX();
	npcBottomLeftY = getY() - 1 + npcNS::NPC_HEIGHT * 0.5;
	npcBottomRightX = getX() - 1 + npcNS::NPC_WIDTH * 0.5;
	npcBottomRightY = getY() - 1 + npcNS::NPC_HEIGHT * 0.5;
	npcTopLeftX = getX();
	npcTopLeftY = getY();
	npcTopRightX = getX() - 1 + npcNS::NPC_WIDTH * 0.5;
	npcTopRightY = getY();
}