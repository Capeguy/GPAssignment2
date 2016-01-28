#include "npc.h"

using namespace std;
using namespace npcNS;
NPC::NPC()	: Entity()
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
}

NPC::~NPC()
{

}
bool NPC::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	gameptr = gamePtr;
	bool result = Entity::initialize(gamePtr, width, height, ncols, textureM);
	startPoint = VECTOR2(spriteData.x, spriteData.y);
	endPoint = VECTOR2(GAME_WIDTH/2, GAME_HEIGHT/2);
	return result;
}
void NPC::draw()
{

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
}
void NPC::update(float frameTime)
{
	ai(frameTime, *this);
	return;
	if (input->isKeyDown(NPC_RIGHT) && canMoveRight)
	{
		spriteData.x += frameTime * npcNS::SPEED;
		while (gameptr->tileIsSolid(spriteData.x + 31, spriteData.y) || gameptr->tileIsSolid(spriteData.x + 31, spriteData.y + 31)) {
			spriteData.x -= frameTime * npcNS::FALLING_SPEED;
		}
		orientation = right;
	}
	if (input->isKeyDown(NPC_LEFT) && canMoveLeft)
	{
		spriteData.x -= frameTime * npcNS::SPEED;
		while (gameptr->tileIsSolid(spriteData.x, spriteData.y) || gameptr->tileIsSolid(spriteData.x, spriteData.y + 31)) {
			spriteData.x += frameTime * npcNS::FALLING_SPEED;
		}
		orientation = left;
	}
	if ((input->isKeyDown(NPC_JUMP) || input->isKeyDown(NPC_UP)) && canMoveUp)
	{
		spriteData.y -= frameTime * npcNS::JUMP_HEIGHT;
		while (gameptr->tileIsSolid(spriteData.x, spriteData.y) || gameptr->tileIsSolid(spriteData.x + 31, spriteData.y)) {
			spriteData.y += frameTime * npcNS::FALLING_SPEED;
		}
		orientation = up;
	}
	if (input->isKeyDown(NPC_DOWN) && canMoveDown)
	{
		spriteData.y += frameTime * npcNS::JUMP_HEIGHT;
		orientation = down;
	}

	if (spriteData.y > 0 && !input->isKeyDown(NPC_JUMP) && !input->isKeyDown(NPC_UP) && !input->isKeyDown(NPC_LEFT) && !input->isKeyDown(NPC_RIGHT)) {
		// Get Bottom left bottom right
		// Get Tile at that location y + 1 pixel
		// If Tile is not solid
		if (canMoveDown) {
			falling = false;
			spriteData.y += frameTime * npcNS::FALLING_SPEED; // Use trajectory
			while (gameptr->tileIsSolid(spriteData.x, spriteData.y + 31) || gameptr->tileIsSolid(spriteData.x + 31, spriteData.y + 31)) {
				spriteData.y -= frameTime * npcNS::FALLING_SPEED;
			}
			orientation = down;
		}
	}
	switch (orientation) {
	case right:
		currentFrame = 953;
		spriteData.flipHorizontal = true;
		break;
	case down:
		currentFrame = 954;
		break;
	case left:
		currentFrame = 953;
		spriteData.flipHorizontal = false;
		break;
	case up:
		currentFrame = 952;
		break;
	}
	string buffer;
	buffer = to_string(orientation);
	buffer += " -> ";
	buffer += currentFrame;
	
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
	if (spriteData.x == endPoint.x && spriteData.y == endPoint.y) {
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