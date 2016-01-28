#include "itemController.h"

ItemController::ItemController()
{
}

ItemController::ItemController(Graphics *graphics)
{
	// item texture initialize
	itemTexture = new TextureManager();
	if (!itemTexture->initialize(graphics, TEXTURE_ITEM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing item texture"));
	crateList = vector<Crate*>();
	levelCrateLoc[0].push_back(VECTOR2(321, 508));
	levelCrateLoc[0].push_back(VECTOR2(652, 704));
};

void ItemController::spawnCrates(int level, Game *gamePtr)
{
	vector<VECTOR2> crateLoc = levelCrateLoc[level - 1];
	for (int i = 0; i < crateLoc.size(); i++)
	{
		Crate* c = new Crate();
		c->initialize(gamePtr, itemTexture);
		c->setX(crateLoc.at(i).x);
		c->setY(crateLoc.at(i).y);
		crateList.push_back(c);
	}
}

void ItemController::update(float frameTime)
{
	for (int i = 0; i < crateList.size(); i++)
	{
		crateList.at(i)->update(frameTime);
	}
}

void ItemController::render()
{
	for (int i = 0; i < crateList.size(); i++)
	{
		Crate* c = crateList.at(i);
		c->draw();
	}
}

/*void ItemController::collisions(Player *player)
{
	VECTOR2 collisionVector;
	/*for (int i = 0; i < crateList.size(); i++)
	{
		Crate* c = crateList.at(i);
		if (player->collidesWith(c, collisionVector)) 
		{
			player->bounce(collisionVector, c);
		}
	}
	
	}
}*/
