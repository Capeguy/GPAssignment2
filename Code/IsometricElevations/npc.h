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
#include "npcController.h"
// TODO: Create an NPCController to control the spawning of NPCs
using namespace std;

namespace npcNS
{
	const int	X = 0;
	const int	Y = 0;
	const float SPEED = 32 * 400;
	const float FALLING_SPEED = 32 * 200;
	const float MASS = 300.0f;
	const float JUMP_HEIGHT = 32 * 2;
	const float JUMP_SPEED = 32 * 400;
	const int   TEXTURE_SIZE = 64;
	const int   TEXTURE_COLS = 32;
	const int   NPC_START_FRAME = 568;
	const int   NPC_END_FRAME = 571;
	const float NPC_ANIMATION_DELAY = 0.2f;
	const float NPC_WIDTH = 64.0;
	const float NPC_HEIGHT = 64.0;
	const int NPC_HEALTH_WIDTH = 30;
	const int NPC_HEALTH_HEIGHT = 4;
	const int NPC_HEALTHBACK_WIDTH = 32;
	const int NPC_HEALTHBACK_HEIGHT = 6;
}

class NPC : public Entity 
{
	enum NPCOrientation { Right, Down, Left, Up };
	enum NPCHealthStatus { Alive, Dead };
protected:
	bool	jump = false;
	bool	doubleJump = false;
	int		orientation = Left;
	int		healthStatus = Alive;
	float	hp = 10;
	float	hpMax = 10;
	Game*	gameptr;
	TextureManager npcTexture;
	TextureManager* npcHealthTexture;
	TextureManager* npcHealthBackTexture;
	Image* npcHealth;
	Image* npcHealthBack;

	MachineGun machineGun;
	Pistol	pistol;
	Shotgun shotgun;
	Inventory inventory;
	float	jumpdistance = 0;
	VECTOR2 startPoint;
	VECTOR2 endPoint;
	VECTOR2 currLoc;
	VECTOR2 currDest;
	int pathCount;
	vector <VECTOR2> pathList;
	float originX;
	float originY;


public:
	bool canJump = true;
	bool jumping = false;
	bool canFall = true;
	bool falling = false;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool dying = false;
	//int spriteNumber = -1; 
	float mapX = 0;
	float pVelocity = 0;
	//explicit
	NPC();
	~NPC();

	//	inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, float mapX, float pVelo); // , LevelController* lc);
	void moveLeft(float frameTime, float);
	void moveRight(float frameTime, float);
	void moveUp(float frameTime);
	void moveDown(float frameTime);
	void ai(float frameTime, Entity & ent, float mapX);
	// TODO: Make NPC AI walk between 2 points / cycle between points in a vector array
	void setFalling(bool f);
	void damage(float amt);
	void damage(Weapon w);
	void damage();
	void healthUpdate();
	void die();
	void setDying(bool d);
	bool isDying();
	void addPath(VECTOR2 v);
	int getHP();
	int getMaxHP();
	void setMapX(float x);
};
#endif