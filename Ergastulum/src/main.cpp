
#include "Engine.h"
#include "Pathfinding.h"

#include "Fov.h"
#include "Color.h"
#include "Character.h"
#include "GUI.h"
#include "Menu.h"
#include "InputHandler.h"
#include "Engine.h"

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
	Engine engine(800,600,200,tileSize,0,10);
	engine.initMap(&engine,30,30);
	Pathfinding::initPathfinding(engine.currentMap());
	engine.gui()->menu("gameInterface")->addText(10, 10, 12, "playerName", engine.player()->name(), engine.gui()->font("Arial"), Color::Black);
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
			if (engine.handler()->isMouseButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i pos(engine.handler()->getMouseCurrentPosition().x, engine.handler()->getMouseCurrentPosition().y);
				sf::Vector2f viewPos(engine.m_view.getCenter());
				sf::Vector2f viewSize(engine.m_view.getSize());

				float viewZeroX = viewPos.x- (viewSize.x / 2);
				float viewZeroY = viewPos.y- (viewSize.y / 2);
				float relativeX = (pos.x+viewZeroX);
				float relativeY = (pos.y+viewZeroY);

								
				int tileX = relativeX / tileSize;
				int tileY = relativeY / tileSize;
				Tile* tile = engine.currentMap()->tile(sf::Vector2i(tileX, tileY));
				engine.currentMap()->wall(tile);
			}
		}
		engine.update();
		engine.render();
	}
	return 0;
}