#include "machineGun.h"

using namespace std;
MachineGun::MachineGun () : Gun () {
	ammo = 100;
	maxAmmo = 150;
	id = machineGun;
	name = "machineGun";
	Gun ();
}

MachineGun::~MachineGun () {

}
