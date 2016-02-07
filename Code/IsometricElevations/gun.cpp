#include "gun.h"

using namespace std;
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
	bullets = vector<Projectile*>();
}

Gun::~Gun() {

}
bool Gun::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM) {
	gameptr = gamePtr;
	bulletTexture = new TextureManager();
	debug = new TextDX();
	debug->initialize(gamePtr->getGraphics(), 20, false, false, "Courier New");
	if (!bulletTexture->initialize(gamePtr->getGraphics(), TEXTURE_BULLETS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}
/*
Projectile * Gun::shoot(LevelController * lc, float frametime) {
	return nullptr;
}
*/
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
	if (adjacent < 0) // facing back
	{
		setX(x - 20);
		setY(y + 5);
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y + 5);
		flipHorizontal(false);
	}
	//fire bullet
	if (input->getMouseLButton()) {
		shoot(lc, frametime);
	} else {
		cooldowncurrent -= frametime;
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
	if (adjacent < 0) // facing back
	{
		setX(x - 20);
		setY(y + 5);
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y + 5);
		flipHorizontal(false);
	}
	//fire bullet
	if (shouldShoot) { // Cause AI calls this
		Projectile* p = shoot(lc, frametime);
		if (p != nullptr)
			p->setOwner(Projectile::NPC);
	} else {
		cooldowncurrent -= frametime;
	}
	Entity::update(frametime);
}

void Gun::update(float frametime, int orientation, float x, float y, Input* input, bool flip) {
	// We should not have 2 update functions omgwtfbbq - Ben
	//edit this to make the npc's gun awesome -clarence
	// Gun's flipping for NPC - Ben
	//npc's gun not flipping currently -- Fixed

	//change orientation of gun based on mouse position
	playerX = x;
	playerY = y;
	//mouseX = input->getMouseX();
	//mouseY = input->getMouseY();
	adjacent = x;
	opposite = y;
	//angle = atan((opposite / adjacent)); // npc's gun is facing straight
	spriteData.angle = 0;
	if (flip) // facing back
	{
		setX(x - 35);
		setY(y);
		//setX(x - 20); //follow mouse
		//setY(y);	//follow mouse
		flipHorizontal(true);
	} else {
		setX(x);
		setY(y);
		flipHorizontal(false);
	}
	//fire bullet
	if (true) {
		// npc cannot shoot yet
	}
	/*
	if (input->getMouseLButton())
	{
		shoot(lc, frametime);
	}
	*/
	else {
		cooldowncurrent -= frametime;
	}
	Entity::update(frametime);
}

void Gun::draw() {
	D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle));
	Entity::draw();
	/*
	OSD::instance()->addLine("Player x: " + to_string(playerX) + " | Player Y: " + to_string(playerY) + " | Mouse x: " + to_string(mouseX) + " |  Mouse Y: " + to_string(mouseY));
	OSD::instance()->addLine("Adjacent = " + to_string(adjacent) + " | Opposite = " + to_string(opposite) + " | Angle = " + to_string(angle));
	OSD::instance()->addLine("Normalized mouse X: " + to_string(mousePos.x) + " | Normalised mouse y: " + to_string(mousePos.y));
	OSD::instance()->addLine("Current Weapon: " + guntype + " ( " + to_string(ammo) + " )");
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
string Gun::getAmmoDisplay() {
	if (ammo == -1) {
		return "?";
	} else
		return to_string(ammo);
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