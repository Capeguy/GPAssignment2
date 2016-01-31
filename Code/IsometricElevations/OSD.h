#ifndef _OSD_H                 // Prevent multiple definitions if this 
#define _OSD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <list>
#include "graphics.h"
#include "textDX.h"

using namespace std;

class OSD {

private:
	int currLine = 0;
	TextDX	dxFont;
	list<string> displayList;
public:
	OSD::OSD(Graphics* graphics);
	~OSD();
	void addLine(string text);
	int getLine();
	void draw();

};
#endif