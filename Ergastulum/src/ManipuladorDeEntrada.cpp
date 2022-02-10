#include "ManipuladorDeEntrada.h"

ManipuladorDeEntrada::PosicaoMouse::PosicaoMouse(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}

ManipuladorDeEntrada::PosicaoMouse::PosicaoMouse()
{
}



ManipuladorDeEntrada::ManipuladorDeEntrada()
{
	auto mouse = sf::Mouse::getPosition();
	m_mouseAtual.m_x = mouse.x;
	m_mouseAtual.m_y = mouse.y;
	m_mouseAnterior = m_mouseAtual;

}

ManipuladorDeEntrada::~ManipuladorDeEntrada()
{

}

void ManipuladorDeEntrada::atualizar()
{
	atualizarTeclado();
	atualizarMouse();
}


void ManipuladorDeEntrada::manipularEvento(const sf::Event& evento)
{
	if (eventoTeclado(evento))
	{
		return;
	}
	if (eventoMouse(evento))
	{
		return;
	}
}

void ManipuladorDeEntrada::atualizarMouse()
{
	m_mouseMovido = true;
	for (auto& it : m_botaoMousePressionado)
	{
		if (it.second)
		{
			m_botaoMouseSegurado[it.first] = true;
			it.second = false;
		}
	}

	for (auto& it : m_botaoMouseSolto)
	{
		if (it.second)
		{
			it.second = false;
		}
	}
	if (m_rodaMouseGirada)
	{
		m_rodaMouseGirada = false;
		m_deltaRodaMouse = 0.0f;
	}

}

bool ManipuladorDeEntrada::mouseMovido()
{
	return m_mouseMovido;
}

const ManipuladorDeEntrada::PosicaoMouse& ManipuladorDeEntrada::mouseAtual()
{
	return m_mouseAtual;
}

const ManipuladorDeEntrada::PosicaoMouse& ManipuladorDeEntrada::mouseAnterior()
{
	return m_mouseAnterior;
}


bool ManipuladorDeEntrada::botaoMousePressionado(sf::Mouse::Button botao)
{
	return m_botaoMousePressionado[botao];
}


bool ManipuladorDeEntrada::botaoMouseSegurado(sf::Mouse::Button botao)
{
	return m_botaoMouseSegurado[botao];
}

bool ManipuladorDeEntrada::botaoMouseSolto(sf::Mouse::Button botao)
{
	return m_botaoMouseSolto[botao];
}

bool ManipuladorDeEntrada::rodaMouseGirada()
{
	return m_rodaMouseGirada;
}


float ManipuladorDeEntrada::deltaRodaMouse()
{
	return m_deltaRodaMouse;
}

void ManipuladorDeEntrada::atualizarTeclado()
{
	for (auto& it : m_teclaPressionada)
	{
		if (it.second)
		{
			m_teclaSegurada[it.first] = true;
			it.second = false;
		}
	}
	for (auto& it : m_teclaSolta)
	{
		if (it.second)
		{
			it.second = false;
		}
	}
}

bool ManipuladorDeEntrada::teclaPressionada(sf::Keyboard::Key tecla)
{
	return m_teclaPressionada[tecla];
}

bool ManipuladorDeEntrada::teclaSegurada(sf::Keyboard::Key tecla)
{
	return m_teclaSegurada[tecla];
}
bool ManipuladorDeEntrada::teclaSolta(sf::Keyboard::Key tecla)
{
	return m_teclaSolta[tecla];
}


bool ManipuladorDeEntrada::eventoTeclado(const sf::Event& evento)
{
	if (evento.type == sf::Event::KeyPressed)
	{
		m_teclaPressionada[evento.key.code] = not m_teclaSegurada[evento.key.code];
		m_teclaSegurada[evento.key.code] = false;
		return true;
	}
}

bool ManipuladorDeEntrada::eventoMouse(const sf::Event& evento)
{
	if (evento.type == sf::Event::MouseButtonPressed)
	{
		m_botaoMousePressionado[evento.mouseButton.button] = not m_botaoMouseSegurado[evento.mouseButton.button];
		m_botaoMouseSolto[evento.mouseButton.button] = false;
		return true;
	}
	else if (evento.type == sf::Event::MouseButtonReleased)
	{
		m_botaoMousePressionado[evento.mouseButton.button] = false;
		m_botaoMouseSegurado[evento.mouseButton.button] = false;
		m_botaoMouseSolto[evento.mouseButton.button] = true;
	}
	else if (evento.type == sf::Event::MouseMoved)
	{
		m_mouseAnterior = m_mouseAtual;
		PosicaoMouse mouse(evento.mouseMove.x, evento.mouseMove.y);
		m_mouseAtual = mouse;
		m_mouseMovido = true;
		return true;
	}
	return false;
}