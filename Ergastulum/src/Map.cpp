#include "Map.h"

int Map::m_spriteSize;

//Constructors & Destructors
Map::Map(unsigned int width, unsigned int height, unsigned int spriteSize, Engine* engine)
{
	this->m_width = width;
	this->m_height = height;
	this->m_spriteSize = spriteSize;
	Tile::spriteSize(spriteSize);
	m_engine = engine;
	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height;y++)
		{
			bool passable = false;
			int sp = 1;
			m_tiles.push_back(std::make_unique<Tile>(sf::Vector2i(x, y), m_engine->sprite(sp, "Terrain"), passable));
		}
	}
	
	m_BSP = std::make_unique<BSP>(0,0,m_width,m_height, this);
	m_BSP.get()->recursiveSplit(2, maxRoomSize,maxRoomSize, 1.5f, 1.5f);
	BSPListener listener((this));
	m_BSP.get()->traverseInOrder(&listener);
	return;
}

Map::Map()
{

}

Map::~Map()
{

}

//Accessors
/**Returns a Tile pointer in the pos position.*/
Tile *Map::tile(sf::Vector2i pos)
{
	return m_tiles[pos.x + pos.y * m_width].get();
}
int Map::height()
{
	return m_height;
}
int Map::width()
{
	return m_width;
}

//Mutators
void Map::engine(Engine* engine)
{
	m_engine = engine;
}

void Map::spriteSize(int spriteSize)
{
	m_spriteSize = spriteSize;
}

//Functions
/**Renders each tile and then each entity in the Map.*/
void Map::render(sf::RenderWindow* window)
{
	for (auto& tile : m_tiles)
	{
		if (tile->visible() == true)
		{
			tile->sprite()->setColor(sf::Color::White);
			window->draw(*tile->sprite());
		}
		else if (tile->visible() == false && tile->explored() == true)
		{
			tile->sprite()->setColor(sf::Color(100,100,100));
			window->draw(*tile->sprite());
		}
	}
}

void Map::update()
{
	for (auto& tile : m_tiles)
	{
		tile->visible(false);
	}
}

void Map::init(unsigned int width, unsigned int height, unsigned int spriteSize, Engine* engine)
{
	this->m_width = width;
	this->m_height = height;
	this->m_spriteSize = spriteSize;
	m_engine = engine;
	Tile::spriteSize(spriteSize);
	for (unsigned int y = 0; y < height;y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			bool passable = false;
			int sp = 1;
			m_tiles.push_back(std::make_unique<Tile>(sf::Vector2i(x, y), m_engine->sprite(sp, "Terrain"), passable, true));
		}
	}

	m_BSP = std::make_unique<BSP>(0,0,m_width,m_height, this);
	m_BSP.get()->recursiveSplit(4, maxRoomSize, maxRoomSize, 1.5f, 1.5f);
	BSPListener listener((this));
	m_BSP.get()->traverseInOrder(&listener);
	for (int y = 0; y < m_height;y++)
	{
		std::cout << std::endl;
		for (int x = 0; x < m_width;x++)
		{
			std::cout << tile(sf::Vector2i(x, y))->passable() ? "." : "#";
		}
	}
	return;
}

/**Chekcs if a tile is walkable.*/
bool Map::isWalkable(Tile* tile)
{
	if (tile->occupant() == nullptr && tile->passable())
	{
		return true;
	}
	return false;
}

bool Map::occupant(sf::Vector2i pos)
{
	return tile(pos)->occupant() != nullptr;
}

void Map::dig(Tile* tile)
{
	tile->passable(true);
	tile->opaque(false);
	tile->sprite(m_engine->sprite(0, "Terrain"));
}

void Map::dig(int x, int y, int width, int height)
{
	for (int i = y; i <= height; i++)
	{
		for (int j = x; j <= width; j++)
		{
			dig(tile(sf::Vector2i(j,i)));
		}
	}
}

void Map::createRoom(bool first, int x, int y, int width, int height)
{
	dig(x,y,width,height);
	if (first)
	{
		sf::Vector2i pos(RNG::randInt(x, width), RNG::randInt(y, height));
		m_engine->addEntity("Jack",pos, m_engine->sprite(0, "Entities"));
		m_engine->player(m_engine->currentMap()->tile(pos)->occupant());
		m_engine->player()->engine(m_engine);
		m_engine->player()->ai(std::make_unique<PlayerAI>());
		m_engine->player()->ai()->engine(m_engine);
	}
	else
	{
		if (RNG::randInt(1, 3) > 0)
		{
			sf::Vector2i pos(RNG::randInt(x, width), RNG::randInt(y, height));
			m_engine->addEntity("Zombie", pos, m_engine->sprite(1, "Entities"));
			m_engine->currentMap()->tile(pos)->occupant()->ai(std::make_unique<DummyAI>());
		}
	}

}