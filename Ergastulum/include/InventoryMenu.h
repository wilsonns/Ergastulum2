#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <vector>

#include "Menu.h"

class Item;

class InventoryMenu : public Menu
{
public:
	friend class Item;
	//Constructors & Destructors
	InventoryMenu(sf::RectangleShape panel, sf::Color innerColor, sf::Color outlineColor,
		float outlineThickness, unsigned int stateToDraw);
	//Accessors

	//Mutators

	//Functions
	void render(sf::RenderTarget* window);
	void update();
protected:
	std::vector<Item> m_itemsToDraw;
};



#endif