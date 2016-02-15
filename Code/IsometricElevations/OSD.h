//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#ifndef _OSD_H                 // Prevent multiple definitions if this 
#define _OSD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <list>
#include "graphics.h"
#include "textDX.h"

class OSD
{
private:
	int currLine = 0;
	TextDX	dxFont;


public:
	std::list<std::string> displayList;
	static OSD* instance() {
		static OSD INSTANCE;
		return &INSTANCE;
	}
	void setGraphics(Graphics* graphics);
	static void addLine(std::string text);
	int getLine();
	void draw(bool draw = true);
};
#endif