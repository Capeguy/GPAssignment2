#include "item.h"

using namespace std;
Item::Item () {
	textureManager = TextureManager ();
}

Item::~Item () {

}

bool Item::initialize (Game * gamePtr, int width, int height, int ncols, std::string file) {
	textureManager.initialize (gamePtr->getGraphics (), file.c_str ());
	return false;
}
