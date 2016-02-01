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
bool Gun::Shoot() {
	return false;
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
	if (adjacent < 0) // facing back
	{
		setX(x - 16);
		setY(y);
		flipHorizontal(true);
	}
	else
	{
		setX(x);
		setY(y);
		flipHorizontal(false);
	}
	//fire bullet
	if (input->isKeyDown(VK_SHIFT)) {
		if (cooldowncurrent <= 0 && hasAmmo()) {
			if (ammo != -1)
				ammo--;
			gameptr->console->print("Remaining ammo: ");
			gameptr->console->print(to_string(ammo));
			cooldowncurrent = cooldown;
			bullet = new Projectile();
			bullet->initialize(gameptr, 32, 32, 1, bulletTexture);
			bullet->setCurrentFrame(1);
			bullet->setX(getX());
			bullet->setY(getY());
			bullet->spriteData.angle = angle;
			D3DXVECTOR2 mousePos = D3DXVECTOR2(cos(angle), sin(angle)); // normalize the vector idk what but it works lol
			if (adjacent >= 0)
			{
				bullet->setVelocity(mousePos);
				bullet->spriteData.angle = angle;
			}
			else
			{
				bullet->setVelocity(-mousePos);
			}
				
			/*
			if (orientation == Right) 
			{
				bullet->setVelocity(D3DXVECTOR2(100, 0));
				bullet->setX(getX() + gunNS::TEXTURE_WIDTH);
				bullet->setY(getY());
			} 
			else if (orientation == Left)
			{
				bullet->setVelocity(D3DXVECTOR2(-100, 0));
				bullet->setX((getX() - gunNS::TEXTURE_WIDTH));
				bullet->setY(getY());
			}
			else if (orientation == Up)
			{
				bullet->setVelocity(D3DXVECTOR2(0, -100));
				bullet->spriteData.angle = -PI / 2;
			}
			else if (orientation == Down)
			{
				bullet->setVelocity(D3DXVECTOR2(0, 100));
				bullet->spriteData.angle = PI / 2;
			}
			*/
			lc->addProjectile(bullet);
			bullets.push_back(bullet);
		} else {
			cooldowncurrent -= frametime;
		}
	} else {
		cooldowncurrent -= frametime;
	}
	/* Hmm
	for (int i = 0; i < bullets.size(); i++) {
		bullet = bullets.at(i);
		bullet->setX(bullet->getX() + bullet->getVelocity().x * frametime);
		bullet->setY(bullet->getY() + bullet->getVelocity().y * frametime);
		bullet->update(frametime);
	}
	*/
		
	/*
	if (orientation == Up) { // up
		//spriteData.x = x;
		//spriteData.y = y;
		setX(x- 16);
		setY(y- 16);
		if (previousOreintation == Right)
			spriteData.angle = -PI / 2;
		else if (previousOreintation == Left)
			spriteData.angle = PI / 2;
		else if (previousOreintation == Down)
			spriteData.angle = 3 * PI / 2;
	}
	if (orientation == Right) // right
	{
		flipHorizontal(false);
		setX(x + 16);
		setY(y);
		spriteData.angle = angle;
	}
	if (orientation == Down) { //down
		setX(x - 16);
		setY(y + 16);
		if (previousOreintation == Right)
			spriteData.angle = -3 * PI / 2;
		else if (previousOreintation == Left)
			spriteData.angle = 3 * PI / 2;
		else if (previousOreintation == Up)
			spriteData.angle = PI / 2;
	}
	if (orientation == Left) //left 
	{
		flipHorizontal(true);
		setX(x - 48);
		setY(y);
		spriteData.angle = angle;
	}
	*/
	previousOreintation = orientation;
	Entity::update(frametime);
}
void Gun::draw() {
	string text = "Player x: " + to_string(playerX) + " | Player Y: " + to_string(playerY) + " | Mouse x: " + to_string(mouseX) + " |  Mouse Y: " + to_string(mouseY) + "\n";
	text += "Adjacent = " + to_string(adjacent) + " | Opposite = " + to_string(opposite) + " | Angle = " + to_string(angle);
	debug->print(text, 0, 0);
	Entity::draw();
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
void Gun::addAmmo()
{
	double a = (double(maxAmmo) / 100.0) * 20.0;
	int add = (int)(a);
	if (ammo < maxAmmo)
	{
		ammo += add;
	}
	if (ammo > maxAmmo)
	{
		ammo = maxAmmo;
	}
}

int Gun::getGunId()
{
	return id;
}
