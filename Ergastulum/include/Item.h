#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Engine;
class Entity;
class Character;
class AttributeComponent;
class ResourceComponent;

class Item : public Entity
{
public:
	//Constructors & Destructors
	Item(sf::String name, sf::Vector2i pos, 
		sf::Sprite sprite, AttributeComponent attributes, Entity* owner = nullptr);
	Item(const json& file, sf::String name, sf::Vector2i pos);
	Item(const Item& copy);
	Item();
	~Item();

	//Accessors
	sf::String description();
	Entity* owner();

	//Mutators
	void description(sf::String description);
	void owner(Entity* owner);

	//Functions
	virtual void render(sf::RenderTarget* window);
	virtual bool use(Character *owner);
	
private:

	Entity* m_owner;
	sf::String m_description;
protected:
	unsigned int m_slot;
};


class Weapon : public Item
{
public:
	using Item::Item;
	bool use(Character* owner);
private:
};

#endif