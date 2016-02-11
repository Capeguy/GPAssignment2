#include "Minimap.h"

Minimap::Minimap() {}

Minimap::Minimap(Graphics*& graphics, Game* gp, TextureManager* tt) {
	tileTexture = tt;
	gameptr = gp;
	dxFont.initialize(graphics, 12, false, false, "Courier New");
	dxFont.setFontColor(SETCOLOR_ARGB(192, 255, 255, 255));
}

Minimap::~Minimap() {}

Tile* Minimap::getTile(float x, float y) {
	int tileX = (int)(floor(x) / TEXTURE_SIZE);
	int tileY = (int)(floor(y) / TEXTURE_SIZE);
	return mapTile[tileY][tileX];
}

Tile* Minimap::getTile(VECTOR2 v) {
	int tileX = (int)(floor(v.x) / TEXTURE_SIZE);
	int tileY = (int)(floor(v.y) / TEXTURE_SIZE);
	return mapTile[tileY][tileX];
}

void Minimap::loadTiles(TextureManager* tt, Game* gameptr) {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			Tile* t = new Tile(tileMap[col][row], tileSolid[tileMap[col][row]][1]);
			mapTile[col][row] = t;
			mapTile[col][row]->initialize(gameptr, TEXTURE2_SIZE, TEXTURE2_SIZE, TEXTURE2_COLS, tt);
			mapTile[col][row]->spriteData.height = 4;
			mapTile[col][row]->spriteData.width = 4;
			mapTile[col][row]->setCurrentFrame(tileMap[col][row]);
			mapTile[col][row]->setX(row * TEXTURE2_SIZE);
			mapTile[col][row]->setY(col * TEXTURE2_SIZE);
		}
	}
}

void Minimap::render(Graphics* graphics) {
	renderTiles(graphics);
}

void Minimap::renderTiles(Graphics* graphics) {
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

void Minimap::update(float frameTime) {
	for (int col = 0; col < MAP_SIZE_Y; col++) {
		for (int row = 0; row < MAP_SIZE_X; row++) {
			mapTile[col][row]->update(frameTime);
		}
	}
}


void Minimap::collisions() {}

void Minimap::setMapX(float x)
{
	mapX -= x;
}

float Minimap::getMapX()
{
	return mapX;
}
