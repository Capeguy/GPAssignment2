#include "itemController.h"

ItemController::ItemController () {
	crateList = vector<Crate> ();
	levelCrateLoc[0].push_back (VECTOR2 (50, 50));
	levelCrateLoc[0].push_back (VECTOR2 (100, 100));
};

void ItemController::spawnCrates (int level, Game *gamePtr, TextureManager *itemTexture) {
	vector<VECTOR2> crateLoc = levelCrateLoc[level - 1];
	for (int i = 0; i < crateLoc.size (); i++) {
		Crate c = Crate ();
		c.initialize (gamePtr, itemTexture);
		c.setX (crateLoc.at (i).x);
		c.setY (crateLoc.at (i).y);
		crateList.push_back (c);
	}
}

void ItemController::update (float frameTime) {
	for (int i = 0; i < crateList.size (); i++) {
		crateList.at (i).update (frameTime);
	}
}

void ItemController::render () {
	for (int i = 0; i < crateList.size (); i++) {
		crateList.at (i).draw ();
	}
}
