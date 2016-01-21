#include "machineGun.h"

using namespace std;
MachineGun::MachineGun()
{
	ammo = 150;
	maxAmmo = 150;
}

MachineGun::~MachineGun()
{

}
bool MachineGun::Shoot()
{
	return false;
}
