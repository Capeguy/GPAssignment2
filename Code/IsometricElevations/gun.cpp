//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#include "gun.h"


Gun::Gun() {
	type = Equipable;
	spriteData.x = 0;                   // location on screen
	spriteData.y = 0;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = 0.2f;
	startFrame = 0;     // first frame of ship animation
	endFrame = 0;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
	bullets = std::vector<Projectile*>();
}

Gun::~Gun() {}
bool Gun::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM) {
	gameptr = gamePtr;
	bulletTexture = new TextureManager();
	debug = new TextDX();
	debug->initialize(gamePtr->getGraphics(), 20, false, false, "Courier New");
	if (!bulletTexture->initialize(gamePtr->getGraphics(), TEXTURE_BULLETS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Gun::update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc) {
	//change orientation of gun based on mouse position
	playerX = x;
	playerY = y;
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();
	adjacent = mouseX - x;
	opposite = mouseY - y;
	angle = atan((opposite / adjacent));
	spriteData.angle = angle;
	if (adjacent < 0) {  // facing back
		setX(x - 20);
		setY(y + 5);
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y + 5);
		flipHorizontal(false);
	}
	//angle = atan((mouseY - getY()) / (mouseX - getX()));
	// Fire bullet
	if (input->getMouseLButton()) {
		shoot(lc, frametime);
	} else {
		cooldownCurrent -= frametime;
	}
	Entity::update(frametime);
}

void Gun::update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc, float destX, float destY, bool shouldShoot) {
	//change orientation of gun based on mouse position
	playerX = x;
	playerY = y;
	adjacent = destX - x;
	opposite = destY - y;
	angle = atan((opposite / adjacent));
	spriteData.angle = angle;
	if (adjacent < 0) { // Facing back
		setX(x - 35);
		setY(y + 5);
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y + 5);
		flipHorizontal(false);
	}
	angle = atan((destY - getY()) / (destX - getX()));
	// Fire bullet
	if (shouldShoot) { // Cause AI calls this
		Projectile* p = shoot(lc, frametime);
		if (p != nullptr)
			p->setOwner(Projectile::NPC);
	} else {
		cooldownCurrent -= frametime;
	}
	Entity::update(frametime);
}

void Gun::update(float frametime, int orientation, float x, float y, Input* input, bool flip) {
	playerX = x;
	playerY = y;
	adjacent = x;
	opposite = y;
	spriteData.angle = 0;
	if (flip) { // Facing back
		setX(x - 35);
		setY(y);
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y);
		flipHorizontal(false);
	}
	// Fire bullet
	if (true) {
		// npc cannot shoot yet
	} else {
		cooldownCurrent -= frametime;
	}
	Entity::update(frametime);
}

void Gun::draw() {
	D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle));
	Entity::draw();
	/*
	OSD::instance()->addLine("Player x: " + std::to_string(playerX) + " | Player Y: " + std::to_string(playerY) + " | Mouse x: " + std::to_string(mouseX) + " |  Mouse Y: " + std::to_string(mouseY));
	OSD::instance()->addLine("Adjacent = " + std::to_string(adjacent) + " | Opposite = " + std::to_string(opposite) + " | Angle = " + std::to_string(angle));
	OSD::instance()->addLine("Normalized mouse X: " + std::to_string(mousePos.x) + " | Normalised mouse y: " + std::to_string(mousePos.y));
	OSD::instance()->addLine("Current Weapon: " + guntype + " ( " + std::to_string(ammo) + " )");
	*/
}
void Gun::collision() {
	for (int i = 0; i < bullets.size(); i++) {
		bullet = bullets.at(i);
		bullet->collision();
	}
}
bool Gun::hasAmmo() {
	return ammo > 0 || ammo == -1;
}
std::string Gun::getAmmoDisplay() {
	if (ammo == -1) {
		return "-";
	} else
		return std::to_string(ammo);
}
void Gun::addAmmo() {
	double a = (double(maxAmmo) / 100.0) * 20.0;
	int add = (int)(a);
	if (ammo < maxAmmo) {
		ammo += add;
	}
	if (ammo > maxAmmo) {
		ammo = maxAmmo;
	}
}

int Gun::getGunId() {
	return id;
}

Projectile* shoot(LevelController* lc, float frametime) {
	return nullptr;
}