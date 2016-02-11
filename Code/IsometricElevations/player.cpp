#include "player.h"


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
	hpMax = 100;
	health = 100;
	setVelocity(VECTOR2(0, 0));
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
	machineGun->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	machineGun->setCurrentFrame(gunNS::MACHINEGUN_FRAME);

	pistol = new Pistol();
	pistol->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	pistol->setCurrentFrame(gunNS::PISTOL_FRAME);

	shotgun = new Shotgun();
	shotgun->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	shotgun->setCurrentFrame(gunNS::SHOTGUN_FRAME);
	// End
	defaultItem = new InventoryItem(machineGun);
	inventory->addItem(defaultItem);
	defaultItem = new InventoryItem(shotgun);
	inventory->addItem(defaultItem);
	defaultItem = new InventoryItem(pistol);
	inventory->addItem(defaultItem);
	updateCoords();
	jumpOriginY = getY();
	setVelocity(VECTOR2(0, 0));
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Player::draw() {
	Image::draw();
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (activeItem->getItemType() == Item::Equipable) {
		Gun* gun = (Gun*)activeItem;
		gun->draw();
	}
	OSD::instance()->addLine("Player is at (" + std::to_string(topLeft.x) + ", " + std::to_string(topLeft.y) + ") Can Jump: " + std::to_string(canJump) + " | Can Fall: " + std::to_string(canFall) + " | Jumping: " + std::to_string(jumping) + " | Falling: " + std::to_string(falling));
	OSD::instance()->addLine("(" + std::to_string(int(topLeft.x)) + ", " + std::to_string(int(topLeft.y)) + ") ---- (" + std::to_string(int(topRight.x)) + ", " + std::to_string(int(topRight.y)) + ")");
	OSD::instance()->addLine("     |     ----     |  ");
	OSD::instance()->addLine("(" + std::to_string(int(bottomLeft.x)) + ", " + std::to_string(int(bottomRight.y)) + ") ---- (" + std::to_string(int(bottomRight.x)) + ", " + std::to_string(int(bottomRight.y)) + ")");

}
bool Player::canMoveUp() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0, topLeft.y - 1)->isSolid() || levelController->getTile(topRight.x + levelController->getMapX() * -1.0, topRight.y - 1)->isSolid());
}
bool Player::canMoveDown() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0, bottomLeft.y + 1)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0, bottomRight.y + 1)->isSolid());
}
bool Player::canMoveLeft() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0 - 1, topLeft.y)->isSolid() || levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0 - 1, bottomLeft.y)->isSolid());
}
bool Player::canMoveRight() {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topRight.x + levelController->getMapX() * -1.0 + 1, topRight.y)->isSolid() || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0 + 1, bottomRight.y)->isSolid());
}

int Player::getHealthStatus() {
	return healthStatus;
}
float Player::getPlayerVelocity() {
	return velocityX;
}
void Player::update(float frameTime, LevelController* lc) {
	levelController = lc;
	updateCoords();
	inventory->update(frameTime, input);
	float mapx = lc->getMapX() * -1.0;
	if (mapx > 1900)
	{
		audio->stopCue(BKMUSIC);
		audio->playCue(BOSSMUSIC);
	}
	velocityX = getVelocity().x;
	velocityY = getVelocity().y;
	// Debug Messages
	OSD::instance()->addLine("Jump Distance: " + std::to_string(jumpdistance) + " / " + std::to_string(playerNS::JUMP_HEIGHT));
	OSD::instance()->addLine("Can | Left: " + std::to_string(canMoveLeft()) + " | Right: " + std::to_string(canMoveRight()) + " | Up: " + std::to_string(canMoveUp()) + " | Down: " + std::to_string(canMoveDown()));
	if (!canMoveLeft() && !canMoveRight() && !canMoveUp() && !canMoveDown()) {
		setX(spawnPos.x);
		setY(spawnPos.y);
	}
	if (healthStatus != Dead) {
		// Handle Fall Logic and Jump Ability
		if (!canMoveDown()) {
			if (!input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_JUMP))
				canJump = true;
			canFall = false;
			falling = false;
		}
		else {
			canFall = true;
			falling = true;
		}
		// Move Left and Right
		if (input->isKeyDown(PLAYER_RIGHT) && canMoveRight()) {
			velocityX = playerNS::SPEED * frameTime;
			while (!canMoveRight()) {
				spriteData.x -= 0.1;
				velocityX = 0;
			}
			orientation = Right;
		}
		else if (input->isKeyDown(PLAYER_LEFT) && canMoveLeft()) {
			velocityX = -playerNS::SPEED * frameTime;
			while (!canMoveLeft()) {
				spriteData.x += 0.1;
				velocityX = 0;
			}
			orientation = Left;
		}
		else {
			velocityX = 0;
			if (input->isKeyDown(PLAYER_UP))
			{
				orientation = Up;
			}

			if (input->isKeyDown(PLAYER_DOWN))
			{
				orientation = Down;
			}
		}
		// Handle Jumping
		if (jumping || (((input->isKeyDown(PLAYER_JUMP) || input->isKeyDown(PLAYER_UP)) && canMoveUp() && canJump))) {
			jumpdistance = jumpOriginY - getY();
			if (canJump && !jumping)
				jumpOriginY = getY();
			if (jumpdistance > playerNS::JUMP_HEIGHT || !canMoveUp()) {
				jumping = false;
				canJump = false;
				falling = true;
			}
			else {
				if (!jumping)
					velocityY = -playerNS::JUMP_SPEED * frameTime;
				else
					velocityY += 0.5 * frameTime;
				jumping = true;
				canJump = false;
			}
		}
		if (!jumping)
			jumpOriginY = getY();
		if (falling && !jumping) {
			if (canMoveDown()) {
				velocityY = playerNS::FALLING_SPEED * frameTime;
			}
			else {
				velocityY = 0;
			}
		}
		// Handle Stuck
		while (canMoveUp() && !canMoveDown() && !canMoveLeft() && !canMoveRight()) {
			spriteData.y -= 1;
		}
		// Final Sanity Check
		if (!canMoveLeft() && velocityX < 0 || !canMoveRight() && velocityX > 0)
			velocityX = 0;
		if (!canMoveUp() && velocityY < 0 || !canMoveDown() && velocityY > 0)
			velocityY = 0;
		setVelocity(VECTOR2(velocityX, velocityY));
		// Handle Orientations
		if (input->isKeyDown(PLAYER_UP))
			orientation = Up;
		else if (input->isKeyDown(PLAYER_DOWN))
			orientation = Down;
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
		// Draw Items
		Item* activeItem = inventory->getActiveItem()->getItem();
		if (inventory->getActiveItem()->getItem()->getItemType() == Item::Equipable) {
			Gun* gun = dynamic_cast<Gun*>(activeItem);
			if (gun != 0) {
				gun->update(frameTime, orientation, spriteData.x, spriteData.y, input, lc);
			}
		}

		if (lc->collidedWithCrate() == 1 && lc->getCrateItem() != -1)
		{
			//audio->playCue(RELOAD);
			/* REMOVE ME
			if (lc->collidedWithCrate() == 1 && lc->getCrateItem() != -1) {
				int itemid = lc->getCrateItem();
				InventoryItem *invItem;
				vector<InventoryItem*>* itemList = inventory->getItems();
				switch (itemid) {
					case playerNS::ItemType::shotGun:
						shotgun = new Shotgun();
						shotgun->initialize(gameptr, 136, 41, 2, gunTexture);
						shotgun->setCurrentFrame(6);
						invItem = new InventoryItem(shotgun);
						break;
					case playerNS::ItemType::machineGun:
						machineGun = new MachineGun();
						machineGun->initialize(gameptr, 136, 41, 2, gunTexture);
						machineGun->setCurrentFrame(0);
						invItem = new InventoryItem(machineGun);
						break;
					case 3:
						break;
				}
				for (int i = 0; i < itemList->size(); i++) {
					InventoryItem *iItem = itemList->at(i);
					Item* item = iItem->getItem();
					Item* newItem = invItem->getItem();
					if (item->getItemType() == Item::Equipable && newItem->getItemType() == Item::Equipable) {
						Gun* gunInvItem = dynamic_cast<Gun*>(item);
						Gun* gunNewItem = dynamic_cast<Gun*>(newItem);
						if (gunInvItem->getGunId() == gunNewItem->getGunId()) {
							gunInvItem->addAmmo();
							lc->setCrateCollided(0);
							return;
						}
					} else if (item->getItemType() == Item::Usable && newItem->getItemType() == Item::Usable) {
						lc->setCrateCollided(0);
						return;
					}
				}
				inventory->addItem(invItem);
				lc->setCrateCollided(0);
				lc->setCrateItem(-1);
				*/

		}
		Entity::update(frameTime);
	}
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
float Player::getHP() {
	return hp;
}
float Player::getMaxHP() {
	return hpMax;
}
Inventory* Player::getInventory() {
	return inventory;
}
Game * Player::getGamePtr() {
	return gameptr;
}
TextureManager * Player::getTexture() {
	return gunTexture;
}
void Player::setFalling(bool f) {
	falling = f;
}
void Player::damage(float amt) {
	audio->playCue(HURT);
	health -= amt;
	healthUpdate();
}
void Player::damage(Weapon w) {

}
void Player::damage(Projectile p) {

}
void Player::healthUpdate() {
	if (health <= 0) {
		health = 0;
		if (healthStatus == Dead)
			return;
		else
			audio->playCue(DIE);
		healthStatus = Dead;		
		die();		
	}
}
void Player::die() {
	currentFrame = 953;
	spriteData.angle = PI / 2;
}