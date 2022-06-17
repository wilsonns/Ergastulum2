#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>

#include "Engine.h"
#include "Entity.h"

class Item;
class Engine;
class Entity;

class Inventory
{
public:
	//Constructors & Destructors
	Inventory(int size);

	//Accessors
	int size();
	std::vector<Item*>* contents();

	//Mutators
	void size(int size);
	static void engine(Engine* engine);

	//Functions
	bool addItem(Item* item, Entity* owner = nullptr);
	bool removeItem(Item* item);

private:
	static Engine* m_engine;
	std::vector<Item*> m_container;
	int m_size;
};



#endif
