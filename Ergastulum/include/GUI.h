#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>


class Message;
class Engine;
class Item;
struct Bar;
class Menu;
class InventoryMenu;

class GUI
{
public:
	//Constructors & Destructors
	GUI(float x, float y, float width, float height, sf::Color innerColor
		, sf::Color outlineColor, sf::RenderTarget* window, Engine*engine);
	~GUI();

	//Accessors
	sf::Font *font(sf::String font);
	Menu* menu(sf::String label);

	//Functions
	//General Functions
	bool addFont(sf::String file);

	//Update Functions
	void update();

	//Render Functions
	void render(sf::RenderTarget* window);
	
	
private:
	//Assets
	// General Assets
	std::map<sf::String, std::unique_ptr<sf::Font>> m_fonts;
	
	//MENUS
	std::map<sf::String,std::unique_ptr<Menu>> m_menus;
	
	Engine* m_engine;
};

#endif