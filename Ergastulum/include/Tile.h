#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#include "Inventory.h"

class Character;
class Inventory;

class Tile
{
public:
	//Constructors & Destructors
	Tile(sf::Vector2i pos, sf::Sprite sprite, bool passable = true, bool opaque = false);
	~Tile();

	//Accessors
	sf::Sprite* sprite();
	sf::Vector2i pos();
	bool passable();
	bool opaque();
	bool explored();
	bool visible();
	Character* occupant();
	Inventory* inventory();

	//Mutators
	void sprite(sf::Sprite sprite);
	void pos(sf::Vector2i pos);
	void passable(bool passable);
	void opaque(bool opaque);
	void explored(bool explored);
	void visible(bool visible);
	void occupant(Character* occupant);
	static void spriteSize(int spriteSize);

private:
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;
	bool m_passable;
	bool m_opaque;
	bool m_explored;
	bool m_visible;
	Character* m_occupant;
	static int m_spriteSize;
	std::unique_ptr<Inventory> m_inventory;

};

#endif