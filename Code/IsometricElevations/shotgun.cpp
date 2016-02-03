#include "shotgun.h"

using namespace std;
Shotgun::Shotgun () {
	ammo = 10;
	maxAmmo = 10;
	id = shotGun;
	name = "shotgun";
	guntype = "Shotgun";
	Gun();
}

Shotgun::~Shotgun () {

}
bool Shotgun::Shoot () {
	return false;
}
