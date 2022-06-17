#include "Menu.h"

#include "Color.h"
#include "Character.h"
#include "Button.h"
#include "InputHandler.h"

Engine* Menu::m_engine;

//Constructors & Destructors
MessageBox::MessageBox(sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor)
{
	m_panel.setPosition(pos);
	m_panel.setSize(size);
	m_panel.setFillColor(fillColor);
	if (fillColor != outlineColor)
	{
		m_panel.setOutlineThickness(1.f);
		m_panel.setOutlineColor(outlineColor);
	}
}

MessageBox::MessageBox(sf::RectangleShape rect, sf::Color fillColor, sf::Color outlineColor)
{
	m_panel = rect;
	m_panel.setFillColor(fillColor);
	if (fillColor != outlineColor)
	{
		m_panel.setOutlineColor(outlineColor);
	}
}

MessageBox::~MessageBox()
{

}
//Accessors
//Mutators

//Functions
void MessageBox::addMessage(sf::String text, sf::Font *font, sf::Color textColor, sf::Color outlineColor)
{
	Message msg(text, font, textColor, outlineColor);
	m_messages.push_back(msg);
}


void MessageBox::render(sf::RenderTarget* window)
{
	window->draw(m_panel);
	if (m_messages.size() > 0)
	{
		update();
		for (auto& message : m_messages)
		{
			message.render(window);
		}
	}
}

void MessageBox::update()
{
	if (m_messages.size() > 0)
	{
		int size = m_panel.getSize().y / 13;
		if (m_messages.size() > size)
		{
			while (m_messages.size() != size)
			{
				m_messages.erase(m_messages.begin());
			}
		}

		int i = 0;
		for (std::vector<Message>::iterator it = m_messages.begin(); it != m_messages.end(); it++, i++)
		{
			(*it).text()->setPosition(m_panel.getPosition().x + 2, m_panel.getPosition().y + i * 13);
		}
		return;
	}
}




//Constructors & Destructors
Menu::Menu(sf::RectangleShape panel, sf::RectangleShape messageBox, sf::Color innerColor, sf::Color outlineColor,
	float outlineThickness, unsigned int stateToDraw)
{
	m_panel = panel;
	m_panel.setOutlineColor(outlineColor);
	m_panel.setOutlineThickness(outlineThickness);
	m_panel.setFillColor(innerColor);
	m_stateToDraw = stateToDraw;		
	if (messageBox.getSize().x)
	{
		m_messageBox = std::make_unique<MessageBox>(messageBox,innerColor,outlineColor);
	}
}

Menu::Menu()
{

}

//Accessors
Engine* Menu::engine()
{
	return m_engine;
}

sf::Sprite Menu::backgroundImage()
{
	return m_backgroundImage;
}

//Mutators
void Menu::engine(Engine* engine)
{
	m_engine = engine;
}

void Menu::backgroundImage(sf::Texture* texture)
{
	m_backgroundImage.setTexture(*texture);
}

//Functions
void Menu::render(sf::RenderTarget* window)
{
	if (m_engine->gameState(m_engine->CURRENT) == m_stateToDraw || m_stateToDraw == m_engine->ANY)
	{
		if (m_panel.getSize().x > 0.f)
		{
			window->draw(this->m_panel);
		}
		
		if (m_backgroundImage.getTexture() != nullptr)
		{
			window->draw(m_backgroundImage);
		}

		if (m_bars.size() > 0)
		{
			for (auto const& bar : m_bars)
			{
				window->draw(bar.bar);
			}
		}
		if (m_text.size() > 0)
		{
			for (auto const& text : m_text)
			{
				if (text.second.getString().getSize() > 0)
				{
					window->draw(text.second);
				}
			}
		}
		if (m_messageBox)
		{
			m_messageBox.get()->render(window);

		}
		if (m_buttons.size() > 0)
		{
			for (auto const& button : m_buttons)
			{
				button.get()->render(window);
			}
		}
	}
}

void Menu::addMessage(sf::String text, sf::Font* font, sf::Color textColor, sf::Color outlineColor)
{
	m_messageBox.get()->addMessage(text, font, textColor, outlineColor);
}

void Menu::addButton(sf::Text text, sf::Vector2f pos, sf::Vector2f size, sf::Color innerColor, 
	sf::Color outlineColor, float outlineThickness)
{
	m_buttons.push_back(std::make_unique<Button<Engine>>(text, size, pos, innerColor, outlineColor, outlineThickness));
}

void Menu::update()
{
	if (m_engine->gameState(m_engine->CURRENT) == m_stateToDraw || m_stateToDraw == m_engine->ANY)
	{
		if (m_messageBox)
		{
			m_messageBox.get()->update();
		}
		
		for (auto& button : m_buttons)
		{
			if (button.get()->clicked(engine()->handler(),sf::Mouse::Button::Left))
			{
				std::cout << "Clickou!!!!" << std::endl;
				//button.get()->callCallback();
			}
		}
	}
}

void Menu::updateSize(float x, float y, float width, float height)
{
	m_panel.setSize(sf::Vector2f(width, height));
	m_panel.setPosition(sf::Vector2f(x, y));
}

void Menu::addText(float x, float y, int size, sf::String label, sf::String text, sf::Font* font, sf::Color color)
{
	sf::Text tmp(text, *font, size);
	tmp.setFillColor(color);
	tmp.setPosition(x, y);
	m_text[label] = tmp;
}
