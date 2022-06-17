#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "Bar.h"
#include "Message.h"
#include "Engine.h"
#include "Button.h"

class Engine;

class MessageBox
{
public:
	//Constructors & Destructors
	MessageBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor);
	MessageBox(sf::RectangleShape rect, sf::Color fillColor, sf::Color outlineColor);
	~MessageBox();
	//Accessors
	
	//Mutators

	//Functions
	void addMessage(sf::String text,sf::Font *font, sf::Color textColor, sf::Color outlineColor);
	void render(sf::RenderTarget* window);
	void update();
	
private:
	std::vector<Message> m_messages;
	sf::RectangleShape m_panel;
};

class Menu
{
public:	
	//Constructors & Destructors
	Menu(sf::RectangleShape panel, sf::RectangleShape messageBox, sf::Color innerColor, sf::Color outlineColor, 
		float outlineThickness, unsigned int stateToDraw);
	Menu();
	//Accessors
	Engine* engine();
	sf::Sprite backgroundImage();

	//Mutators
	static void engine(Engine* engine);
	void backgroundImage(sf::Texture* texture);

	//Functions
	virtual void render(sf::RenderTarget* window);
	virtual void update();
	void addMessage(sf::String text, sf::Font* font, sf::Color textColor, sf::Color outlineColor);
	void updateSize(float x, float y, float width, float height);
	void addText(float x, float y, int size, sf::String label, sf::String text, sf::Font* font, sf::Color color);
	void addButton(sf::Text text,sf::Vector2f pos, sf::Vector2f size, sf::Color innerColor, 
		sf::Color outlineColor, float outlineThickness, void(*ptr)());

protected:
	sf::RectangleShape m_panel; 
	std::vector<sf::Sprite> m_sprites;
	std::vector<Bar> m_bars;
	std::map<sf::String, sf::Text> m_text;
	sf::Color m_innerColor;
	sf::Color m_outlineColor;
	std::unique_ptr<MessageBox> m_messageBox;
	std::vector<std::unique_ptr<Button<Engine>>> m_buttons;
	sf::Sprite m_backgroundImage;

	static Engine* m_engine;
	unsigned int m_stateToDraw;

};

#endif