#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <SFML/Graphics.hpp>


#include "Engine.h"
#include "Mapa.h"
#include "ComponenteAtributos.h"
#include "Destrutivel.h"
#include "IA.h"

class ComponenteAtributos;
class IA;
class IAJogador;
class Engine;

class Entidade
{
public:
	Entidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite);
	~Entidade();
	Entidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite, ManipuladorDeEntrada* manipulador);
	Entidade(const Entidade& copia);

	//Acessoress
	sf::String nome();
	sf::Sprite sprite(); //retorna o Sprite da entidade
	sf::Vector2i pos(); //retorna a posição no grid
	ComponenteAtributos* atributos();

	//Setters
	void nome(sf::String nome);//muda o nome
	void sprite(sf::Sprite sprite);//muda o sprite da entidade
	void pos(sf::Vector2i pos);//seta uma posição absoluta no grid
	void mover(sf::Vector2i offset);//Soma o offset à posição atual

	//Utilidades
	void atualizar();

	//Combate
	void atacar(Entidade* alvo);

private:
	sf::String m_nome;
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;
	std::unique_ptr<ComponenteAtributos> m_atributos;
	std::unique_ptr<IA> m_IA;
};


#endif
