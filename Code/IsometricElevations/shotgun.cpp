#include "shotgun.h"

using namespace std;
Shotgun::Shotgun () {
	ammo = 10;
	maxAmmo = 10;
	name = "shotgun";
	Gun();
}

Shotgun::~Shotgun () {

}
bool Shotgun::Shoot () {
	return false;
}
