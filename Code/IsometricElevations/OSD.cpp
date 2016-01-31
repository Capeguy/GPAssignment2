#include "OSD.h"

using namespace std;


int OSD::getLine() {
	currLine++;
	return currLine;
}

void OSD::addLine(string text) {
	// OSD::instance.displayList.push_back(text);
}

void OSD::draw() {
	string output = "";
	for each(string text in displayList) {
		output += text + "\n";
	}
	dxFont.print(output, 0, 0);
	displayList.clear();
}
void OSD::setGraphics(Graphics* graphics) {
	dxFont.initialize(graphics, 20, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 0, 0, 0));
}