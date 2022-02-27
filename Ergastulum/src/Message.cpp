#include "Message.h"

//Constructors & Destructors
Message::Message(sf::String text, sf::Font* font, sf::Color color)
{
	this->m_text.setFillColor(color);
	this->m_text.setFont(*font);
	this->m_text.setString(text);
	this->m_text.setCharacterSize(12);
}

Message::~Message()
{

}

//Accessors
sf::Text* Message::text()
{
	return &m_text;
}


//Functions
void Message::render(sf::RenderTarget *window)
{
	window->draw(this->m_text);
}
