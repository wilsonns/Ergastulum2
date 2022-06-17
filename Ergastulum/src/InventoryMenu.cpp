#include "InventoryMenu.h"

#include "GUI.h"
#include "Character.h"
#include "Item.h"
#include "Inventory.h"


InventoryMenu::InventoryMenu(sf::RectangleShape panel, 
	sf::Color innerColor, sf::Color outlineColor,
	float outlineThickness, unsigned int stateToDraw)
{
	m_panel = panel;
	m_panel.setOutlineColor(outlineColor);
	m_panel.setOutlineThickness(outlineThickness);
	m_panel.setFillColor(innerColor);
	m_stateToDraw = stateToDraw;
}


void InventoryMenu::render(sf::RenderTarget* window)
{
	if (m_engine->gameState(m_engine->CURRENT) == m_stateToDraw || m_stateToDraw == m_engine->ANY)
	{
		window->draw(m_panel);
		int shortcut = 'a';
		for (Item& item : m_itemsToDraw)
		{
			item.render(window);
			sf::Text tmp(item.name(), *m_engine->gui()->font("Arial"), 16);
			tmp.setFillColor(sf::Color::Black);
			tmp.setPosition(sf::Vector2f(item.sprite()->getPosition().x + item.spriteSize()+6, item.sprite()->getPosition().y));
			sf::Text shtct((char)shortcut, *m_engine->gui()->font("Arial"), 16);
			shtct.setFillColor(sf::Color::Black);
			shtct.setPosition(sf::Vector2f(item.sprite()->getPosition().x + item.spriteSize() -18, item.sprite()->getPosition().y));
			window->draw(shtct);
			window->draw(tmp);
		}
	}
}

void InventoryMenu::update()
{
	if (m_engine->gameState(m_engine->CURRENT) == m_stateToDraw || m_stateToDraw == m_engine->ANY)
	{
		m_itemsToDraw.clear();
		//updates the inventory contents
		std::vector<Item*> items = *m_engine->player()->inventory()->contents();
		int h = 0;
		for (auto& item : items)
		{
			item->sprite()->setPosition((float)m_panel.getPosition().x + 9, (float)m_panel.getPosition().y + item->spriteSize() * h);
			m_itemsToDraw.push_back((*item));
			h++;
		}

		int width = 0;
		for (auto& item : m_itemsToDraw)
		{
			if (item.name().getSize() > width)
			{
				width = item.name().getSize();
			}
		}
		width *= 30;
		updateSize(100.f, 100.f, (float)width, (float)Item::spriteSize() * m_itemsToDraw.size());
	}
}