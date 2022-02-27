#include "Engine.h"

//Constructors & Desctructors
Engine::Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap)
{
	m_gameState = START;
	this->m_tileSize = tileSize;
	Entity::spriteSize(tileSize);
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Ergastulum:Histórias de X e Y");
	texture(loadTexture("Assets/Graphics/Entities/Entities.png"), "Entities");
	texture(loadTexture("Assets/Graphics/Terrain/Dummy.png"), "Dummy");
	texture(loadTexture("Assets/Graphics/Terrain/Dummywall.png"), "Dummywall");
	m_spritesheets["Entities"];
	m_spritesheets["Terrain"];
	makeTileSet(texture("Entities"), tileSize, tileGap, spritesheet("Entities"));
	makeTileSet(texture("Dummy"), tileSize, tileGap, spritesheet("Terrain"));
	makeTileSet(texture("Dummywall"), tileSize, tileGap, spritesheet("Terrain"));
	m_gui = new GUI(0, (height-guiHeight), height, guiHeight,sf::Color::White,sf::Color::Black, m_window.get() , this);
	this->m_fixed = m_window.get()->getView();
	this->m_view = m_fixed;
	this->m_handler = std::make_unique<InputHandler>();
	RNG::seed();
	return;
}

Engine::~Engine()
{
	return;
}


//Functions
void Engine::update()
{
	m_currentMap.get()->update();
	if (m_gameState == START || m_gameState == PLAYER_TURN)
	{
		m_player->FOV();
		m_player->update();
	}
	else if (m_gameState == ENEMY_TURN)
	{
		for (std::vector<std::unique_ptr<Entity>>::iterator it = m_entities.begin();
			it != m_entities.end();it++)
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
		m_gameState = PLAYER_TURN;
	}
	return;
}

void Engine::render()
{
	m_window->clear();
	
	m_window.get()->setView(m_view);
	m_view.setCenter(sf::Vector2f((float)(m_player->pos().x*m_tileSize), (float)((m_player->pos().y*m_tileSize)+(m_tileSize*3))));
	m_currentMap->render(m_window.get());
	for (auto& entity : m_entities)
	{
		if (currentMap()->tile(entity.get()->pos())->visible())
		{
			m_window->draw(*entity.get()->sprite());
		}
	}
	m_window.get()->setView(m_fixed);
	m_gui->render(m_window.get());
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
* std::string refers to the directory.
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
Entity* Engine::player()
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
	return m_gui;
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
	int xGap = 1;
	int yGap = 0;
	int tiles = (texture->getSize().x / tileSize) * (texture->getSize().y / tileSize);
	for (int y = 0; y < (texture->getSize().y / tileSize);y++)
	{
		xGap = 1;
		yGap++;
		for (int x = 0; x < (texture->getSize().x / tileSize);x++)
		{
			sf::Sprite sp;
			sp.setTexture(*texture);
			sp.setTextureRect(sf::IntRect((x * tileSize) + (tileGap) ? xGap : 0,
				(y * tileSize) + (tileGap) ? yGap : 0, tileSize, tileSize));
			sprites->emplace(std::make_pair(it, std::make_unique<sf::Sprite>(sp)));
			it++;
			xGap++;
		}
	}
	if (debug)
	{
	
	}
	return;
}

/**Initializes a Map as the currentMap.*/
void Engine::initMap(Engine* engine)
{
	m_currentMap = std::make_unique<Map>();
	currentMap()->engine(engine);
	currentMap()->init(20, 20,m_tileSize, this);
}

/** Sets an Entity as the m_player.*/
void Engine::player(Entity* player)
{
	m_player = player;
}

/**Adds an entity to the map in a given position.*/
void Engine::addEntity(sf::String name, sf::Vector2i pos, sf::Sprite sprite)
{
	std::unique_ptr<Entity> entity;
	entity = std::make_unique<Entity>(name, pos, sprite);
	currentMap()->tile(pos)->occupant(entity.get());
	m_entities.push_back(std::move(entity));
}

void Engine::gameState(GameStates gameState)
{
	m_gameState = gameState;
}