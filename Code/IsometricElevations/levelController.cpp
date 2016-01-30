#include "LevelController.h"

LevelController::LevelController() {}

LevelController::LevelController(Graphics*& graphics, Game* gp, TextureManager* tt) {
	tileTexture = tt;
	gameptr = gp;
	dxFont.initialize(graphics, 12, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	iController = new ItemController(graphics);
	projectiles = list<Projectile*>();
}

LevelController::~LevelController() {}

Tile* LevelController::getTile(float x, float y) {
	int tileX = (int)(floor(x) / TEXTURE_SIZE);
	int tileY = (int)(floor(y) / TEXTURE_SIZE);
	return mapTile[tileY][tileX];
}
void LevelController::loadTiles(TextureManager* tt, Game* gameptr) {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			Tile* t = new Tile(tileMap[col][row], tileSolid[tileMap[col][row]][1]);
			mapTile[col][row] = t;
			mapTile[col][row]->initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tt);
			mapTile[col][row]->spriteData.height = 32;
			mapTile[col][row]->spriteData.width = 32;
			mapTile[col][row]->setCurrentFrame(tileMap[col][row]);
			mapTile[col][row]->setX(row * TEXTURE2_SIZE);
			mapTile[col][row]->setY(col * TEXTURE2_SIZE);
		}
	}
	iController->spawnCrates(1, gameptr);

}
void LevelController::render(Graphics* graphics) {
	renderTiles(graphics);
	renderProjectiles(graphics);
}
void LevelController::renderProjectiles(Graphics* graphics) {
	for (std::list<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		(*it)->draw();
	}
}
void LevelController::renderTiles(Graphics* graphics) {
	string buffer;
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->draw();
			if (debugInfo) {
				buffer = to_string(mapTile[col][row]->getId());
				buffer += ":";
				buffer += to_string(mapTile[col][row]->isSolid());
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE);
				buffer = "(" + to_string(row);
				buffer += "," + to_string(col);
				buffer += ")";
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE + 14);
			}
		}
	}
	iController->render();
}

void LevelController::update(float frameTime) {

	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->update(frameTime);
		}
	}
	iController->update(frameTime);
	for (list<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		Projectile* bullet = (*it);
		bullet->setX(bullet->getX() + bullet->getVelocity().x * frameTime);
		bullet->setY(bullet->getY() + bullet->getVelocity().y * frameTime);
		bullet->update(frameTime);
	}
}

ItemController* LevelController::getIController() {
	return iController;
}

void LevelController::collisions() {
	D3DXVECTOR2 collisionVector = D3DXVECTOR2();
	list<Crate*>* crateList = iController->getCrateList();
	list<Crate*>::iterator cit; 
	list<Projectile*>::iterator it = projectiles.begin();
	bool removed = false;
	while (!projectiles.empty() && it != projectiles.end()) {
	//for (list<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		cit = crateList->begin();
		removed = false;
		while (!crateList->empty() && cit != crateList->end() && !removed) {
			if ((*it)->collidesWith(**cit, collisionVector)) {
				// TODO: Handle giving of items from crate to player here @Isaac
				cit = crateList->erase(cit);
				it = projectiles.erase(it);
				removed = true;
			} else {
				++cit;
			}
		}
		if (!removed) 
			++it;
	}
}
void LevelController::addProjectile(Projectile* p) {
	projectiles.push_back(p);
}
