#ifndef MENSAGEM_H
#define MENSGEM_H

#include <SFML/Graphics.hpp>
#include <vector>





class Mensagem
{
public:
	Mensagem(sf::String texto, sf::Font& fonte, sf::Color cor);
	~Mensagem();

	void render(sf::RenderTarget* janela);
	sf::Text *texto();
private:
	sf::Text m_texto;
	sf::Color m_cor;
};

#endif
