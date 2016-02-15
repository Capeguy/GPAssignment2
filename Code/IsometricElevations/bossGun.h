//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#pragma once
#ifndef _bossGun_H                 // Prevent multiple definitions if this 
#define _bossGun_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "gun.h"

namespace bossGunNS {
	const int spacing = 32;
}

class BossGun : public Gun
{
private:

public:
	BossGun();
	~BossGun();
	void update(float frametime, int orientation, float x, float y, Input* input, LevelController* lc, float, float, bool);
	Projectile* shoot(LevelController* lc, float frametime);
};
#endif