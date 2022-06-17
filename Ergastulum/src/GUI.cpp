#include "GUI.h"

#include "Engine.h"
#include "Message.h"
#include "Bar.h"
#include "Item.h"
#include "Menu.h"
#include "InventoryMenu.h"
#include "MainMenu.h"
#include "Color.h"
#include "GameInterface.h"

//Constructors & Destructors
GUI::GUI(float x, float y, float width, float height, sf::Color innerColor
	, sf::Color outlineColor, sf::RenderTarget* window,Engine*engine)
{
	this->addFont("Arial");
	this->addFont("CloisterBlack");

	this->m_engine = engine;
	Menu::engine(engine);

	sf::RectangleShape gameInterface;
	gameInterface.setPosition(0, window->getSize().y - (window->getSize().y / 3));
	gameInterface.setSize(sf::Vector2f((float)(window->getSize().x), (float)(window->getSize().y / 3)));
	sf::RectangleShape messageBox;
	messageBox.setPosition(gameInterface.getPosition().x + gameInterface.getSize().x / 2.1f, gameInterface.getPosition().y + 10.f);
	messageBox.setSize(sf::Vector2f((float)(gameInterface.getSize().x / 2), gameInterface.getSize().y * 0.8f));
	
	sf::RectangleShape inventory;
	inventory.setPosition(100.f, 100.f);
	inventory.setSize(sf::Vector2f(200.f, 200.f));

	m_menus.insert(std::make_pair("gameInterface", std::make_unique<GameInterface>(gameInterface,messageBox,innerColor, outlineColor, 1.f,m_engine->ANY)));

	m_menus.insert(std::make_pair("inventory", std::make_unique<InventoryMenu>(inventory, innerColor, outlineColor, 1.f, m_engine->INVENTORY_MENU)));
	m_menus.insert(std::make_pair("mainMenu", std::make_unique<MainMenu>(sf::Sprite(m_engine->m_startScreen))));

	m_menus.at("mainMenu").get()->addButton(sf::Text(), sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f), Color::Blue, Color::White, 1.f,nullptr);
}

GUI::~GUI()
{

}//DTOR


//Accessors
/**Return a sf::Font by its name. If no font is found, returns Arial*/
sf::Font *GUI::font(sf::String font)
{
	if (this->m_fonts.find(font) != this->m_fonts.end())
	{
		return m_fonts[font].get();
	}
	return m_fonts["Arial"].get();
}

/**Gets a menu*/
Menu* GUI::menu(sf::String label)
{
	if (this->m_menus.find(label) != this->m_menus.end())
	{
		return m_menus[label].get();
	}
	return nullptr;
}

//Functions

/**Adds a new sf:Font from a file to be used in the GUI.*/
bool GUI::addFont(sf::String file)
{
	sf::Font tmp;
	if (this->m_fonts.find(file) == this->m_fonts.end())
	{
		if (tmp.loadFromFile("Assets/Fonts/" + file + ".ttf"))
		{
			this->m_fonts.emplace(file, std::make_unique<sf::Font>(tmp));
			std::cout << "Font loaded!" << std::endl;
			return true;
		}
	}
	else
	{
		std::cout << "Font already exists" << std::endl;
		return false;
	}
}









/**Updates the whole GUI.*/
void GUI::update()
{	
	for (const auto& menu : m_menus)
	{
		menu.second.get()->update();
	}
}

/**Renders the GUI to the window.*/
void GUI::render(sf::RenderTarget* window)
{
	this->update();
	for (const auto& menu : m_menus)
	{
		menu.second.get()->render(window);
	}

}
