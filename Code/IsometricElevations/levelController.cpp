#include "LevelController.h"

LevelController::LevelController() {}

LevelController::LevelController(Graphics*& graphics, Game* gp, TextureManager* tt, TextureManager* pt) {
	tileTexture = tt;
	gameptr = gp;
	dxFont.initialize(graphics, 12, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	iController = new ItemController(graphics, pt);
	//npcController = new NPCController(graphics);
	projectiles = std::list<Projectile*>();
	crateCollided = 0;
	crateItem = -1;
	playerIcon.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, 2, pt);
	playerIcon.setCurrentFrame(1);
	playerIcon.setX(GAME_WIDTH*0.6);
	playerIcon.setY(50);
	playerIcon.setScale(0.5);
}

LevelController::~LevelController() {}

Tile* LevelController::getTile(float x, float y) {
	int tileX = (int)(floor(x) / TEXTURE_SIZE);
	int tileY = (int)(floor(y) / TEXTURE_SIZE);
	if (tileX < 0 || tileY < 0)
		return nullptr;
	return mapTile[tileY][tileX];
}

Tile* LevelController::getTile(VECTOR2 v) {
	int tileX = (int)(floor(v.x) / TEXTURE_SIZE);
	int tileY = (int)(floor(v.y) / TEXTURE_SIZE);
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

void LevelController::refreshTiles(float frameTime) { // For post debug
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->refresh(frameTime);
		}
	}
}

void LevelController::render(Graphics* graphics) {
	
	renderTiles(graphics);
	renderProjectiles(graphics);
	//npcController->render();
	// Render Minimap
	renderMinimap(graphics);
	playerIcon.draw();
	iController->render(mapX);
}

void LevelController::renderProjectiles(Graphics* graphics) {
	for (std::list<Projectile*>::iterator projectileIter = projectiles.begin(); projectileIter != projectiles.end(); ++projectileIter) {
		(*projectileIter)->draw(dxFont);
	}
}

void LevelController::renderTiles(Graphics* graphics) {
	std::string buffer;
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			// Scroll map according to mapX
			Tile* tile = mapTile[col][row];
			float x = (float)((row * (tileNS::TEXTURE_SIZE / 2)) + mapX);
			float y = (float)(col * (tileNS::TEXTURE_SIZE / 2));
			tile->setY(y);
			tile->setX(x);
			tile->draw();
			if (debugInfo) {
				buffer = std::to_string(mapTile[col][row]->getId());
				buffer += ":";
				buffer += std::to_string(mapTile[col][row]->isSolid());
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE);
				buffer = "(" + std::to_string(row);
				buffer += "," + std::to_string(col);
				buffer += ")";
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE + 14);
			}
		}
	}	
}

void LevelController::renderMinimap(Graphics * graphics)
{
	std::string buffer;
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			// Scroll map according to mapX
			Tile* tile = mapTile[col][row];
			tile->setScale(0.125);
			float x = (float)((row * (tileNS::TEXTURE_SIZE / 16)) + (GAME_WIDTH*0.60));
			float y = (float)(col * (tileNS::TEXTURE_SIZE / 16 ) + 50);
			tile->setY(y);
			tile->setX(x);
			tile->draw();
			if (debugInfo) {
				buffer = std::to_string(mapTile[col][row]->getId());
				buffer += ":";
				buffer += std::to_string(mapTile[col][row]->isSolid());
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE);
				buffer = "(" + std::to_string(row);
				buffer += "," + std::to_string(col);
				buffer += ")";
				dxFont.print(buffer, row * TEXTURE2_SIZE, col * TEXTURE2_SIZE + 14);
			}
			tile->setScale(1);
		}
	}
}

void LevelController::update(float frameTime, VECTOR2 pv) {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->update(frameTime);
		}
	}
	refreshTiles(frameTime);
	bool removed;
	std::list<Projectile*>::iterator projectileIter = projectiles.begin();
	while (!projectiles.empty() && projectileIter != projectiles.end()) {
		removed = false;
		if (
			(
				((*projectileIter)->getFlipHorizontal())
				&& (getTile((*projectileIter)->getX() - getMapX(), (*projectileIter)->getY())->isSolid())
				)
			||
			(
				(!(*projectileIter)->getFlipHorizontal())
				&& (getTile((*projectileIter)->getX() - getMapX() + (*projectileIter)->getWidth(), (*projectileIter)->getY())->isSolid())
				)
			) {
			(*projectileIter)->setVisible(false);
			projectileIter = projectiles.erase(projectileIter);
			removed = true;
		}
		if (!removed)
			++projectileIter;
	}

	for (std::list<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		(*it)->setX((*it)->getX() + (*it)->getVelocity().x * frameTime * (*it)->getSpeed());
		(*it)->setY((*it)->getY() + (*it)->getVelocity().y * frameTime * (*it)->getSpeed());
		(*it)->update(frameTime);
	}
	iController->update(frameTime, mapX);
	//npcController->update(frameTime);
	playerIcon.setX((pv.x*0.120) + (GAME_WIDTH*0.6) + (-mapX*0.125));
	playerIcon.setY((pv.y*0.125 + 40));
	playerIcon.update(frameTime);
}

ItemController* LevelController::getIController() {
	return iController;
}

void LevelController::collisions() {
	D3DXVECTOR2 collisionVector = D3DXVECTOR2();
	std::list<Crate*>* crateList = iController->getCrateList();
	std::list<VECTOR2>* crateLocList = iController->getCrateLoc();
	std::list<Crate*>::iterator crateIter;
	std::list<Projectile*>::iterator projectileIter = projectiles.begin();
	std::list<VECTOR2>::iterator crateLocIter = crateLocList->begin();
	int count = 0;
	bool removed = false;
	while (!projectiles.empty() && projectileIter != projectiles.end()) {
		crateIter = crateList->begin();
		removed = false;
		while (!crateList->empty() && crateIter != crateList->end() && !removed) {
			if ((*projectileIter)->collidesWith(**crateIter, collisionVector) && (*projectileIter)->getOwner() == Projectile::Player) {
				// TODO: Handle giving of items from crate to player here @Isaac
				std::advance(crateLocIter, count); //here2
				setCrateCollided(1);
				setCrateItem((*crateIter)->getItemId());
				crateIter = crateList->erase(crateIter);
				projectileIter = projectiles.erase(projectileIter);
				crateLocIter = crateLocList->erase(crateLocIter);
				
				removed = true;
			} else {
				++crateIter;
				count++;
			}
			if (count + 1 > crateLocList->size()) {
				count = 0;
			}
		}
		if (!removed)
			++projectileIter;
	}
}

void LevelController::addProjectile(Projectile* p) {
	projectiles.push_back(p);
}

int LevelController::collidedWithCrate() {
	return crateCollided;
}

void LevelController::setCrateCollided(int col) {
	crateCollided = col;
}

void LevelController::setCrateItem(int itemtype) {
	crateItem = itemtype;
}

int LevelController::getCrateItem() {
	return crateItem;
}

void LevelController::setMapX(float x) {
	mapX -= x;
}

float LevelController::getMapX() {
	return mapX;
}

void LevelController::releaseJack() {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			// Scroll map according to mapX
			Tile* tile = mapTile[col][row];
			if (tile->getId() == 392) {
				tile->setId(215);
				tile->setSolid(false);
				tile->initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tileTexture);
			}
		}
	}
}
