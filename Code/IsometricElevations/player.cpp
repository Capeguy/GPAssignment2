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

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	
	Entity::update(frameTime);
	//spriteData.x += frameTime * velocity.x;         // move ship along X 
	//spriteData.y += frameTime * velocity.y;         // move ship along Y

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
	/*												// Bounce off walls
	if (spriteData.x > GAME_WIDTH - playerNS::WIDTH*spriteData.scale)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - playerNS::WIDTH*spriteData.scale;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - playerNS::HEIGHT*spriteData.scale)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - playerNS::HEIGHT*spriteData.scale;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	*/

}
void Player::setFalling(bool f) {
	falling = f;
}