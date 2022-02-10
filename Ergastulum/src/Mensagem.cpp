#include "Mensagem.h"

Mensagem::Mensagem(sf::String texto, sf::Font& fonte, sf::Color cor)
{
	this->m_texto.setFillColor(cor);
	this->m_texto.setFont(fonte);
	this->m_texto.setString(texto);
	this->m_texto.setCharacterSize(12);
}

Mensagem::~Mensagem()
{

}

void Mensagem::render(sf::RenderTarget *janela)
{
	janela->draw(this->m_texto);
}

sf::Text *Mensagem::texto()
{
	return &m_texto;
}