#include "Item.h"

int Item::m_spriteSize;

//Constructors & Destructors
Item::Item(sf::String name, sf::Vector2i pos, sf::Sprite sprite, int size, int weight, Entity* owner)
{
	this->m_name = name;
	if (owner == nullptr)
	{
		this->m_pos = pos;
	}
	else
	{
		this->m_pos = owner->pos();
	}

	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)(this->m_pos.x * m_spriteSize),
		(float)(this->m_pos.y * m_spriteSize));

	this->m_size = size;
	this->m_weight = weight;
	
	std::cout << "Item created. " << std::endl;
}

Item::~Item()
{
	std::cout << "Item destroyed." << std::endl;
}

//Accessors
/**Returns m_size.*/
int Item::size()
{
	return m_size;
}

/**Returns m_weight.*/
int Item::weight()
{
	return m_weight;
}

//Mutators
/**Sets m_size.*/
void Item::size(int size)
{
	m_size = size;
}

/**Sets m_weight.*/
void Item::weight(int weight)
{
	m_weight = weight;
}

//Functions
bool Item::use(Entity* owner)
{
	//PENDING
	return true;
}