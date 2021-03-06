//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _GUN_H                 // Prevent multiple definitions if this 
#define _GUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "item.h"
#include <vector>
#include "projectile.h"
#include "OSD.h"
#include "list.h"
#include "levelController.h"

namespace gunNS {
	const int TEXTURE_WIDTH = 136;
	const int TEXTURE_HEIGHT = 41;
	const int TEXTURE_COLS = 2;
	const int PISTOL_FRAME = 8;
	const int MACHINEGUN_FRAME = 0;
	const int SHOTGUN_FRAME = 6;
	const int PISTOL_OFFSET = 20;
	const int MACHINEGUN_OFFSET = 48;
	const int SHOTGUN_OFFSET = 48;
}

class Gun : public Item // Still an abstract class
{

protected:
	int id = -1;
	int ammo = 10;
	int maxAmmo = 10;
	float cooldown = 0;
	float cooldownCurrent = 0;
	int previousOreintation = -1;
	Projectile* bullet;
	std::vector<Projectile*> bullets;
	Game* gameptr;
	TextureManager* bulletTexture;
	double opposite, adjacent, angle;
	TextDX* debug; // to be taken out
	float playerX, playerY; // to be taken out 
	double mouseX, mouseY;
	std::string guntype;
	double damage = 0;
	float bullet_speed = 0;
public:
	enum Orientation { Right, Down, Left, Up };
	enum ItemType { machineGun, shotGun, pistol };
	Gun();
	~Gun();
	bool initialize(Game * gamePtr, int width, int height, int ncols, TextureManager * textureM);
	virtual Projectile* shoot(LevelController* lc, float frametime) { return nullptr; };
	virtual void setCooldown(float) {};
	virtual void update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc);
	virtual void update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc, float, float, bool);
	void update(float frametime, int orientation, float x, float y, Input* input, bool flip);
	void draw();
	void collision();
	bool hasAmmo();
	std::string getAmmoDisplay();
	void addAmmo();
	int getGunId();
};
#endif