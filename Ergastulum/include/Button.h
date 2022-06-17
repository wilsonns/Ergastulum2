#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "Color.h"

#include <iostream>

class InputHandler;
struct MousePosition;


template<class T>
class Button
{
public:
	typedef void (T::*TCallback)();
	//Constructors & Destructors
	Button(sf::Text text ,sf::Vector2f size, sf::Vector2f pos, 
		sf::Color innerColor, sf::Color outlineColor, float outlineThickness, TCallback function);
	~Button();
	//Accessors
	void callCallback();

	//Mutators
	void setCallback(T* callbackClass, TCallback function);

	//Functions
	void render(sf::RenderTarget* window);
	bool clicked(InputHandler* handler, sf::Mouse::Button mouseButton);

private:
	T* m_callbackClass;
	TCallback m_callback;
	sf::RectangleShape m_shape;
	sf::Color m_idleColor;
	sf::Color m_clickedColor;
	sf::Text m_text;
protected:

};

#endif