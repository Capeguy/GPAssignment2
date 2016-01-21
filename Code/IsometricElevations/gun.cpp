#include "gun.h"

using namespace std;
Gun::Gun()
{
	type = Equipable;
}

Gun::~Gun()
{

}
bool Gun::Shoot() {
	return false;
}