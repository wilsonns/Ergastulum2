#include "IA.h"


IAJogador::IAJogador(ManipuladorDeEntrada* manipulador)
{
	this->m_manipulador = manipulador;
}

IAJogador::IAJogador()
{
}

void IAJogador::atualizar(Entidade* owner)
{
	int x, y;
	x = 0;
	y = 0;
	if (m_manipulador->teclaPressionada(sf::Keyboard::Up))
	{
		y--;
	}
	else if (m_manipulador->teclaPressionada(sf::Keyboard::Down))
	{
		y++;
	}
	else if (m_manipulador->teclaPressionada(sf::Keyboard::Left))
	{
		x--;
	}
	else if (m_manipulador->teclaPressionada(sf::Keyboard::Right))
	{
		x++;
	}
	owner->mover(sf::Vector2i(x, y));
}