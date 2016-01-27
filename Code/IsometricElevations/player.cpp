#include "player.h"

using namespace std;
Player::Player() : Entity()
{
	//spriteData.width = playerNS::WIDTH;           // size of player ship
	//spriteData.height = playerNS::HEIGHT;
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
	collisionType = entityNS::CIRCLE;
	spriteData.scale = 0.5;
	inventory = Inventory();
}

Player::~Player()
{

}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	gameptr = gamePtr;
	if (!gunTexture.initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	pistol.initialize(gameptr, 136, 41, 2, &gunTexture);
	pistol.setCurrentFrame(8);
	machineGun.initialize(gameptr, 136, 41, 2, &gunTexture);
	machineGun.setCurrentFrame(0);
	shotgun.initialize(gameptr, 136, 41, 2, &gunTexture);
	shotgun.setCurrentFrame(6);
	InventoryItem* iItem = new InventoryItem(machineGun);
	inventory.addItem(*iItem);
	// Give default pistol
	Pistol pistol = Pistol();


	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Player::draw()
{

	//spriteData.scale = 0.5;
	Image::draw();              // draw ship
	pistol.draw();
}
void Player::update(float frameTime, LevelController* lc)
{	
	Tile* leftTile = lc->getTile(spriteData.x, spriteData.y + 32);
	Tile* rightTile = lc->getTile(spriteData.x + 32, spriteData.y + 32);
	if (leftTile->isSolid() || rightTile->isSolid())
	{
		jump = true;
	}
	else
	{
		jump = false;
	}
	if (input->isKeyDown(PLAYER_RIGHT) && canMoveRight)
	{
		spriteData.x += frameTime * playerNS::SPEED;
		while (lc->getTile(spriteData.x + 31, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y + 31)->isSolid()) {
			spriteData.x -= frameTime * playerNS::FALLING_SPEED;
		}
		orientation = right;
	}
	if (input->isKeyDown(PLAYER_LEFT) && canMoveLeft)
	{
		spriteData.x -= frameTime * playerNS::SPEED;
		while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x, spriteData.y + 31)->isSolid()) {
			spriteData.x += frameTime * playerNS::FALLING_SPEED;
		}
		orientation = left;
	}
	if ((input->isKeyDown(PLAYER_JUMP) || input->isKeyDown(PLAYER_UP)) && canMoveUp && jump)
	{
		spriteData.y -= frameTime * playerNS::JUMP_HEIGHT;
		while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y)->isSolid()) {
			spriteData.y += frameTime * playerNS::FALLING_SPEED;
		}
		orientation = up;
	}
	if (spriteData.y > 0 && !input->isKeyDown(PLAYER_JUMP) && !input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_LEFT) && !input->isKeyDown(PLAYER_RIGHT)) {
		// Get Bottom left bottom right
		// Get Tile at that location y + 1 pixel
		// If Tile is not solid
	
			//orientation = down;
		machineGun.update(frameTime, orientation, spriteData.x, spriteData.y);
	}
	if (canMoveDown) {
		falling = false;
		spriteData.y += frameTime * playerNS::FALLING_SPEED; // Use trajectory
		while (lc->getTile(spriteData.x, spriteData.y + 31)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y + 31)->isSolid()) {
			spriteData.y--;
		}
	}
	spriteData.y = (int)spriteData.y;
	


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
	pistol.update(frameTime, orientation, spriteData.x, spriteData.y);
	Entity::update(frameTime);
	//update gun
	
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