#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>


#include "RNG.h"
#include "InputHandler.h"


#include "Map.h"
#include "GUI.h"
#include "Entity.h"

class Map;
class GUI;
class Entity;
class AI;

class Engine
{
public:
	enum GameStates
	{
		START = 0,
		PLAYER_TURN,
		ENEMY_TURN
	};
	//Constructors & Desctructors
	Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap);
	~Engine();
	

	//Accessors
	int tileSize();
	sf::Texture* texture(std::string st);
	sf::Texture loadTexture(std::string file, bool colorKey = false);
	sf::Sprite makeSprite(sf::Texture* texture, sf::IntRect rect);
	sf::Sprite sprite(unsigned int sp, sf::String map);
	Entity* player();
	Map* currentMap();
	GUI* gui();
	std::map<unsigned int, std::unique_ptr<sf::Sprite>>* spritesheet(sf::String index);
	sf::RenderWindow* window();
	InputHandler* handler();
	inline GameStates* gameState()
	{
		return &m_gameState;
	}

	//Mutators
	void texture(sf::Texture texture, std::string st); //adciona uma textura nova ao mapa m_texturas
	void sprite(sf::String sprite, sf::Texture* texture, sf::IntRect rect);//adciona um sprite ao bagulho ali sei la fodasse
	void makeTileSet(sf::Texture* texture, unsigned int tileSize, unsigned int vazioTile, std::map<unsigned int, std::unique_ptr<sf::Sprite>>* sprites);
	void player(Entity* player);
	void initMap(Engine *engine);
	void gameState(GameStates gameState);

	//Functions
	void update();
	void render();
	void addEntity(sf::String name, sf::Vector2i pos, sf::Sprite sprite);

private:
	bool debug;
	Entity* m_player;
	std::unique_ptr<Map> m_currentMap;
	std::map<std::string,std::unique_ptr<sf::Texture>> m_textures;
	std::map<sf::String, std::map<unsigned int, std::unique_ptr<sf::Sprite>>> m_spritesheets;
	std::unique_ptr<InputHandler> m_handler;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::unique_ptr<Entity>> m_entities;
	GameStates m_gameState;
	sf::View m_view;
	sf::View m_fixed;
protected:
	int m_tileSize;
	GUI* m_gui;
	std::vector<sf::String> m_attributes;
};

#endif