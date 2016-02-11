#include "crate.h"

Crate::Crate() : Entity()
{
	spriteData.x = crateNS::X;              // location on screen
	spriteData.y = crateNS::Y;
	startFrame = crateNS::START_FRAME;    // first frame of crate animation
	endFrame = crateNS::END_FRAME;      // last frame of crate animation
	setCurrentFrame(startFrame);
	spriteData.rect.bottom = crateNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = crateNS::WIDTH;
	collisionType = entityNS::BOX;
	itemList = vector<Entity>();
	//itemList.push_back(new healh)
	RECT e;
	e.right = crateNS::WIDTH / 2;
	e.left = -crateNS::WIDTH / 2;
	e.bottom = crateNS::HEIGHT / 2;
	e.top = -crateNS::HEIGHT / 2;
	setEdge(e);
	//itemId = rand() % NUM_ITEMS;
	itemId = -1; //default itemID
}

void Crate::spawnItem(Crate* c)
{
	//not using this for now
	int itemId = rand() % NUM_ITEMS;
	switch (itemId)
	{
		case pistol:		
			c->setCurrentFrame(8);
			break;
		case shotGun:
			c->setCurrentFrame(6);
			break;
		case machineGun:
			c->setCurrentFrame(0);
			break;
		case healthPack:
			c->setCurrentFrame(14);
			break;
	}	
}

/*void Crate::addItem(Inventory * i, Game* gameptr, TextureManager* gunTexture, int id)
{
	InventoryItem *invItem;
	Inventory* inventory = i;
	vector<InventoryItem*>* itemList = i->getItems();
	switch (id)
	{
		case pistol:
			break;
		case shotGun:
			shotgun = new Shotgun();
			shotgun->initialize(gameptr, 136, 41, 2, gunTexture);
			shotgun->setCurrentFrame(6);
			invItem = new InventoryItem(shotgun);
			break;
		case machineGun:
			mg = new MachineGun();
			mg->initialize(gameptr, 136, 41, 2, gunTexture);
			mg->setCurrentFrame(0);
			invItem = new InventoryItem(mg);
			break;
		case healthPack:
			hp = new HealthPack();
			invItem = new InventoryItem(hp);
			break;
	}	
	for (int i = 0; i < itemList->size(); i++)
	{
		InventoryItem *iItem = itemList->at(i);
		Item* item = iItem->getItem();
		Item* newItem = invItem->getItem();			
		if (item->getItemType() == Item::Equipable && newItem->getItemType()== Item::Equipable)
		{	
			Gun* gunInvItem = dynamic_cast<Gun*>(item);				
			Gun* gunNewItem = dynamic_cast<Gun*>(newItem);
			if (gunInvItem->getGunId() == gunNewItem->getGunId())
			{
				gunInvItem->addAmmo();
				return;
			}
		}
		else if (item->getItemType() == Item::Usable && newItem->getItemType() == Item::Usable)
		{
			return;
		}
	}
	inventory->addItem(invItem);
}*/
bool Crate::initialize(Game *gamePtr, TextureManager* itemTexture, int itemtype)
{	
	setItemId(itemtype);
	return Entity::initialize(gamePtr, crateNS::WIDTH, crateNS::HEIGHT, crateNS::TEXTURE_COLS, itemTexture);
}
int Crate::getItemId()
{
	return itemId;
}

void Crate::setItemId(int i) {
	itemId = i;
}