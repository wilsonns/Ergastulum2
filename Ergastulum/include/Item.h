#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item
{
public:
	//Constructors & Destructors
	Item(sf::String name, sf::Vector2i pos, 
		sf::Sprite sprite, int size, int weight ,Entity* owner = nullptr);
	~Item();

	//Accessors
	int size();
	int weight();

	//Mutators
	void size(int size);
	void weight(int weight);

	//Functions
	virtual bool use(Entity *owner);
	
private:
	int m_size;
	int m_weight;


	sf::String m_name;
	sf::String description;
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;

	static int m_spriteSize;
	static Engine* m_engine;

};


#endif