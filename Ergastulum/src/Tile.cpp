#include "Tile.h"

int Tile::m_spriteSize;

//Constructors & Destructors
Tile::Tile(sf::Vector2i pos, sf::Sprite sprite, bool passable, bool opaque)
{
	this->m_pos = pos;
	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)pos.x * m_spriteSize, (float)pos.y * m_spriteSize);
	this->m_passable = passable;
	this->m_opaque = opaque;
	this->m_visible = false;
	this->m_explored = false;
}

Tile::~Tile()
{

}

//Accessors
/**Returns the tile's sprite.*/
sf::Sprite *Tile::sprite()
{
	return &m_sprite;
}

/**Returns the tile's absolute position in the grid.*/
sf::Vector2i Tile::pos()
{
	return m_pos;
}

/**Returns the tile's bool passable*/
bool Tile::passable()
{
	return m_passable;
}
/**Returns the tile's bool opaque*/
bool Tile::opaque()
{
	return m_opaque;
}

bool Tile::explored()
{
	return m_explored;
}

bool Tile::visible()
{
	return m_visible;
}

/**Returns the tile's occupant Entity.*/
Entity* Tile::occupant()
{
	return m_occupant;
}

//Mutators
/**Sets the tile's sprite.*/
void Tile::sprite(sf::Sprite sprite)
{
	m_sprite = sprite;
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
}

/**Sets the tile's absolute position in the grid.*/
void Tile::pos(sf::Vector2i pos)
{
	m_pos = pos;
}

/**Sets the tile's bool passable.*/
void Tile::passable(bool passable)
{
	m_passable = passable;
}

void Tile::opaque(bool opaque)
{
	m_opaque = opaque;
}

void Tile::explored(bool explored)
{
	m_explored = explored;
}

void Tile::visible(bool visible)
{
	m_visible = visible;
}

/**Sets the tile's occupant Entity.*/
void Tile::occupant(Entity* occupant)
{
	m_occupant = occupant;
}

void Tile::spriteSize(int spriteSize)
{
	m_spriteSize = spriteSize;
}