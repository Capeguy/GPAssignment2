#include "player.h"

Player::Player() : Entity()
{
	spriteData.width = playerNS::WIDTH;           // size of player ship
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
	endFrame = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = playerNS::WIDTH / 2.0;
	mass = playerNS::MASS;
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
	}

	if (input->isKeyDown(PLAYER_LEFT))
	{
		spriteData.x -= frameTime * playerNS::SPEED;
	}
	if (input->isKeyDown(PLAYER_JUMP))
	{
		spriteData.y += frameTime * playerNS::JUMP_HEIGHT;
	}

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
