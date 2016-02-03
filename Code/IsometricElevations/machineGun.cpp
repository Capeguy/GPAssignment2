#include "machineGun.h"

using namespace std;
MachineGun::MachineGun () : Gun () {
	ammo = 100;
	maxAmmo = 150;
	id = machineGun;
	cooldown = 0.2f;
	name = "machineGun";
	guntype = "Machine Gun";
	Gun ();
}

MachineGun::~MachineGun () {

}
void MachineGun::draw() {
	
}