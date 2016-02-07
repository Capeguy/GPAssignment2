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
using namespace std;


namespace gunNS
{
	const int TEXTURE_WIDTH = 136;
	const int TEXTURE_HEIGHT = 41;
	const int TEXTURE_COLS = 2;
	const int PISTOL_FRAME = 8;
	const int MACHINEGUN_FRAME = 0;
	const int SHOTGUN_FRAME = 6;
	
}

class Gun : public Item // Still an abstract class
{

protected:
	int id = -1;
	int ammo = 10;
	int maxAmmo = 10;
	float cooldown = 0;
	float cooldowncurrent = 0;
	int previousOreintation = -1;
	Projectile* bullet;
	vector<Projectile*> bullets;
	Game* gameptr;
	TextureManager* bulletTexture;
	double opposite, adjacent, angle;
	TextDX* debug; // to be taken out
	float playerX, playerY; // to be taken out 
	double mouseX, mouseY;
	string guntype;
	double damage = 0;
	float bullet_speed = 0;
public:
	enum Orientation { Right, Down, Left, Up };;
	//explicit
	Gun();
	Gun (string);
	~Gun ();
	bool initialize (Game * gamePtr, int width, int height, int ncols, TextureManager * textureM);
	virtual void shoot(LevelController* lc, float frametime) { } 
	void update (float frametime, int orientation, float x, float y, Input* input, LevelController* lc);
	void update(float frametime, int orientation, float x, float y, Input* input, bool flip);
	void draw();
	void collision();
	bool hasAmmo();
	string getAmmoDisplay();
	void addAmmo();
	int getGunId();
	enum ItemType { machineGun, shotGun, pistol };
};
#endif