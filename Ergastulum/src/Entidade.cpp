#include "Entidade.h"


Entidade::Entidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite)
{
	this->m_nome = nome;
	this->m_pos = pos;
	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)m_pos.x * 64, (float)m_pos.y * 64);
	this->m_IA = std::make_unique<IAJogador>();

	m_atributos.get()->atributo("Força", 10);
	m_atributos.get()->atributo("Destreza", 10);
	m_atributos.get()->atributo("Intelecto", 10);
	m_atributos.get()->atributo("Vitalidade", 10);
	m_atributos.get()->atributo("Saúde", m_atributos.get()->atributo("Força").m_nivelAjustado *3 + m_atributos.get()->atributo("Vitalidade").m_nivelAjustado *2);
	m_atributos.get()->atributo("Energia", m_atributos.get()->atributo("Intelecto").m_nivelAjustado *10);
	m_atributos.get()->atributo("Ataque", (int)m_atributos.get()->atributo("Destreza").m_nivelAjustado / 2);
	m_atributos.get()->atributo("Defesa", (int)m_atributos.get()->atributo("Destreza").m_nivelAjustado/2);
	m_atributos.get()->atributo("RD", 0);
	m_atributos.get()->atributo("Velocidade", 100 + m_atributos.get()->atributo("Destreza").m_nivelAjustado);

	std::cout << "Entidade criada!" << std::endl;
}

Entidade::Entidade(sf::String nome, sf::Vector2i pos, sf::Sprite sprite, ManipuladorDeEntrada* manipulador)
{
	this->m_nome = nome;
	this->m_pos = pos;
	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)m_pos.x * 64, (float)m_pos.y * 64);
	this->m_IA = std::make_unique<IAJogador>(manipulador);
	std::cout << "Entidade criada!" << std::endl;
}

Entidade::~Entidade()
{

}


Entidade::Entidade(const Entidade &copia)
{
	this->m_nome = copia.m_nome;
	this->m_pos = copia.m_pos;
	this->m_sprite = copia.m_sprite;
	this->m_sprite.setPosition((float)m_pos.x * 64, (float)m_pos.y * 64);
	*this->m_atributos.get() = *copia.m_atributos.get();
}

sf::String Entidade::nome()
{
	return m_nome;
}

sf::Sprite Entidade::sprite() 
{
	return m_sprite;
}//retorna o Sprite da entidade


sf::Vector2i Entidade::pos()
{
	return m_pos;
}//retorna a posição no grid

ComponenteAtributos* Entidade::atributos()
{
	return m_atributos.get();
}

void Entidade::nome(sf::String nome)
{
	this->m_nome = nome;
}

void Entidade::sprite(sf::Sprite sprite) 
{
	m_sprite = sprite;
}//muda o sprite da entidade

void Entidade::pos(sf::Vector2i pos)
{
	m_pos = pos;
	m_sprite.setPosition((float)m_pos.x * 64, (float)m_pos.y * 64);
}//seta uma posição absoluta no grid

void Entidade::mover(sf::Vector2i offset)
{
	m_pos.x += offset.x;
	m_pos.y += offset.y;
	m_sprite.setPosition((float)m_pos.x * 64, (float)m_pos.y * 64);
}//Soma o offset à posição atual



void Entidade::atualizar()
{
	if (this->m_IA)
	{
		this->m_IA->atualizar(this);
	}
}


void Entidade::atacar(Entidade* alvo)
{
	int acerto = (50+ (this->atributos()->atributo("Ataque").m_nivelAtual));
	if (acerto > 90)
	{
		acerto = 90;
	}
	acerto -= alvo->atributos()->atributo("Defesa").m_nivelAtual;
	if (acerto < 20)
	{
		acerto = 20;
	}

	if (rand()%100 < acerto)
	{
		int dano = rand() % 10;
	}
}