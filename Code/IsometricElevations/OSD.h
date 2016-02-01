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
	
	
public:
	list<string> displayList;
	static OSD& instance() {
		static OSD INSTANCE;
		return INSTANCE;
	}
	void setGraphics(Graphics* graphics);
	static void addLine(string text);
	int getLine();
	void draw();

};
#endif