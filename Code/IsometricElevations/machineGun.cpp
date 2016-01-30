#include "machineGun.h"

using namespace std;
MachineGun::MachineGun () : Gun () {
	ammo = 150;
	maxAmmo = 150;
	name = "machineGun";
	Gun ();
}

MachineGun::~MachineGun () {

}
