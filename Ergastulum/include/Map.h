#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "BSP.h"
#include "Engine.h"
#include "AI.h"


class BSP;
class Engine;

class Map
{
public:
	//Constructors & Destructors
	Map(unsigned int width, unsigned int height,unsigned int spriteSize, Engine* engine);
	Map();
	~Map();

	//Accessors
	Tile *tile(sf::Vector2i pos);
	int height();
	int width();
	//Mutators
	void engine(Engine* engine);
	static void spriteSize(int spriteSize);
	///Functions
	void render(sf::RenderWindow* window);
	void update();
	void init(unsigned int width, unsigned int height, unsigned int spriteSize, Engine* engine);
	bool isWalkable(Tile* tile);
	bool occupant(sf::Vector2i pos);
	void dig(Tile* tile);
	void dig(int x, int y, int width, int height);
	void createRoom(bool first, int x, int y, int width, int height);

private:
	int m_width, m_height;
	static const int minRoomSize = 2;
	static const int maxRoomSize = 4;
	std::vector<std::unique_ptr<Tile>> m_tiles;
	Engine* m_engine;
	std::unique_ptr<BSP> m_BSP;
	static int m_spriteSize;
};

//

#endif