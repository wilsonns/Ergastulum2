#ifndef DESENHAVEL_H
#define DESENHAVEL_H

#include <SFML/Graphics.hpp>
#include "Entidade.h"
#include <vector>

class Entidade;

class Desenhavel
{
public:
	Desenhavel(sf::Texture* textura);
	~Desenhavel();
	
	void pos(sf::Vector2f vec);
	sf::Sprite sprite();
	
	void sprite(sf::Texture *textura, sf::IntRect rect);
	void mover(float x, float y);
private:
	std::vector<sf::Sprite*> _sprite;
	std::vector<sf::Sprite*>::iterator _atual;
	sf::Vector2f _pos;
	static const int TILE_SIZE = 32;
};

#endif