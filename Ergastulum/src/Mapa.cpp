#include "Mapa.h"


// TTTTTTT    III    LL       EEEEEEE     SSSSSS
//   TTT      III    LL       EE          SS  
//   TTT      III    LL       EEEEEE      SSSSSS
//   TTT      III    LL       EE              SS
//   TTT      III    LLLLL    EEEEEEE     SSSSSS
Tile::Tile(sf::Vector2i pos, sf::Sprite sprite, bool passavel)
{
	this->m_pos = pos;
	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)pos.x *64, (float)pos.y * 64);
	this->m_passavel = passavel;
}

Tile::~Tile()
{

}

//GETTERS//

sf::Sprite Tile::sprite()
{
	return m_sprite;
}//retorna o sprite

sf::Vector2i Tile::pos()
{
	return m_pos;
}//retorna a posição no grid

bool Tile::passavel()
{
	return m_passavel;
}//retorna se o tile é denso ou não


Entidade* Tile::ocupante()
{
	return m_ocupante;
}//retorna o ocupante

//SETTERS//

void Tile::sprite(sf::Sprite sprite)
{
	m_sprite = sprite;
}//Muda o sprite

void Tile::pos(sf::Vector2i pos) 
{
	m_pos = pos;
}//seta uma posição absoluta no grid


void Tile::passavel(bool passavel)
{
	m_passavel = passavel;
}//muda se o tile é denso ou não


void Tile::ocupante(Entidade* ocupante)
{
	m_ocupante = ocupante;
}//muda o ocupante

//  MM   MM        A         PPPPPP          A
//  MMM MMM       A A        PP   PP        A A
//  MM M MM      AAAAA       PPPPPP        AAAAA 
//  MM   MM     AA   AA      PP           AA   AA 
//  MM   MM    AA     AA     PP          AA     AA

Mapa::Mapa(int largura, int altura, Engine& engine)
{
	this->m_altura = altura;
	this->m_largura = largura;
	for (int x = 0; x < largura; x++)
	{
		for (int y = 0; y < altura;y++)
		{
			bool passavel = true;
			int sp = 0;
			if (x < 1 || x == largura || y < 1 || y == altura)
			{
				passavel = false;
				sp = 1;
			}
			m_tiles.push_back(std::make_unique<Tile>(sf::Vector2i(x, y),engine.sprite(sp),passavel));
		}
	}
}

Mapa::~Mapa()
{

}

Tile *Mapa::tile(sf::Vector2i pos)
{
	return m_tiles[pos.x + pos.y * m_largura].get();
}


void Mapa::render(sf::RenderWindow* janela)
{
	for (auto& tile : m_tiles)
	{
		janela->draw(tile->sprite());
	}

	for (auto& entidade : m_entidades)
	{
		janela->draw(entidade->sprite());
	}
}

void Mapa::atualizar()
{
	for (std::vector<std::unique_ptr<Entidade>>::iterator it = m_entidades.begin(); it != m_entidades.end(); it++)
	{
		it->get()->atualizar();
	}
}


void Mapa::adcionarEntidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite)
{
	std::unique_ptr<Entidade> entidade;
	entidade = std::make_unique<Entidade>(nome, pos, sprite);
	tile(pos)->ocupante(entidade.get());
	m_entidades.push_back(std::move(entidade));
}

void Mapa::adcionarEntidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite, ManipuladorDeEntrada* manipulador)
{
	std::unique_ptr<Entidade> entidade;
	entidade = std::make_unique<Entidade>(nome, pos, sprite,manipulador);
	tile(pos)->ocupante(entidade.get());
	m_entidades.push_back(std::move(entidade));
}