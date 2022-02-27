#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "Engine.h"
#include "Message.h"
#include "Bar.h"

class Message;
class Engine;
struct Bar;

class GUI
{
public:
	//Constructors & Destructors
	GUI(float x, float y, float width, float height, sf::Color innerColor
		, sf::Color outlineColor, sf::RenderTarget* window, Engine*engine);
	~GUI();

	//Accessors
	sf::Font *font(sf::String font);

	//Functions
	void update(sf::RectangleShape& box, std::vector<std::unique_ptr<Message>>*messages);
	void render(sf::RenderTarget* window);
	bool addFont(sf::String file);
	void addText(float x, float y, int size, sf::String label, sf::String text, sf::Font *fonte, sf::Color cor);
	void addMessage(sf::String text, sf::Font* font, sf::Color color);

	
private:
	//Assets
	sf::RectangleShape m_panel;
	
	std::map<sf::String, std::unique_ptr<sf::Font>> m_fonts;
	std::map<sf::String,std::unique_ptr<Bar>> m_bars;
	std::map<sf::String, std::unique_ptr<sf::Text>> m_text;
		
	sf::RectangleShape m_messageBox;
	std::vector<std::unique_ptr<Message>> m_messages;

	sf::Color m_innerColor;
	sf::Color m_outlineColor;
	Engine* m_engine;


};

#endif