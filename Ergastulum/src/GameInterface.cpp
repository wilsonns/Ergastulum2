#include "GameInterface.h"

#include "Engine.h"
#include "Character.h"
#include "InputHandler.h"

GameInterface::GameInterface(sf::RectangleShape panel, sf::RectangleShape messageBox, sf::Color innerColor, sf::Color outlineColor,
	float outlineThickness, unsigned int stateToDraw)
{
	m_panel = panel;
	m_panel.setOutlineColor(outlineColor);
	m_panel.setOutlineThickness(outlineThickness);
	m_panel.setFillColor(innerColor);
	m_stateToDraw = stateToDraw;
	//HP back
	m_bars.push_back(Bar(10.f, m_panel.getPosition().y + 10.f, 200.f, 25.f, 1.f, Color::DarkRed, Color::Black));
	//HP front
	m_bars.push_back(Bar(10.f, m_panel.getPosition().y + 10.f, 200.f, 25.f, 1.f, Color::Red, Color::Black));

	if (messageBox.getSize().x)
	{
		m_messageBox = std::make_unique<MessageBox>(messageBox, innerColor, outlineColor);
	}
}


GameInterface::~GameInterface()
{
}

void GameInterface::update()
{
	Menu::update();
	float newHpWidth = (float)m_engine->player()->currentResource("Health") / (float)m_engine->player()->maxResource("Health");
	m_bars[1].width(m_bars[0].bar.getSize().x * newHpWidth);

}