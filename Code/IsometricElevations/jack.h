#pragma once
#ifndef _JACK_H                 // Prevent multiple definitions if this 
#define _JACK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define VECTOR2     D3DXVECTOR2
#include "constants.h"
#include "npc.h"

class Jack : public NPC 
{
public:
	Jack();
	~Jack();
};
#endif