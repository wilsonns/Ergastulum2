#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

#include "Engine.h"
#include "Entidade.h"
#include "Mapa.h"

#include "Globais.h"

int main()
{
	sf::SoundBuffer s;
	s.loadFromFile("Recursos/Sons/Musica/Menu.wav");
	sf::Sound sound;
	sound.setBuffer(s);
	sound.play();

	int tamanhoTile = 64;
	Engine engine(800,600,200,tamanhoTile,0);
	engine.mapaAtual()->adcionarEntidade("Jack",sf::Vector2i(3, 3), engine.sprite(4),&engine.manipulador);
	engine.jogador(engine.mapaAtual()->tile(sf::Vector2i(3, 3))->ocupante());
	engine.m_gui->adcionarTexto(10, 10, 12, engine.jogador()->nome(), *engine.m_gui->m_fontes["Arial"].get(), sf::Color::Black);

	while (engine.m_janela->isOpen())
	{
		engine.manipulador.atualizar();
		sf::Event evento;
		while (engine.m_janela->pollEvent(evento))
		{
			engine.manipulador.manipularEvento(evento);
			if (evento.type == sf::Event::Closed)
			{
				engine.m_janela->close();
			}
		}
		engine.atualizar();
		engine.render();
	}
	return 0;
}