#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>

namespace Color
{
	static const sf::Color Red(255,0,0);
	static const sf::Color Green(0, 255, 0);
	static const sf::Color Blue(0,0,255);
		
	static const sf::Color DarkRed(102, 0, 0);
	static const sf::Color DarkGreen(0,102, 0);
	static const sf::Color DarkBlue(0, 0, 102);

	static const sf::Color Black(0, 0, 0);
	static const sf::Color White(255, 255, 255);
	static const sf::Color Gray(160, 160, 160);
	static const sf::Color DarkGray(64, 64, 64);

	static const sf::Color Sepia(112, 66, 20);
}


#endif