#include "gun.h"

using namespace std;
Gun::Gun()
{
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
}

Gun::~Gun()
{

}
bool Gun::initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM)
{
	return (Entity::initialize(gamePtr, width, height, ncols, textureM));
}
bool Gun::Shoot() {
	return false;
}
void Gun::update(float frametime, int orientation, float x, float y) {
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
		spriteData.y = y;
	}
	Entity::update(frametime);
}