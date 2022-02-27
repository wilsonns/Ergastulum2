#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>

class Entity;

class Inventory
{
public:
	//Constructors & Destructors
	Inventory(int size);

	//Accessors
	int size();

	//Mutators
	void size(int size);

	//Functions
	bool addItem(Entity* item);
	bool removeItem(Entity* item);

private:
	std::vector<Entity*> m_container;
	int m_size;
};



#endif
