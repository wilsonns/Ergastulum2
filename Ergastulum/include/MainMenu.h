#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"

#include <vector>
#include <memory>

#include "Menu.h"

class Button;
class Engine;
class InputHandler;

class MainMenu : public Menu
{
public:
	//Constructors & Destructors
	MainMenu();
	MainMenu(sf::Sprite background);
	~MainMenu();

	//Accessors

	//Mutators

	//Functions

private:
protected:
};




#endif