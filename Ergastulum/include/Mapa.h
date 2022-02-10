#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Entidade.h"
#include "Engine.h"
#include "ManipuladorDeEntrada.h"


class Entidade;
class Engine;
class ManipuladorDeEntrada;

class Tile
{
public:
	enum Terreno {
		CHAO = 0,
		PAREDE = 1
	};
	Tile(sf::Vector2i pos, sf::Sprite sprite, bool passavel = true);
	~Tile();

	//Acessores
	sf::Sprite sprite();//retorna o sprite
	sf::Vector2i pos();//retorna a posição no grid
	bool passavel();//retorna se o tile é denso ou não
	Entidade* ocupante();//retorna o ocupante
	
	//Setters
	void sprite(sf::Sprite sprite);//Muda o sprite
	void pos(sf::Vector2i pos);//seta uma posição absoluta no grid
	void passavel(bool passavel);//muda se o tile é denso ou não
	void ocupante(Entidade* ocupante);//muda o ocupante

private:
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;
	bool m_passavel;
	Entidade* m_ocupante;
};


class Mapa
{
public:
	Mapa(int altura, int largura, Engine &engine);
	~Mapa();

	//GETTERS
	Tile *tile(sf::Vector2i pos);//retorna a tile na posição do vetor

	//SETTER
	void render(sf::RenderWindow* janela);
	void atualizar();

	void adcionarEntidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite);
	void adcionarEntidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite, ManipuladorDeEntrada* manipulador);

private:
	int m_largura, m_altura;
	std::vector<std::unique_ptr<Tile>> m_tiles;
	std::vector<std::unique_ptr<Entidade>> m_entidades;
};

//

#endif