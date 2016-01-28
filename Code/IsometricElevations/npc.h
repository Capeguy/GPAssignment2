#pragma once
#ifndef _NPC_H                 // Prevent multiple definitions if this 
#define _NPC_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2

#include "constants.h"
#include "entity.h"
#include "item.h"
#include "constants.h"
#include "weapon.h"
#include "projectile.h"
#include "inventory.h"
#include "gun.h"
#include "machineGun.h"
#include "shotgun.h"
#include "pistol.h"
#include "levelController.h"

using namespace std;

namespace npcNS
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
	const int   NPC_START_FRAME = 952;
	const int   NPC_END_FRAME = 955;
	const float NPC_ANIMATION_DELAY = 0.2f;
	const float NPC_WIDTH = 64.0;
	const float NPC_HEIGHT = 64.0;
}

class NPC : public Entity // Still an abstract class
{
	enum NPCOrientation { right, down, left, up };
	enum NPCHealthStatus { Alive, Dead };
protected:
	bool	jump = false;
	bool	doubleJump = false;
	int		orientation = right;
	int		healthStatus = Alive;
	float	hp;
	float	hpMax;
	Game*	gameptr;
	TextureManager gunTexture;
	MachineGun machineGun;
	Pistol	pistol;
	Shotgun shotgun;
	Inventory inventory;
	float	jumpdistance = 0;
	VECTOR2 startPoint;
	VECTOR2 endPoint;

public:
	bool canJump = true;
	bool jumping = false;
	bool canFall = true;
	bool falling = false;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;

	float npcBottomLeftX;
	float npcBottomLeftY;
	float npcBottomRightX;
	float npcBottomRightY;
	float npcTopLeftX;
	float npcTopLeftY;
	float npcTopRightX;
	float npcTopRightY;
	//explicit
	NPC();
	~NPC();

	//	inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, LevelController* lc);
	void moveLeft(float frameTime);
	void moveRight(float frameTime);
	void moveUp(float frameTime);
	void moveDown(float frameTime);
	void ai(float frameTime, Entity & ent);
	void setFalling(bool f);
	void damage(float amt);
	void damage(Weapon w);
	void damage(Projectile p);
	void healthUpdate();
	void die();
	void updateCoords();
};
#endif