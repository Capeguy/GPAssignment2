#include "OSD.h"

int OSD::getLine() {
	currLine++;
	return currLine;
}

void OSD::addLine(std::string text) {
	OSD::instance()->displayList.push_back(text);
}

void OSD::draw(bool draw) {
	if (draw) {
		std::string output = "";
		for each(std::string text in displayList) {
			output += text + "\n";
		}
		dxFont.print(output, 0, 0);
	}
	displayList.clear();
}
void OSD::setGraphics(Graphics* graphics) {
	dxFont.initialize(graphics, 20, true, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
}