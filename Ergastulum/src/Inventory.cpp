#include "Inventory.h"

//Constructors & Destructors
Inventory::Inventory(int size)
{
	m_size = size;
}

//Accessors
/**Gets the size of the Inventory*/
int Inventory::size()
{
	return m_size;
}

//Mutators
/**Sets the size of the Inventory*/
void Inventory::size(int size)
{
	m_size = size;
}

//Functions
/**Adds an Entity to the m_container vector*/
bool Inventory::addItem(Entity* item)
{
	m_container.push_back(item);
	return true;
}

/**Removes an Entity from the m_container vector*/
bool Inventory::removeItem(Entity* item)
{
	std::vector<Entity*>::iterator it = std::find(m_container.begin(), m_container.end(), item);
	if (it == m_container.end())
	{
		return false;
	}
	else
	{
		//PENDENTE
		return true;
	}
}