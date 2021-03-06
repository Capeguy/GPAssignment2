//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "player.h"


Player::Player() : Entity() {
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	startFrame = playerNS::PLAYER_START_FRAME;
	endFrame = playerNS::PLAYER_END_FRAME;
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

Player::~Player() {}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	gameptr = gamePtr;
	gunTexture = new TextureManager();
	if (!gunTexture->initialize(gamePtr->getGraphics(), TEXTURE_GUNS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));
	pistol = new Pistol();
	pistol->initialize(gameptr, gunNS::TEXTURE_WIDTH, gunNS::TEXTURE_HEIGHT, gunNS::TEXTURE_COLS, gunTexture);
	pistol->setCurrentFrame(gunNS::PISTOL_FRAME);
	defaultItem = new InventoryItem(pistol);
	inventory->addItem(defaultItem);
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
bool Player::canMoveUp(bool s = false) {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0, topLeft.y - 1)->isSolid(s) || levelController->getTile(topRight.x + levelController->getMapX() * -1.0, topRight.y - 1)->isSolid(s));
}
bool Player::canMoveDown(bool s = false) {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0, bottomLeft.y + 1)->isSolid(s) || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0, bottomRight.y + 1)->isSolid(s));
}
bool Player::canMoveLeft(bool s = false) {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topLeft.x + levelController->getMapX() * -1.0 - 1, topLeft.y)->isSolid(s) || levelController->getTile(bottomLeft.x + levelController->getMapX() * -1.0 - 1, bottomLeft.y)->isSolid(s));
}
bool Player::canMoveRight(bool s = false) {
	bottomLeft = VECTOR2(getX(), getY() - 1 + getHeight() * getScale());
	bottomRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY() - 1 + getHeight() * getScale());
	topLeft = VECTOR2(getX(), getY());
	topRight = VECTOR2(getX() - 1 + getWidth() * getScale(), getY());
	return !(levelController->getTile(topRight.x + levelController->getMapX() * -1.0 + 1, topRight.y)->isSolid(s) || levelController->getTile(bottomRight.x + levelController->getMapX() * -1.0 + 1, bottomRight.y)->isSolid(s));
}

int Player::getHealthStatus() {
	return healthStatus;
}
int Player::getTotalPoints() {
	return totalPoints;
}
float Player::getPlayerVelocity() {
	return velocityX;
}
void Player::update(float frameTime, LevelController* lc) {
	// 1-Press NoClip
	if (noClipButtonReleased && input->isKeyDown(VK_F2)) {
		noClip = !noClip;
		noClipButtonReleased = false;
	} else {
		noClipButtonReleased = true;
	}
	velocityX = getVelocity().x;
	velocityY = getVelocity().y;
	// Handle NoClip
	if (noClip) {
		if (input->isKeyDown(PLAYER_RIGHT)) {
			velocityX = playerNS::NOCLIP_SPEED * frameTime;
			orientation = Right;
		} else if (input->isKeyDown(PLAYER_LEFT)) {
			velocityX = -playerNS::NOCLIP_SPEED * frameTime;
			orientation = Left;
		} else {
			velocityX = 0;
		}
		if (input->isKeyDown(PLAYER_UP)) {
			velocityY = -playerNS::NOCLIP_SPEED * frameTime;
			orientation = Up;
		} else if (input->isKeyDown(PLAYER_DOWN)) {
			velocityY = playerNS::NOCLIP_SPEED * frameTime;
			orientation = Down;
		} else {
			velocityY = 0;
		}
		velocity = VECTOR2(velocityX, velocityY);
		frameDelay = 1000000;
		Item* activeItem = inventory->getActiveItem()->getItem();
		if (inventory->getActiveItem()->getItem()->getItemType() == Item::Equipable) {
			Gun* gun = dynamic_cast<Gun*>(activeItem);
			if (gun != 0) {
				gun->update(frameTime, orientation, getX(), getY(), input, lc);
			}
		}
		Entity::update(frameTime);
		return;
	}
	// Set Obj Vars
	levelController = lc;
	// Debug Messages
	OSD::instance()->addLine("Jump Distance: " + std::to_string(jumpdistance) + " / " + std::to_string(playerNS::JUMP_HEIGHT));
	OSD::instance()->addLine("Can | Left: " + std::to_string(canMoveLeft(true)) + " | Right: " + std::to_string(canMoveRight(true)) + " | Up: " + std::to_string(canMoveUp(true)) + " | Down: " + std::to_string(canMoveDown(true)));
	// Stuck Hotfix
	if (!canMoveLeft() && !canMoveRight() && !canMoveUp() && !canMoveDown()) {
		setX(spawnPos.x);
		setY(spawnPos.y);
	}
	// Update Guns
	inventory->update(frameTime, input);
	// Boss Audio
	if (lc->getMapX() * -1.0 > 1900) {
		audio->stopCue(BK_MUSIC);
		audio->playCue(BOSS_MUSIC);
	}

	// Start of Player Movement
	if (healthStatus != Dead) {
		if (!canMoveDown()) {
			if (!input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_JUMP))
				canJump = true;
			canFall = false;
			falling = false;
		} else {
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
		} else if (input->isKeyDown(PLAYER_LEFT) && canMoveLeft()) {
			velocityX = -playerNS::SPEED * frameTime;
			while (!canMoveLeft()) {
				spriteData.x += 0.1;
				velocityX = 0;
			}
			orientation = Left;
		} else {
			velocityX = 0;
			if (input->isKeyDown(PLAYER_UP)) {
				orientation = Up;
			}

			if (input->isKeyDown(PLAYER_DOWN)) {
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
			} else {
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
			} else {
				velocityY = 0;
			}
		}
		// Handle Stuck
		while (canMoveUp() && !canMoveDown() && !canMoveLeft() && !canMoveRight()) {
			spriteData.y -= 0.1;
		}
		while (!canMoveUp() && !canMoveDown() && !canMoveLeft() && canMoveRight()) {
			spriteData.x += 0.1;
		}
		while (!canMoveUp() && !canMoveDown() && canMoveLeft() && !canMoveRight()) {
			spriteData.x -= 0.1;
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
				gun->update(frameTime, orientation, getX(), getY(), input, lc);
			}
		}
		// Crate Collision
		if (lc->collidedWithCrate() == 1 && lc->getCrateItem() != -1) {
			audio->playCue(RELOAD);
			if (lc->collidedWithCrate() == 1 && lc->getCrateItem() != -1) {
				int itemid = lc->getCrateItem();
				InventoryItem *invItem;
				std::vector<InventoryItem*>* itemList = inventory->getItems();
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
							return; // Should this be return or break?
						}
					} else if (item->getItemType() == Item::Usable && newItem->getItemType() == Item::Usable) {
						lc->setCrateCollided(0);
						return;
					} // Should this be return or break?
				}
				inventory->addItem(invItem);
				lc->setCrateCollided(0);
				lc->setCrateItem(-1);
			}
		}
		Entity::update(frameTime);
	}
}
void Player::setTotalPoints(int points) {
	totalPoints += points;
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
void Player::setHealth(float f) {
	if (f > hpMax)
		health = hpMax;
	else if (f < 0)
		health = 0;
	else health = f;
}