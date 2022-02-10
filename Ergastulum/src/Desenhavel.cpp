#include "Desenhavel.h"

Desenhavel::Desenhavel(sf::Texture* textura)
{
	sf::Vector2u tamanho = textura->getSize();
	for (unsigned int x = 0; x < tamanho.x;x += 32)
	{
		for (unsigned int y = 0; y < tamanho.y;y += 32)
		{
			_sprite.push_back(new sf::Sprite());
		}
	}
	for (unsigned int y = 0; y < tamanho.y/TILE_SIZE;y ++)
	{
		for (unsigned int x = 0; x < tamanho.x/TILE_SIZE;x ++)
		{
			_sprite[x + y * (tamanho.y/TILE_SIZE)]->setTextureRect(sf::IntRect(x*TILE_SIZE, y*TILE_SIZE, 32, 32));
			_sprite[x + y * (tamanho.y/TILE_SIZE)]->setTexture(*textura);
		}
	}

	_atual = _sprite.begin();
}

Desenhavel::~Desenhavel()
{
	for (auto sprite : _sprite)
	{
		delete sprite;
	}
}

void Desenhavel::pos(sf::Vector2f vec)
{
	_pos = vec;
	(*_atual)->setPosition(_pos);
}

sf::Sprite Desenhavel::sprite()
{
	return *(*_atual);
}

void Desenhavel::sprite(sf::Texture* textura, sf::IntRect rect)
{
	//_sprite.setTextureRect(rect);
	//_sprite.setTexture(*textura);
}

void Desenhavel::mover(float x, float y)
{
	/*_pos = sf::Vector2f(_pos.x + x, _pos.y + y);
	if (y > 0)
	{
		_atual = _sprite.begin();
	}
	if (x > 0)
	{
		_atual = _sprite.begin()+4;
	}
	if (x < 0)
	{
		_atual = _sprite.begin() + 8;
	}
	if (y < 0)
	{
		_atual = _sprite.begin() + 12;
	}
	(*_atual)->setPosition(_pos.x, _pos.y);
	*/
}