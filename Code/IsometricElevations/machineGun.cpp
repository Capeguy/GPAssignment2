#include "machineGun.h"

using namespace std;
MachineGun::MachineGun() :  Gun()
{
	ammo = 150;
	maxAmmo = 150;
	//spriteData.width = playerNS::WIDTH;           // size of player ship
	//spriteData.height = playerNS::HEIGHT;
	spriteData.x = 0;                   // location on screen
	spriteData.y = 0;
	//spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	//spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = 0.2f;
	startFrame = 0;     // first frame of ship animation
	endFrame = 0;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	spriteData.scale = 0.5;
}

MachineGun::~MachineGun()
{

}
bool MachineGun::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void MachineGun::update(float frameTime, int orientation, float x, float y)
{
	
	if (orientation == 0) // right
	{
		spriteData.flipHorizontal = false;
		spriteData.x = x + 16;
		spriteData.y = y;
	}
	if (orientation == 1)
	{
		
	}
	if (orientation == 2) //left 
	{
		spriteData.flipHorizontal = true;
		spriteData.x = x - 48;
		spriteData.y = y;
	}
	if (orientation == 3)
	{
		spriteData.x = x;
		spriteData.y = y ;
	}

	Entity::update(frameTime);
}
void MachineGun::update(float frameTime)
{
	Entity::update(frameTime);
}
void MachineGun::draw()
{
	Image::draw();
}
bool MachineGun::Shoot()
{
	return false;
}
