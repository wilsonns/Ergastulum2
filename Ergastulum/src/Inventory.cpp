#include "Inventory.h"

#include "Color.h"
#include "Engine.h"
#include "GUI.h"
#include "Menu.h"
#include "Item.h"

Engine* Inventory::m_engine;

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


std::vector<Item*>* Inventory::contents()
{
	return &m_container;
}


//Mutators
/**Sets the size of the Inventory*/
void Inventory::size(int size)
{
	m_size = size;
}

void Inventory::engine(Engine* engine)
{
	m_engine = engine;
}
//Functions
/**Adds an Entity to the m_container vector*/
bool Inventory::addItem(Item* item, Entity* owner)
{
	if (m_container.size() + 1 < m_size)
	{
		m_container.push_back(item);
		if (owner != nullptr)
		{
			m_engine->gui()->menu("gameInterface")->addMessage(owner->name() + " gets the " + item->name() + " from the ground.",
				m_engine->gui()->font("Arial"), Color::Black, Color::Black);
		}
		item->owner(owner);
		return true;
	}
	else
	{
		if(owner != nullptr || owner != NULL)
		{
			m_engine->gui()->menu("gameInterface")->addMessage("Inventory full.",
			m_engine->gui()->font("Arial"), Color::Black, Color::Black);
		}
		return false;
	}
}

/**Removes an Entity from the m_container vector*/
bool Inventory::removeItem(Item* item)
{
	std::vector<Item*>::iterator it = std::find(m_container.begin(), m_container.end(), item);
	if (it == m_container.end())
	{
		return false;
	}
	else
	{
		m_container.erase(it);
		return true;
	}
}