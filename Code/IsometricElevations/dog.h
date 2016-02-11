#pragma once
#ifndef _DOG_H                 // Prevent multiple definitions if this 
#define _DOG_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

class Dog : public NPC 
{
public:
	Dog();
	~Dog();
};
#endif