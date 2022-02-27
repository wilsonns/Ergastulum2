
#include "Engine.h"
#include "Pathfinding.h"

int main()
{
	/*
	sf::SoundBuffer s;
	s.loadFromFile("Assets/Sounds/Musica/Menu.wav");
	sf::Sound sound;
	sound.setVolume(10);
	sound.setBuffer(s);
	sound.play();
	*/
	int tileSize = 32;
	Engine engine(800,600,200,tileSize,0);
	engine.initMap(&engine);
	Pathfinding::initPathfinding(engine.currentMap());
	engine.gui()->addText(10, 10, 12,"playerName", engine.player()->name(), engine.gui()->font("Arial"), sf::Color::Black);
	while (engine.window()->isOpen())
	{
		engine.handler()->update();
		sf::Event event;
		while (engine.window()->pollEvent(event))
		{
			engine.handler()->handleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				engine.window()->close();
			}
		}
		engine.update();
		engine.render();
	}
	return 0;
}