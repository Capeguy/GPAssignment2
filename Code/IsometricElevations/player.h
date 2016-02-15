//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

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

namespace playerNS {
	const int	X = 0;
	const int	Y = 0;
	const float SPEED = 32 * 600;
	const float NOCLIP_SPEED = 32 * 300 * 10;
	const float FALLING_SPEED = 32 * 400;
	const float MASS = 300.0f;
	const float JUMP_HEIGHT = 32 * 2;
	const float JUMP_SPEED = 32 * 400;
	const int   TEXTURE_SIZE = 64;
	const int   TEXTURE_COLS = 32;
	const int   PLAYER_START_FRAME = 952;
	const int   PLAYER_END_FRAME = 955;
	const float PLAYER_ANIMATION_DELAY = 0.2f;
	const float PLAYER_WIDTH = 64.0;
	const float PLAYER_HEIGHT = 64.0;
	const int WIDTH = 32;
	const int HEIGHT = 32;
	const enum ItemType { machineGun, shotGun, pistol };
}

class Player : public Entity
{
private:
	bool	doubleJump = false;
	int		orientation = Right;
	int		healthStatus = Alive;
	int		totalPoints = 0;
	float	hp;
	float	hpMax;
	Game*	gameptr;
	TextureManager* gunTexture;
	Inventory* inventory;
	float	jumpdistance = 0;
	float	jumpOriginY;
	float velocityX = getVelocity().x;
	float velocityY = getVelocity().y;
	MachineGun* machineGun;
	Pistol* pistol;
	Shotgun * shotgun;
	InventoryItem* defaultItem;
	LevelController* levelController;
	VECTOR2 spawnPos = VECTOR2(GAME_WIDTH / 2, 64);
	bool noClipButtonReleased = true;

public:
	enum PlayerOrientation { Right, Down, Left, Up };
	enum PlayerHealthStatus { Alive, Dead };
	bool noClip = false;
	bool canJump = true;
	bool jumping = false;
	bool canFall = true;
	bool falling = false;

	Player();
	~Player();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, LevelController* lc);
	void setFalling(bool f);
	void damage(float amt);
	void healthUpdate();
	void die();
	void setTotalPoints(int);
	float getHP();
	float getMaxHP();
	Inventory* getInventory();
	Game* getGamePtr();
	TextureManager* getTexture();
	bool canMoveUp(bool);
	bool canMoveDown(bool);
	bool canMoveLeft(bool);
	bool canMoveRight(bool);
	int getHealthStatus();
	int	getTotalPoints();
	float getPlayerVelocity();
	void setHealth(float);
};
#endif