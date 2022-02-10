#include "GUI.h"


Barra::Barra(float x, float y, float largura, float altura, float larguraBorda, sf::Color corInterna, sf::Color corBorda)
{
	this->barra.setPosition(x, y);
	this->barra.setSize(sf::Vector2f(largura, altura));
	this->barra.setFillColor(corInterna);
	this->barra.setOutlineThickness(larguraBorda);
	this->barra.setOutlineColor(corBorda);
}


void Barra::largura(float novaLargura)
{
	this->barra.setSize(sf::Vector2f(novaLargura, this->barra.getSize().y));
}

GUI::GUI(float x, float y, float largura, float altura, sf::Color corInterna
	, sf::Color corBorda, sf::RenderTarget* janela,Engine*engine)
{

	//adcionar as fontes à serem usadas pela GUI
	this->adcionarFonte("Arial");
	this->adcionarFonte("CloisterBlack");

	this->m_engine = engine;

	//Seta Posição e Tamanho do retangulo basico da GUI
	this->m_painel.setPosition(sf::Vector2f(x, janela->getSize().y / 1.5f));

	//Seta cores da borda e do interior do retangulo
	this->m_corInterna = corInterna;
	this->m_painel.setFillColor(m_corInterna);
	this->m_corBorda = corBorda;
	this->m_painel.setOutlineColor(m_corBorda);
	this->m_painel.setOutlineThickness(1.f);
	this->m_painel.setSize(sf::Vector2f(janela->getSize().x - (this->m_painel.getOutlineThickness()), (janela->getSize().y / 3.f) - (this->m_painel.getOutlineThickness())));

	this->m_caixaDeMensagens.setPosition(sf::Vector2f((float)(janela->getSize().x / 2)-100, (float)this->m_painel.getPosition().y + 16));
	this->m_caixaDeMensagens.setFillColor(m_corInterna);
	this->m_caixaDeMensagens.setOutlineColor(m_corBorda);
	this->m_caixaDeMensagens.setOutlineThickness(1.f);
	this->m_caixaDeMensagens.setSize(sf::Vector2f(450, 160));

	//Barra
	this->m_barras.push_back(std::make_unique<Barra>((this->m_painel.getGlobalBounds().left + 10), (this->m_painel.getGlobalBounds().top + 24),
		200.f, 24.f, 1.f, sf::Color(200, 20, 20)));
	this->m_barras.push_back(std::make_unique<Barra>((this->m_painel.getGlobalBounds().left + 10), (this->m_painel.getGlobalBounds().top +24),
		200.f, 24.f, 1.f, sf::Color::Red));
	adcionarMensagem("Você acorda com uma dor de cabeça terrível, ao seu redor, apenas pedras frias e mofo... Sua ascenção começa aqui.",*this->m_fontes["Arial"].get(),sf::Color::Black);
	adcionarTexto(60,24,20, "HP:"+std::to_string(80)+"/"+std::to_string(100), * m_fontes["Arial"].get(), sf::Color::Black);

	//

}//CTOR

GUI::~GUI()
{

}//DTOR

bool GUI::adcionarFonte(sf::String arquivo)
{
	sf::Font tmp;
	if (this->m_fontes.find(arquivo) == this->m_fontes.end())
	{
		if (tmp.loadFromFile("Recursos/Fontes/" + arquivo + ".ttf"))
		{
			this->m_fontes.emplace(arquivo, std::make_unique<sf::Font>(tmp));
			std::cout << "Fonte carregada!" << std::endl;
			return true;
		}
	}
	else
	{
		std::cout << "Fonte ja existente!" << std::endl;
		return false;
	}
}

void GUI::adcionarTexto(float x, float y, int tamanho, sf::String texto, sf::Font& fonte, sf::Color cor)
{
	sf::Text tmp(texto, fonte, tamanho);
	tmp.setFillColor(cor);
	tmp.setPosition(this->m_painel.getGlobalBounds().left+x, this->m_painel.getGlobalBounds().top+ y);
	m_texto.push_back(std::make_unique<sf::Text>(tmp));
}//Adciona algum texto a ser mostrado na GUI


void GUI::adcionarMensagem(sf::String texto,sf::Font& fonte, sf::Color cor)
{
	auto mensagem = std::make_unique<Mensagem>(texto, fonte, cor);
	this->m_mensagens.push_back(std::move(mensagem));
}

void GUI::atualizar(sf::RectangleShape& caixa, std::vector<std::unique_ptr<Mensagem>>*mensagens)
{
	float tamanho = caixa.getSize().y / 16;

	if (mensagens->size() > tamanho)
	{
		while (mensagens->size() != tamanho)
		{
			mensagens->erase(mensagens->end()-1);
		}
	}
	int i = 0;
	for (std::vector<std::unique_ptr<Mensagem>>::iterator mensagem = mensagens->begin(); mensagem != mensagens->end();mensagem ++,i++)
	{
		mensagem->get()->texto()->setPosition(caixa.getPosition().x + 2, caixa.getPosition().y + (i * 16));
	}
}

void GUI::render(sf::RenderTarget* janela)
{
	this->atualizar(m_caixaDeMensagens, &m_mensagens);
	janela->draw(this->m_painel);
	for (auto const& barra : m_barras)
	{
		janela->draw(barra.get()->barra);
	}
	for (auto const& texto : m_texto)
	{
		if (texto.get()->getString().getSize() > 0)
		{
			janela->draw(*texto.get());
		}
	}
	janela->draw(this->m_caixaDeMensagens);
	for(auto const& mensagem: m_mensagens)
	{
		mensagem.get()->render(janela);
	}
}//Desenha a GUI na tela;

