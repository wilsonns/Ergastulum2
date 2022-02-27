#include "Bar.h"

//Constructors & Destructors
Bar::Bar(float x, float y, float width, float height, float outlineThickness,
	sf::Color innerColor, sf::Color outlineColor)
{
	this->bar.setPosition(x, y);
	this->bar.setSize(sf::Vector2f(width, height));
	this->bar.setFillColor(innerColor);
	this->bar.setOutlineThickness(outlineThickness);
	this->bar.setOutlineColor(outlineColor);
}


void Bar::width(float newWidth)
{
	this->bar.setSize(sf::Vector2f(newWidth, this->bar.getSize().y));
}