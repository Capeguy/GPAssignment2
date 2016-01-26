#pragma once
#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "weapon.h"
#include "projectile.h"
#include "constants.h"

namespace playerNS
{
	const int	X = 0;   
	const int	Y = 0;
	const float SPEED = 64;                
	const float FALLING_SPEED = 32;        
	const float MASS = 300.0f;             
	const float JUMP_HEIGHT = 64;
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

class Player : public Entity
{
	enum PlayerOrientation { right, down, left, up };
	enum PlayerHealthStatus { Alive, Dead };
private:
	bool	jump = false;
	bool	doubleJump = false;
	bool	falling = false;
	int		orientation = right;
	int		healthStatus = Alive;
	float	hp;
	float	hpMax;
	Game*	gameptr;
	

public:
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;

	Player();
	~Player();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void setFalling(bool f);
	void damage(float amt);
	void damage(Weapon w);
	void damage(Projectile p);
	void healthUpdate();
	void die();
};
#endif