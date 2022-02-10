#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "Map.h"
#include "GUI.h"
#include "InputHandler.h"

#include "Globals.h"

class Map;
class GUI;
class Entity;

class Engine
{
public:
	//Constructors & Desctructors
	Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap);
	~Engine();
	
	//Functions
	void update();
	void render();

	//Accessors
	sf::Texture* texture(std::string st);//retorna uma textura do mapa m_texturas
	sf::Texture loadTexture(std::string file, bool colorKey = false);//Carrega uma textura a partir de um arquivo
	sf::Sprite makeSprite(sf::Texture* texture, sf::IntRect rect = sf::IntRect(0, 0, 64, 64));//retorna um Sprite a partir de uma textura + um retangulo
	sf::Sprite sprite(unsigned int sp, std::map<unsigned int, std::unique_ptr<sf::Sprite>> sprite);
	Entity* player();
	Map* currentMap();

	//Mutators
	void texture(sf::Texture texture, std::string st); //adciona uma textura nova ao mapa m_texturas
	void sprite(sf::String sprite, sf::Texture* texture, sf::IntRect rect = sf::IntRect(0, 0, 64, 64));//adciona um sprite ao bagulho ali sei la fodasse
	void makeTileSet(sf::Texture* textura, unsigned int tamanhoTile, unsigned int vazioTile, std::map<unsigned int, std::unique_ptr<sf::Sprite>>* sprites);
	void player(Entity* player);
	void initMap();

	
private:
	bool debug;
	Entity* m_player;
	std::unique_ptr<Map> m_currentMap;
	std::map<std::string,std::unique_ptr<sf::Texture>> m_textures;
	std::map<unsigned int, std::unique_ptr<sf::Sprite>> m_terrainSprites;
	std::map<unsigned int, std::unique_ptr<sf::Sprite>> m_entitySprites;
protected:
	std::unique_ptr<sf::RenderWindow> m_window;
	InputHandler handler;
	int m_tileSize;
	GUI* m_gui;
	std::vector<sf::String> m_attributes;
};

extern Engine engine;

#endif