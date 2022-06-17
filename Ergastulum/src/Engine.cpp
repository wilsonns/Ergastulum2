#include "Engine.h"

#include "Color.h"
#include "RNG.h"
#include "InputHandler.h"

#include "Map.h"
#include "GUI.h"
#include "Entity.h"
#include "Character.h"
#include "Item.h"
#include "FOV.h"
#include "Menu.h"

//Constructors & Desctructors
Engine::Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap, float framesPerSecond)
{
	m_gameState[CURRENT] = START_MENU;
	this->m_tileSize = tileSize;
	
	m_startScreen.loadFromFile("Assets/Graphics/Menu.png");

	
	Entity::spriteSize(tileSize);
	
	Inventory::engine(this);

	m_framesPerSecond = framesPerSecond;


	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Ergastulum");

	texture(loadTexture("Assets/Graphics/Entities/Entities.png"), "Entities");
	texture(loadTexture("Assets/Graphics/Entities/Human.png"), "Human");
	texture(loadTexture("Assets/Graphics/Entities/Zombie.png"), "Zombie");
	texture(loadTexture("Assets/Graphics/Entities/Abomination.png"), "Abomination");
	texture(loadTexture("Assets/Graphics/Terrain/Dummy.png"), "Dummy");
	texture(loadTexture("Assets/Graphics/Terrain/Dummywall.png"), "Dummywall");

	texture(loadTexture("Assets/Graphics/Items/BastardSword.png"), "BastardSword");

	m_spritesheets["Entities"];
	m_spritesheets["Terrain"];
	m_spritesheets["Items"];

	makeTileSet(texture("Entities"), tileSize, tileGap, spritesheet("Entities"));
	makeTileSet(texture("Dummy"), tileSize, tileGap, spritesheet("Terrain"));
	makeTileSet(texture("Dummywall"), tileSize, tileGap, spritesheet("Terrain"));
	makeTileSet(texture("BastardSword"), tileSize, tileGap, spritesheet("Items"));

	m_gui = std::make_unique<GUI>(0, (height - guiHeight), width, guiHeight, Color::White, Color::Black, m_window.get(), this);
	this->m_fixed = m_window.get()->getView();
	this->m_view = m_fixed;
	this->m_handler = std::make_unique<InputHandler>();

	RNG::seed();
	
	m_elapsedTime = m_clock.restart();
	
	return;
}

Engine::~Engine()
{
	return;
}


//Functions
void Engine::update()
{
	if (m_gameState[CURRENT] == START_MENU)
	{
		gui()->menu("mainMenu")->update();
	}
	else
	{
		m_currentMap.get()->update();
		if (m_gameState[CURRENT] == GAME_START || m_gameState[CURRENT] == PLAYER_TURN)
		{
			ShadowCastingFOV::computeFov(m_fovMap.get(), currentMap(), m_player->pos().x, m_player->pos().y, 8);//PENDING - Radius need to be changed
			m_player->update();
		}
		else if (m_gameState[CURRENT] == ENEMY_TURN)
		{
			for (std::vector<std::unique_ptr<Character>>::iterator it = m_characters.begin();
				it != m_characters.end();it++)
			{
				if ((*it).get() == m_player)
				{
					continue;
				}
				else
				{
					(*it).get()->update();

				}
			}
			m_gameState[CURRENT] = PLAYER_TURN;
		}
		else if (m_gameState[CURRENT] == INVENTORY_MENU)
		{
			m_player->update();
		}
		else if (m_gameState[CURRENT] == CHARACTER_MENU)
		{
			m_player->update();
		}
		m_gui->update();
		return;
	}
}

void Engine::render()
{
	float elapsedTime = m_clock.restart().asSeconds();
	m_window->clear();
	


	if (gameState(CURRENT) == START_MENU)
	{
		gui()->menu("mainMenu")->render(m_window.get());
	}
	else
	{

		m_window.get()->setView(m_view);
		m_view.setCenter(sf::Vector2f((float)(m_player->pos().x * m_tileSize), (float)((m_player->pos().y * m_tileSize) + (m_tileSize * 3))));
		m_currentMap->render(m_window.get());
		for (auto& item : m_items)
		{
			if (currentMap()->tile(item.get()->pos())->visible() && item.get()->owner() == nullptr)
			{
				item.get()->render(m_window.get());
			}
		}
		for (auto& character : m_characters)
		{
			if (currentMap()->tile(character.get()->pos())->visible())
			{
				character.get()->render(m_window.get(), elapsedTime);
				//			m_window->draw(*character.get()->sprite());
			}
		}
		m_window.get()->setView(m_fixed);
		m_gui->render(m_window.get());

	}
	m_window.get()->display();
	return;
}


//Accessors
/**Returns the size of the Tiles in the grid*/
int Engine::tileSize()
{
	return m_tileSize;
}

/**Returns a sf::Texture from the m_textures map.*/
sf::Texture* Engine::texture(std::string st)
{
	if (m_textures.find(st) != m_textures.end())
	{
		return m_textures[st].get();
	}
	std::cout << "Texture not found" << std::endl;
	return m_textures["Dummy"].get();
}

/**Loads and returns a texture from a string representing the directory.
* std::string file refers to the directory.
* bool colorKey, if true, gets the background color of the loaded image and swaps it for alpha 0.
*/
sf::Texture Engine::loadTexture(std::string file, bool colorKey)
{
	sf::Image image;
	try
	{
		throw image.loadFromFile(file);
	}
	catch(bool answer)
	{
		if (!answer)
		{
			std::cout << "File not found" << std::endl;
			throw;
		}
	}
	if (colorKey)
	{
		image.createMaskFromColor(image.getPixel(0, 0));
	}
	sf::Texture texture;
	texture.loadFromImage(image);
	return texture;
}

/**Makes and returns an sf::Sprite from a texture and a rectangle.*/
sf::Sprite Engine::makeSprite(sf::Texture *texture, sf::IntRect rect)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setTextureRect(rect);
	return sprite;
}

/**Returns a sf::Sprite from a given map.
* int sp is the index.
* map sprites is the map.
*/
sf::Sprite Engine::sprite(unsigned int sp,sf::String map)
{
	return *m_spritesheets[map][sp].get();
}

/**Gets m_player.*/
Character* Engine::player()
{
	return m_player;
}

/** Returns correntMap.*/
Map* Engine::currentMap()
{

	return m_currentMap.get();
}

/**Returns GUI*/
GUI* Engine::gui()
{
	return m_gui.get();
}

/**Returns a std::map which stores unique ptrs to sf::Sprites, in other words, a spritesheet.*/
std::map<unsigned int, std::unique_ptr<sf::Sprite>>* Engine::spritesheet(sf::String index) 
{
	return (&m_spritesheets[index]);
}


/**Returns the sf::RenderWindow * window*/
sf::RenderWindow* Engine::window()
{
	return m_window.get();
}

/**Returns the input handler*/
InputHandler* Engine::handler()
{
	return m_handler.get();
}

//Mutators
/**Checks if a texture exists within the texture map. If it doesn't, adds it.*/
void Engine::texture(sf::Texture texture, std::string st)
{
	if (m_textures.find(st) == m_textures.end())
	{
		m_textures.insert(std::make_pair(st, std::make_unique<sf::Texture>(texture)));
	}
	else
	{
		std::cout << "There's already a texture with this name" << std::endl;
	}
}

/**
* Makes a tileset from a texture.
* sf::Texture *texture is a pointer to a sf::Texture.
* int tileSize is the size of each tile in pixels.
* int tileGap is the gap between each tile in the texture. 0 if there is no gap.
* map sprites  is a given map to add the sprites to.
*/
void Engine::makeTileSet(sf::Texture* texture, unsigned int tileSize, unsigned int tileGap, std::map<unsigned int, std::unique_ptr<sf::Sprite>>* sprites)
{
	size_t it = sprites->size();
	int tiles = (texture->getSize().x / tileSize) * (texture->getSize().y / tileSize);
	for (int y = 0; y < (texture->getSize().y / tileSize);y++)
	{
		for (int x = 0; x < (texture->getSize().x / tileSize);x++)
		{
			sf::Sprite sp;
			sp.setTexture(*texture);
			sp.setTextureRect(sf::IntRect(x*tileSize,y*tileSize,tileSize,tileSize));
			sprites->emplace(std::make_pair(it, std::make_unique<sf::Sprite>(sp)));
			it++;
		}
	}
	if (debug)
	{
	
	}
	return;
}

/**Initializes a Map as the currentMap.*/
void Engine::initMap(Engine* engine,int width, int height)
{
	m_currentMap = std::make_unique<Map>();
	currentMap()->engine(engine);
	currentMap()->init(width, height,m_tileSize, this);
	m_fovMap = std::make_unique<FOVMap>(width, height);
}

/** Sets an character as the m_player.*/
void Engine::player(Character* player)
{
	m_player = player;
}

/**Adds an character to the map in a given position.*/
void Engine::addCharacter(sf::String name, sf::Vector2i pos,sf::Texture* texture)
{
	std::unique_ptr<Character> character;
	character = std::make_unique<Character>(name, pos, texture);
	currentMap()->tile(pos)->occupant(character.get());
	m_characters.push_back(std::move(character));
}

void Engine::addItem(sf::String name, sf::Vector2i pos, sf::Sprite sprite)
{
	std::unique_ptr<Weapon> item;
	AttributeComponent AttCom;
	
	AttCom.attribute("Attack", 1);
	AttCom.attribute("Weight", 1);
	AttCom.attribute("Damage", 100);

	item = std::make_unique<Weapon>(name, pos, sprite, AttCom);//PENDING - make items more varied
	currentMap()->tile(pos)->inventory()->addItem(item.get());
	m_items.push_back(std::move(item));
}

void Engine::addItem(const json& file, sf::String name, sf::Vector2i pos)
{
	std::unique_ptr<Weapon> item;
	item = std::make_unique<Weapon>(file,name, pos);
	currentMap()->tile(pos)->inventory()->addItem(item.get());
	m_items.push_back(std::move(item));
}


void Engine::addCharacter(const json& file,sf::String mob, sf::Vector2i pos)
{
	std::unique_ptr<Character> character;
	character = std::make_unique<Character>(file, mob, pos);
	currentMap()->tile(pos)->occupant(character.get());
	m_characters.push_back(std::move(character));
}

void Engine::gotoGame()
{
	gameState(GameStates::GAME_START);
}

void Engine::gameState(GameStates gameState)
{
	GameStates tmp = m_gameState[CURRENT];
	m_gameState[CURRENT] = gameState;
	m_gameState[PREVIOUS] = tmp;
}