#include "Item.h"

#include "Engine.h"
#include "Stats.h"
#include "Character.h"
#include "GUI.h"
#include "RNG.h"
#include "Menu.h"
#include "GameInterface.h"
#include "InventoryMenu.h"
#include "Color.h"
#include "Inventory.h"

//Constructors & Destructors
Item::Item(sf::String name, sf::Vector2i pos, sf::Sprite sprite, AttributeComponent attributes, Entity* owner)
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
		(float)(this->m_pos.y * m_spriteSize));	/*Sets the sf::Sprite position as a float value*/
		
	std::cout << "Item created. " << std::endl;
}

Item::Item(const json& file, sf::String name, sf::Vector2i pos)
{

	this->m_name = file.at(name).at("name");
	this->m_pos = pos;
	this->m_sprite = m_engine->sprite(file.at(name).at("sprite"), "Items");
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
	this->m_slot = file.at(name).at("type");
	//Create unique_ptrs
	this->m_attributes = std::make_unique<AttributeComponent>();
	this->m_resources = std::make_unique<ResourceComponent>();

	this->m_inventory = std::make_unique<Inventory>(file.at(name).at("inventory"));

	for (const auto& attribute : file.at(name).at("attributes").items())
	{
		m_attributes.get()->attribute(attribute.key(), attribute.value());
	}

	m_resources.get()->maxLevel("Durability", attribute("Weight") * attribute("Size") * 2);
}

Item::Item(const Item& copy)
{
	this->m_sprite = copy.m_sprite;
	this->m_name = copy.m_name;
	this->m_description = copy.m_description;
}

Item::Item()
{

}

Item::~Item()
{
	std::cout << "Item destroyed." << std::endl;
}

//Accessors
sf::String Item::description()
{
	return m_description;
}

Entity* Item::owner()
{
	return m_owner;
}

//Mutators

void Item::description(sf::String description)
{
	this->m_description = description;
}

void Item::owner(Entity* owner)
{
	m_owner = owner;
}

//Functions
void Item::render(sf::RenderTarget* window)
{
	window->draw(*this->sprite());
}

bool Item::use(Character* owner)
{
	//PENDING
	return true;
}

bool Weapon::use(Character* owner)
{
	if (owner->equippedItem(this->m_slot) == nullptr)
	{
		owner->equippedItem(this->m_slot, this);
		m_engine->gui()->menu("gameInterface")->addMessage(owner->name() + " equips the " + this->name() + ".", m_engine->gui()->font("Arial"), Color::Black, Color::Black);
		return true;
	}
	else
	{
		m_engine->gui()->menu("gameInterface")->addMessage("There's already an item in this slot.", m_engine->gui()->font("Arial"), Color::Black, Color::Black);
		return false;
	}
}