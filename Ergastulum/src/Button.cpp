#include "Button.h"

#include "InputHandler.h"

template<class T>
//Constructors & Destructors
Button<T>::Button(sf::Text text, sf::Vector2f size, sf::Vector2f pos, sf::Color innerColor,
	sf::Color outlineColor, float outlineThickness, TCallback function)
{
	this->m_shape.setPosition(pos);
	this->m_shape.setSize(size);
	this->m_shape.setFillColor(innerColor);
	this->m_idleColor = innerColor;
	this->m_clickedColor = sf::Color(innerColor.r*0.5f, innerColor.g * 0.5f, innerColor.b * 0.5f); //Makes the clicked Color a darker hue than the idleColor
	if (outlineThickness > 0.f)
	{
		this->m_shape.setOutlineColor(outlineColor);
		this->m_shape.setOutlineThickness(outlineThickness);
	}
	this->m_text = text;
}


template<class T>
Button<T>::~Button()
{

}

//Accessors

template<class T>
void Button<T>::callCallback()
{
	(m_callbackClass->*m_callback)();
}

//Mutators
template<class T>
void Button<T>::setCallback(T* callbackClass, TCallback function)
{
	m_callbackClass = callbackClass;
	m_callback = &function;
}

//Functions

template<class T>
void Button<T>::render(sf::RenderTarget* window)
{
	window->draw(m_shape);
}

template<class T>
bool Button<T>::clicked(InputHandler *handler, sf::Mouse::Button mouseButton)
{
	sf::Vector2f size = m_shape.getSize();
	sf::Vector2f position = m_shape.getPosition()+size;
	sf::Vector2f pos = sf::Vector2f(handler->getMouseCurrentPosition().x, handler->getMouseCurrentPosition().y);

	if ((pos.x >= size.x && pos.x <= position.x) && (pos.y >= size.y && pos.y <= position.y) && handler->isMouseButtonDown(mouseButton))
	{
		m_shape.setFillColor(m_clickedColor);
		return true;
	}
	m_shape.setFillColor(m_idleColor);
	return false;
}
