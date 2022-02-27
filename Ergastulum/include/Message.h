#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include <vector>





class Message
{
public:
	//Constructors & Destructors
	Message(sf::String text, sf::Font* font, sf::Color color);
	~Message();

	//Accessors
	sf::Text* text();

	//Functions
	void render(sf::RenderTarget* window);
	
private:
	sf::Text m_text;
	sf::Color m_color;
};

#endif
