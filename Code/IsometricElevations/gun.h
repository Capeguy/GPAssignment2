#pragma once
#ifndef _GUN_H                 // Prevent multiple definitions if this 
#define _GUN_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "item.h"
#include <vector>
#include "projectile.h"
#include "list.h"
#include "levelController.h"
using namespace std;

/*
namespace gunNS
{
	int TEXTURE_WIDTH = 67;
	int TEXTURE_HEIGHT = 41;
	int TEXTURE_COLS = 2;
}
*/

class Gun : public Item // Still an abstract class
{

protected:
	int id = 0;
	int ammo = 10;
	int maxAmmo = 10;
	float cooldown = 0.2f;
	float cooldowncurrent = 0;
	Projectile* bullet;
	vector<Projectile*> bullets;
	Game* gameptr;
	TextureManager* bulletTexture;
public:

	//explicit
	Gun ();
	~Gun ();
	bool initialize (Game * gamePtr, int width, int height, int ncols, TextureManager * textureM);
	bool Shoot(); // Deprecated
	void update (float frametime, int orientation, float x, float y, Input* input, LevelController* lc);
	void draw();
	void collision();
	bool hasAmmo();
	string getAmmoDisplay();
	void addAmmo();
	int getGunId();
	enum ItemType { machineGun, shotGun, pistol };
};
#endif