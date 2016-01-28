#include "pistol.h"

using namespace std;
Pistol::Pistol () {
	ammo = -1;
	maxAmmo = -1;
}

Pistol::~Pistol () {

}
bool Pistol::Shoot () {
	return false;
}
