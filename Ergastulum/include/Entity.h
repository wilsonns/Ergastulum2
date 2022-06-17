#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>

#include "Stats.h"

using json = nlohmann::json;


class Engine;
class Inventory;
class AI;
class AnimationComponent;

class Entity
{
public:
	//Constructors & Destructors
	Entity();
	~Entity();

	//Accessors
	sf::String name();
	sf::Sprite* sprite();
	sf::Vector2i pos(); 
	Engine* engine();
	static int spriteSize();
	int attribute(sf::String attribute);
	int currentResource(sf::String resource);
	int maxResource(sf::String resource);
	AI* ai();
	Inventory* inventory();

	//Mutators
	void name(sf::String name);
	void sprite(sf::Sprite sprite);
	void pos(sf::Vector2i pos);
	void move(sf::Vector2i offset);
	void engine(Engine* engine);
	static void spriteSize(int spriteSize);
	void ai(std::unique_ptr<AI> ai);
	void currentResource(sf::String resource, int offset);
	void maxResource(sf::String resource, int level);

	//Functions
	void update(float elapsedTime);
	void render(sf::RenderTarget* window, float elapsedTime);
protected:
	static Engine* m_engine;
	sf::String m_name;
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;

	std::unique_ptr<Inventory> m_inventory;

	std::unique_ptr<AttributeComponent> m_attributes;
	std::unique_ptr<ResourceComponent> m_resources;
	std::unique_ptr<AnimationComponent> m_animation;
	std::unique_ptr<AI> m_AI;

	static int m_spriteSize;
};


#endif
