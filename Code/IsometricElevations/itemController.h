#pragma once
#ifndef _ITEMCONTROLLER_H                 // Prevent multiple definitions if this 
#define _ITEMCONTROLLER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "item.h"
#include "entity.h"
#include "crate.h"
using namespace std;
namespace itemControllerNS
{
}

class ItemController : public Entity
{
public:
	ItemController();
	void initializeItems();
	void spawnCrates();
};
#endif