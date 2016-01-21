#pragma once
#ifndef _NPC_H                 // Prevent multiple definitions if this 
#define _NPC_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "entity.h"
#include "item.h"

using namespace std;

namespace npcNS
{

}

class NPC : Entity // Still an abstract class
{
protected:

public:
	//explicit
	NPC();
	~NPC();
};
#endif