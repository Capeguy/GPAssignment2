#include "player.h"

using namespace std;
Player::Player() : Entity()
{
	//spriteData.width = playerNS::WIDTH;           // size of player ship
	//spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	//spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	//spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
	endFrame = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
}

Player::~Player()
{

}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Player::draw()
{

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
}
void Player::update(float frameTime)
{	
	Entity::update(frameTime);
	if (input->isKeyDown(PLAYER_RIGHT))
	{
		spriteData.x += frameTime * playerNS::SPEED;
		orientation = right;
	}
	if (input->isKeyDown(PLAYER_LEFT))
	{
		spriteData.x -= frameTime * playerNS::SPEED;
		orientation = left;
	}
	if (input->isKeyDown(PLAYER_JUMP) || input->isKeyDown(PLAYER_UP))
	{
		spriteData.y -= frameTime * playerNS::JUMP_HEIGHT;
		orientation = up;
	}
	if (input->isKeyDown(PLAYER_DOWN))
	{
		spriteData.y += frameTime * playerNS::JUMP_HEIGHT;
		orientation = down;
	}

	if (spriteData.y > 0 && !input->isKeyDown(PLAYER_JUMP) && !input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_LEFT) && !input->isKeyDown(PLAYER_RIGHT)) {
		// Get Bottom left bottom right
		// Get Tile at that location y + 1 pixel
		// If Tile is not solid
		if (falling) {
			falling = false;
			spriteData.y += frameTime * playerNS::FALLING_SPEED; // Use trajectory
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
	if (spriteData.x < 32) // tileNS::TEXTURE_SIZE
		spriteData.x = 32;
	if (spriteData.x > GAME_WIDTH - playerNS::TEXTURE_SIZE)
		spriteData.x = GAME_WIDTH - playerNS::TEXTURE_SIZE;
	if (spriteData.y < 32)
		spriteData.y = 32;
	if (spriteData.y > GAME_HEIGHT - playerNS::TEXTURE_SIZE)
		spriteData.y = GAME_HEIGHT - playerNS::TEXTURE_SIZE;
	Entity::update(frameTime);
}
void Player::setFalling(bool f) {
	falling = f;
}
void Player::damage(float amt) {
	hp -= amt;
	healthUpdate();
}
void Player::damage(Weapon w) {

}
void Player::damage(Projectile p) {

}
void Player::healthUpdate() {
	if (hp < 0) {
		healthStatus = Dead;
		die();
	}
}
void Player::die() {

}