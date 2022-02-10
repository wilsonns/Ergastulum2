#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Engine.h"
#include "Mensagem.h"

class Mensagem;
class Engine;


struct Barra
{
	Barra(float x, float y, float largura, float altura, float larguraBorda,sf::Color corInterna, sf::Color corBorda = sf::Color::Black);
	void largura(float novaLargura);

	sf::RectangleShape barra;
};

class GUI
{
public:
	GUI(float x, float y, float largura, float altura, sf::Color corInterna
		, sf::Color corBorda, sf::RenderTarget* janela, Engine*engine);
	~GUI();

	std::map<sf::String, std::unique_ptr<sf::Font>> m_fontes;

	bool adcionarFonte(sf::String arquivo);
	void adcionarTexto(float x, float y,int tamanho, sf::String texto, sf::Font& fonte, sf::Color cor);

	void adcionarMensagem(sf::String texto, sf::Font& fonte, sf::Color cor);

	void atualizar(sf::RectangleShape& caixa, std::vector<std::unique_ptr<Mensagem>>*mensagens);
	void render(sf::RenderTarget* janela);

	
private:
	std::vector<std::unique_ptr<Barra>> m_barras;
	sf::RectangleShape m_painel;
	std::vector<std::unique_ptr<sf::Text>> m_texto;
	
	sf::RectangleShape m_caixaDeMensagens;
	std::vector<std::unique_ptr<Mensagem>> m_mensagens;

	sf::Color m_corInterna;
	sf::Color m_corBorda;
	Engine* m_engine;


};

#endif