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
	hpMax = 100;
	hp = 100;
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
	OSD::instance()->addLine("Player is at (" + to_string(topLeft.x) + ", " + to_string(topLeft.y) + ") Can Jump: " + to_string(canJump) + " | Can Fall: " + to_string(canFall) + " | Jumping: " + to_string(jumping) + " | Falling: " + to_string(falling));
	OSD::instance()->addLine("(" + to_string(int(topLeft.x)) + ", " + to_string(int(topLeft.y)) + ") ---- (" + to_string(int(topRight.x)) + ", " + to_string(int(topRight.y)) + ")");
	OSD::instance()->addLine("     |     ----     |  ");
	OSD::instance()->addLine("(" + to_string(int(bottomLeft.x)) + ", " + to_string(int(bottomRight.y)) + ") ---- (" + to_string(int(bottomRight.x)) + ", " + to_string(int(bottomRight.y)) + ")");

}
void Player::update(float frameTime, LevelController* lc) {
	updateCoords();
	inventory->update(frameTime, input);
	float mapx = lc->getMapX() * -1.0;
	Tile* leftTile = lc->getTile(playerBottomLeftX + mapx, playerBottomLeftY + 1);
	Tile* rightTile = lc->getTile(playerBottomRightX + mapx, playerBottomRightY + 1);
	if (leftTile->isSolid() || rightTile->isSolid()) {
		if (!input->isKeyDown(PLAYER_UP) && !input->isKeyDown(PLAYER_JUMP))
			canJump = true;
		canFall = false;
		falling = false;
	}
	else {
		canFall;
		falling = true;
	}
	if (input->isKeyDown(PLAYER_RIGHT) && canMoveRight) {
		spriteData.x += frameTime * playerNS::SPEED;
		velocity.x = spriteData.x;
		while (lc->getTile(spriteData.x + 31 + mapx, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31 + mapx, spriteData.y + 31)->isSolid()) {
			spriteData.x -= frameTime * playerNS::FALLING_SPEED;
		}
		orientation = Right;
	}
	if (input->isKeyDown(PLAYER_LEFT) && canMoveLeft) {
		spriteData.x -= frameTime * playerNS::SPEED;
		velocity.x = spriteData.x;
		while (lc->getTile(spriteData.x + mapx, spriteData.y)->isSolid() || lc->getTile(spriteData.x + mapx, spriteData.y + 31)->isSolid()) {
			spriteData.x += frameTime * playerNS::FALLING_SPEED;
		}
		orientation = Left;
	}
	if (input->isKeyDown(PLAYER_UP))
	{
		orientation = Up;
	}
	if (input->isKeyDown(PLAYER_DOWN))
	{
		orientation = Down;
	}
	if (jumping || ((input->isKeyDown(PLAYER_JUMP) && canMoveUp && canJump))) {
		if (!jumping && canJump)
			jumpdistance = 0;
		if (jumpdistance > playerNS::JUMP_HEIGHT) {
			jumping = false;
			canJump = false;
			falling = true;
		}
		else {
			jumping = true;
			canJump = false;
			jumpdistance += frameTime * playerNS::JUMP_SPEED;
			spriteData.y -= frameTime * playerNS::JUMP_SPEED;
			while (lc->getTile(spriteData.x + mapx, spriteData.y)->isSolid() || lc->getTile(spriteData.x + 31 + mapx, spriteData.y)->isSolid()) {
				spriteData.y += frameTime * playerNS::FALLING_SPEED;
			}
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
		Tile* tileA = lc->getTile(playerBottomLeftX + mapx, playerBottomLeftY + 1);
		Tile* tileB = lc->getTile(playerBottomRightX + mapx, playerBottomRightY + 1);
		if (!tileA->isSolid() && !tileB->isSolid()) {
			spriteData.y += frameTime * playerNS::FALLING_SPEED; // Use trajectory
		}
		tileA = lc->getTile(playerBottomLeftX + mapx, playerBottomLeftY + 1);
		tileB = lc->getTile(playerBottomRightX + mapx, playerBottomRightY + 1);
		while (tileA->isSolid() || tileB->isSolid()) {
			updateCoords();
			spriteData.y--;
		}
	}
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
	Item* activeItem = inventory->getActiveItem()->getItem();
	if (inventory->getActiveItem()->getItem()->getItemType() == Item::Equipable) {
		Gun* gun = dynamic_cast<Gun*>(activeItem);
		if (gun != 0) {
			gun->update(frameTime, orientation, spriteData.x, spriteData.y, input, lc);
		}
	}

	if (lc->collidedWithCrate() == 1)
	{
		int id = rand() % 2 + 1;
		InventoryItem *invItem;
		vector<InventoryItem*>* itemList = inventory->getItems();
		switch (id)
		{
		case 1:
			shotgun = new Shotgun();
			shotgun->initialize(gameptr, 136, 41, 2, gunTexture);
			shotgun->setCurrentFrame(6);
			invItem = new InventoryItem(shotgun);
			break;
		case 2:
			machineGun = new MachineGun();
			machineGun->initialize(gameptr, 136, 41, 2, gunTexture);
			machineGun->setCurrentFrame(0);
			invItem = new InventoryItem(machineGun);
			break;
		case 3:
			/*hp = new HealthPack();
			invItem = new InventoryItem(hp);*/
			break;
		}
		for (int i = 0; i < itemList->size(); i++)
		{
			InventoryItem *iItem = itemList->at(i);
			Item* item = iItem->getItem();
			Item* newItem = invItem->getItem();
			if (item->getItemType() == Item::Equipable && newItem->getItemType() == Item::Equipable)
			{
				Gun* gunInvItem = dynamic_cast<Gun*>(item);
				Gun* gunNewItem = dynamic_cast<Gun*>(newItem);
				if (gunInvItem->getGunId() == gunNewItem->getGunId())
				{
					gunInvItem->addAmmo();
					lc->setCrateCollided(0);
					return;
				}
			}
			else if (item->getItemType() == Item::Usable && newItem->getItemType() == Item::Usable)
			{
				lc->setCrateCollided(0);
				return;
			}
		}
		inventory->addItem(invItem);
		lc->setCrateCollided(0);
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
float Player::getHP()
{
	return hp;
}
float Player::getMaxHP()
{
	return hpMax;
}
Inventory* Player::getInventory()
{
	return inventory;
}
Game * Player::getGamePtr()
{
	return gameptr;
}
TextureManager * Player::getTexture()
{
	return gunTexture;
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