#include "player.h"

using namespace std;
Player::Player() : Entity() {
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
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	RECT e;
	e.right = playerNS::WIDTH / 2;
	e.left = -playerNS::WIDTH / 2;
	e.bottom = playerNS::HEIGHT / 2;
	e.top = -playerNS::HEIGHT / 2;
	setEdge(e);
	inventory = new Inventory();
	
}

Player::~Player() {

}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {

	gameptr = gamePtr;
	gameptr->console->print("THIS CAME FROM PLAYER");
	gunTexture = new TextureManager();
	if (!gunTexture->initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	// We should move this elsewhere - Ben
	
	machineGun = new MachineGun();
	machineGun->initialize(gameptr, 136, 41, 2, gunTexture);
	machineGun->setCurrentFrame(0);

	pistol = new Pistol();
	pistol->initialize(gameptr, 136, 41, 2, gunTexture);
	pistol->setCurrentFrame(8);

	shotgun = new Shotgun();
	shotgun->initialize(gameptr, 136, 41, 2, gunTexture);
	shotgun->setCurrentFrame(6);
	// End
	defaultItem = new InventoryItem(machineGun);
	inventory->addItem(defaultItem);
	defaultItem = new InventoryItem(shotgun);
	inventory->addItem(defaultItem);
	defaultItem = new InventoryItem(pistol);
	inventory->addItem(defaultItem);
	updateCoords();
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Player::draw() {
	Image::draw();
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (activeItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)activeItem;
		gun->draw();
	}
}
void Player::update(float frameTime, LevelController* lc) {
	updateCoords();
	inventory->update(frameTime, input);
	Tile* leftTile = lc->getTile(playerBottomLeftX, playerBottomLeftY + 1);
	Tile* rightTile = lc->getTile(playerBottomRightX, playerBottomRightY + 1);
	if (leftTile->isSolid() || rightTile->isSolid()) {
		if (!input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_JUMP))
			canJump = true;
		canFall = false;
		falling = false;
	} else {
		canFall;
		falling = true;
	}
	if (input->isKeyDown(PLAYER_RIGHT) && canMoveRight) {
		spriteData.x += frameTime * playerNS::SPEED;
		while (lc->getTile(spriteData.x + 31, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y + 31)->isSolid()) {
			spriteData.x -= frameTime * playerNS::FALLING_SPEED;
		}
		orientation = right;
	}
	if (input->isKeyDown(PLAYER_LEFT) && canMoveLeft) {
		spriteData.x -= frameTime * playerNS::SPEED;
		while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x, spriteData.y + 31)->isSolid()) {
			spriteData.x += frameTime * playerNS::FALLING_SPEED;
		}
		orientation = left;
	}
	if (jumping || ((input->isKeyDown(PLAYER_JUMP) || input->isKeyDown(PLAYER_UP)) && canMoveUp && canJump)) {
		if (!jumping && canJump)
			jumpdistance = 0;
		if (jumpdistance > playerNS::JUMP_HEIGHT) {
			jumping = false;
			canJump = false;
			falling = true;
		} else {
			jumping = true;
			canJump = false;
			jumpdistance += frameTime * playerNS::JUMP_SPEED;
			spriteData.y -= frameTime * playerNS::JUMP_SPEED;
			while (lc->getTile(spriteData.x, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31, spriteData.y)->isSolid()) {
				spriteData.y += frameTime * playerNS::FALLING_SPEED;
			}
			orientation = up;
		}
	}
	if (spriteData.y > 0 && !input->isKeyDown(PLAYER_JUMP) && !input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_LEFT) && !input->isKeyDown(PLAYER_RIGHT)) {
		// Get Bottom left bottom right
		// Get Tile at that location y + 1 pixel
		// If Tile is not solid

			//orientation = down;
		//machineGun.update(frameTime, orientation, spriteData.x, spriteData.y);
	}
	if (falling && !jumping) {
		Tile* tileA = lc->getTile(playerBottomLeftX, playerBottomLeftY + 1);
		Tile* tileB = lc->getTile(playerBottomRightX, playerBottomRightY + 1);
		if (!tileA->isSolid() && !tileB->isSolid()) {
			spriteData.y += frameTime * playerNS::FALLING_SPEED; // Use trajectory
		}
		tileA = lc->getTile(playerBottomLeftX, playerBottomLeftY + 1);
		tileB = lc->getTile(playerBottomRightX, playerBottomRightY + 1);
		while (tileA->isSolid() || tileB->isSolid()) {
			updateCoords();
			spriteData.y--;
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
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (inventory->getActiveItem()->getItem()->getItemType() == Item::Equipable) {
		Gun* gun = dynamic_cast<Gun*>(activeItem);
		if (gun != 0) {
			gun->update(frameTime, orientation, spriteData.x, spriteData.y, input, lc);
		}
	}
	Entity::update(frameTime);
}
void Player::updateCoords() {
	playerBottomLeftX = getX();
	playerBottomLeftY = getY() - 1 + playerNS::PLAYER_HEIGHT * 0.5;
	playerBottomRightX = getX() - 1 + playerNS::PLAYER_WIDTH * 0.5;
	playerBottomRightY = getY() - 1 + playerNS::PLAYER_HEIGHT * 0.5;
	playerTopLeftX = getX();
	playerTopLeftY = getY();
	playerTopRightX = getX() - 1 + playerNS::PLAYER_WIDTH * 0.5;
	playerTopRightY = getY();
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