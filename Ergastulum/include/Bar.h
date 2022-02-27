#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

struct Bar
{
	//Constructors & Destructors
	Bar(float x, float y, float width, float height, float outlineThickness,
		sf::Color innerColor, sf::Color outlineColor = sf::Color::Black);

	//Mutators
	void width(float newWidth);

	//Assets
	sf::RectangleShape bar;
};
#endif