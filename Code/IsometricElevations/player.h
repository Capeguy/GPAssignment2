#pragma once
#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "weapon.h"
#include "projectile.h"
#include "constants.h"
#include "inventory.h"
#include "gun.h"
#include "machineGun.h"
#include "shotgun.h"
#include "pistol.h"
#include "levelController.h"

namespace playerNS
{
	const int	X = 0;
	const int	Y = 0;
	const float SPEED = 200;
	const float FALLING_SPEED = 120;
	const float MASS = 300.0f;
	const float JUMP_HEIGHT = 32;
	const float JUMP_SPEED = 200;
	const int   TEXTURE_SIZE = 64;
	const int   TEXTURE_COLS = 32;
	const int   PLAYER_START_FRAME = 952;
	const int   PLAYER_END_FRAME = 955;
	const float PLAYER_ANIMATION_DELAY = 0.2f;
	const float PLAYER_WIDTH = 64.0;
	const float PLAYER_HEIGHT = 64.0;
	const int WIDTH = 32;
	const int HEIGHT = 32;
}


class Player : public Entity {
	enum PlayerOrientation { right, down, left, up };
	enum PlayerHealthStatus { Alive, Dead };
private:

	bool	doubleJump = false;

	int		orientation = right;
	int		healthStatus = Alive;
	float	hp;
	float	hpMax;
	Game*	gameptr;
	TextureManager* gunTexture;
	Inventory* inventory;
	float	jumpdistance = 0;


	MachineGun* machineGun;
	Pistol* pistol;
	Shotgun * shotgun;
	InventoryItem* defaultItem;

public:
	bool canJump = true;
	bool jumping = false;
	bool canFall = true;
	bool falling = false;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	float playerBottomLeftX;
	float playerBottomLeftY;
	float playerBottomRightX;
	float playerBottomRightY;
	float playerTopLeftX;
	float playerTopLeftY;
	float playerTopRightX;
	float playerTopRightY;



	Player ();
	~Player ();
	virtual void draw ();
	virtual bool initialize (Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update (float frameTime, LevelController* lc);
	void setFalling (bool f);
	void damage (float amt);
	void damage (Weapon w);
	void damage (Projectile p);
	void healthUpdate ();
	void die ();
	void updateCoords ();
};
#endif