#include "LevelController.h"

LevelController::LevelController() {}

LevelController::LevelController(Graphics*& graphics, Game* gp, TextureManager* tt) {
	tileTexture = tt;
	gameptr = gp;
	dxFont.initialize(graphics, 12, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
	iController = new ItemController(graphics);
	//npcController = new NPCController(graphics);
	projectiles = list<Projectile*>();
	crateCollided = 0;
	crateItem = -1;
}

LevelController::~LevelController() {}

Tile* LevelController::getTile(float x, float y) {
	int tileX = (int)(floor(x) / TEXTURE_SIZE);
	int tileY = (int)(floor(y) / TEXTURE_SIZE);
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
	iController->spawnCrates(1, gameptr, levelControllerNS::ItemType::machineGun);
}

void LevelController::render(Graphics* graphics) {
	renderTiles(graphics);
	renderProjectiles(graphics);
	//npcController->render();
}

void LevelController::renderProjectiles(Graphics* graphics) {
	for (std::list<Projectile*>::iterator projectileIter = projectiles.begin(); projectileIter != projectiles.end(); ++projectileIter) {
		(*projectileIter)->draw();
	}
}

void LevelController::renderTiles(Graphics* graphics) {
	string buffer;
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
	iController->render(mapX);
}

void LevelController::update(float frameTime) {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->update(frameTime);
		}
	}
	for (list<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		Projectile* bullet = (*it);
		bullet->setX(bullet->getX() + bullet->getVelocity().x * frameTime * bullet->getSpeed());
		bullet->setY(bullet->getY() + bullet->getVelocity().y * frameTime * bullet->getSpeed());
		bullet->update(frameTime);
	}
	iController->update(frameTime);
	//npcController->update(frameTime);
}

ItemController* LevelController::getIController() {
	return iController;
}

void LevelController::collisions() {
	D3DXVECTOR2 collisionVector = D3DXVECTOR2();
	list<Crate*>* crateList = iController->getCrateList();
	list<VECTOR2>* crateLocList = iController->getCrateLoc();
	list<Crate*>::iterator crateIter;
	list<Projectile*>::iterator projectileIter = projectiles.begin();
	list<VECTOR2>::iterator crateLocIter = crateLocList->begin();
	int count = 0;
	bool removed = false;
	while (!projectiles.empty() && projectileIter != projectiles.end()) {
		crateIter = crateList->begin();
		removed = false;
		while (!crateList->empty() && crateIter != crateList->end() && !removed) {
			if ((*projectileIter)->collidesWith(**crateIter, collisionVector) && (*projectileIter)->getOwner() == Projectile::Player) {
				// TODO: Handle giving of items from crate to player here @Isaac
				std::advance(crateLocIter, count);
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
			if (count+1 > crateLocList->size())
			{
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

int LevelController::collidedWithCrate()
{
	return crateCollided;
}

void LevelController::setCrateCollided(int col)
{
	crateCollided = col;
}

void LevelController::setCrateItem(int itemtype) {
	crateItem = itemtype;
}

int LevelController::getCrateItem() {
	return crateItem;
}
void LevelController::setMapX(float x)
{
	mapX -= x;
}

float LevelController::getMapX()
{
	return mapX;
}
