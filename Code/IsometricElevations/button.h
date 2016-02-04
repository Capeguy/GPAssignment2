#pragma once
#pragma once
#ifndef _BUTTON_H                 // Prevent multiple definitions if this 
#define _BUTTON_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC
#include "entity.h"
#include "constants.h"
#include "list.h"
#include "input.h"

using namespace std;

namespace buttonNS
{
	const int width = 400;
	const int height = 65;
	const int cols = 1;
	const int spacing = 105;
}
class Button : public Entity // Abstract class
{

protected:
	int id;
	bool clicked;
	bool hovered;
public:
	Button(int id);
	virtual ~Button();
	bool isHovered(Input* input);
	bool isClicked(Input* input);
	void update(float frameTime);
	int getID();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

};
#endif