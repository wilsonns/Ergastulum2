#ifndef ENGINE_H
#define ENGINE_H

#include<SFML/Graphics.hpp>
#include<nlohmann/json.hpp>



using json = nlohmann::json;

class Map;
class GUI;
class Character;
class Item;
class AI;
class InputHandler;

struct FOVMap;

class Engine
{
public:
	enum GameStates
	{
		START_MENU = 0,
		GAME_START,
		PLAYER_TURN,
		ENEMY_TURN,
		INVENTORY_MENU,
		CHARACTER_MENU,
		ANY = 999
	};
	enum StateNumber
	{
		CURRENT = 0,
		PREVIOUS
	};
	//Constructors & Desctructors
	Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap, float framesPerSecond);
	~Engine();


	//Accessors
	int tileSize();
	sf::Texture* texture(std::string st);
	sf::Texture loadTexture(std::string file, bool colorKey = false);
	sf::Sprite makeSprite(sf::Texture* texture, sf::IntRect rect);
	sf::Sprite sprite(unsigned int sp, sf::String map);
	Character* player();
	Map* currentMap();
	GUI* gui();
	std::map<unsigned int, std::unique_ptr<sf::Sprite>>* spritesheet(sf::String index);
	sf::RenderWindow* window();
	InputHandler* handler();

	
	inline GameStates gameState(StateNumber state)
	{
		//return the GameState ín the StateNumber
		return m_gameState[state];
	}

	//Mutators
	void texture(sf::Texture texture, std::string st); //adciona uma textura nova ao mapa m_texturas
	void sprite(sf::String sprite, sf::Texture* texture, sf::IntRect rect);//adciona um sprite ao bagulho ali sei la fodasse
	void makeTileSet(sf::Texture* texture, unsigned int tileSize, unsigned int vazioTile, std::map<unsigned int, std::unique_ptr<sf::Sprite>>* sprites);
	void player(Character* player);
	void initMap(Engine *engine, int width, int height);
	void gameState(GameStates gameState);

	//Functions
	void update();
	void render();
	void addCharacter(sf::String name, sf::Vector2i pos, sf::Texture* texture);
	void addItem(sf::String name, sf::Vector2i pos, sf::Sprite sprite);
	void addCharacter(const json& file, sf::String mob, sf::Vector2i pos);
	void addItem(const json& file, sf::String name, sf::Vector2i pos);
	void gotoGame();

	sf::View m_view;

	//StartMenu Stuff
	sf::Texture m_startScreen;
private:
	//sf::Window resources
	std::unique_ptr<sf::RenderWindow> m_window;

	sf::View m_fixed;

	//InputHandler resources
	std::unique_ptr<InputHandler> m_handler;

	//Textures and Sprite resources
	std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	std::map<sf::String, std::map<unsigned int, std::unique_ptr<sf::Sprite>>> m_spritesheets;


	//Game Logic Resources
	//Map and Entities
	Character* m_player;
	std::unique_ptr<Map> m_currentMap;
	std::vector<std::unique_ptr<Character>> m_characters;
	std::vector<std::unique_ptr<Item>> m_items;
	std::unique_ptr<FOVMap> m_fovMap;
	sf::Clock m_clock;
	sf::Time m_elapsedTime;
	float m_updatesPerSecond;
	float m_framesPerSecond;

	//GameStates
	std::map<StateNumber, GameStates> m_gameState;

	//Misc.
	bool debug;

protected:
	int m_tileSize;
	std::unique_ptr<GUI> m_gui;
	std::vector<sf::String> m_attributes;
};

#endif