#include "AI.h"

Engine* AI::m_engine;

PlayerAI::PlayerAI()
{
}


PlayerAI::PlayerAI(PlayerAI& copy)
{
}

void PlayerAI::update(Entity* owner)
{
	int x, y;
	x = 0;
	y = 0;
	if (m_engine->handler()->isKeyPressed(sf::Keyboard::Up))
	{
		y--;
	}
	if (m_engine->handler()->isKeyPressed(sf::Keyboard::Down))
	{
		y++;
	}
	if (m_engine->handler()->isKeyPressed(sf::Keyboard::Left))
	{
		x--;
	}
	if (m_engine->handler()->isKeyPressed(sf::Keyboard::Right))
	{
		x++;
	}
	if (x != 0 || y != 0)
	{
		Tile* tile = m_engine->currentMap()->tile(sf::Vector2i(owner->pos().x + x, owner->pos().y + y));
		if (m_engine->currentMap()->isWalkable(tile))
		{
			owner->move(sf::Vector2i(x, y));
		}
		else if (tile->occupant() != nullptr)
		{
			if (!tile->occupant()->died())
			{
				owner->attack(tile->occupant());
			}
		}
		m_engine->gameState(m_engine->ENEMY_TURN);
	}
}


void PlayerAI::engine(Engine* engine)
{
	m_engine = engine;
}



DummyAI::DummyAI()
{

}


DummyAI::DummyAI(DummyAI& copy)
{

}

void DummyAI::update(Entity* owner)
{
	
	path = Pathfinding::findPath(owner->pos(), m_engine->player()->pos());
	int dx = 0;
	int dy = 0;
	if (path.size() > 0)
	{
		dx = path[0]->m_pos.x - owner->pos().x;
		dy = path[0]->m_pos.y - owner->pos().y;
		if (m_engine->currentMap()->tile(path[0]->m_pos)->occupant() == m_engine->player())
		{
			owner->attack(m_engine->player());
		}
		else
		{
			owner->move(sf::Vector2i(dx, dy));
		}
	}
	else
	{
		return;
	}
}
	


void DummyAI::engine(Engine* engine)
{
	std::cout << "Fodasse?" << std::endl;
}