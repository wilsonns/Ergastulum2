#ifndef MANIPULADOR_H
#define MANIPULADOR_H

#include <iostream>
#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class ManipuladorDeEntrada
{
public:
	struct PosicaoMouse
	{
		PosicaoMouse(int x, int y);
		PosicaoMouse();
		int m_x, m_y;	
	};


	ManipuladorDeEntrada();
	~ManipuladorDeEntrada();

	void atualizar();

	void manipularEvento(const sf::Event& evento);


	void atualizarMouse();
	bool mouseMovido();
	const PosicaoMouse& mouseAtual();
	const PosicaoMouse& mouseAnterior();
	bool botaoMousePressionado(sf::Mouse::Button botao);
	bool botaoMouseSegurado(sf::Mouse::Button botao);
	bool botaoMouseSolto(sf::Mouse::Button botao);

	void atualizarTeclado();
	bool teclaPressionada(sf::Keyboard::Key tecla);
	bool teclaSegurada(sf::Keyboard::Key tecla);
	bool teclaSolta(sf::Keyboard::Key tecla);
	bool rodaMouseGirada();
	float deltaRodaMouse();


	bool eventoTeclado(const sf::Event& evento);
	bool eventoMouse(const sf::Event& evento);


private:
	bool m_mouseMovido;
	bool m_rodaMouseGirada;
	float m_deltaRodaMouse;

	PosicaoMouse m_mouseAtual;
	PosicaoMouse m_mouseAnterior;
	std::unordered_map<unsigned int, bool> m_botaoMousePressionado;
	std::unordered_map<unsigned int, bool> m_botaoMouseSegurado;
	std::unordered_map<unsigned int, bool> m_botaoMouseSolto;
	
	std::unordered_map<unsigned int, bool> m_teclaPressionada;
	std::unordered_map<unsigned int, bool> m_teclaSegurada;
	std::unordered_map<unsigned int, bool> m_teclaSolta;
};








#endif
