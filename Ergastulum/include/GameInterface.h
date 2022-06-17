#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Menu.h"

class Engine;
class Menu;

class GameInterface : public Menu
{
public:
	//Constructors & Destructors
	GameInterface(sf::RectangleShape panel, sf::RectangleShape messageBox, sf::Color innerColor, sf::Color outlineColor,
		float outlineThickness, unsigned int stateToDraw);
	~GameInterface();

	//Accessors

	//Mutators

	//Functions
	void update();

	//Resources

private:
protected:
};

#endif
