#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Engine.h"
#include "AI.h"
#include "Stats.h"
#include "Inventory.h"

#include "HelperFunctions.h"

class Engine;
class Inventory;
class AI;


class Entity
{
public:
	//Constructors & Destructors
	Entity(sf::String name, sf::Vector2i pos, sf::Sprite sprite);
	Entity(const Entity& copy);
	Entity();
	~Entity();
	
	//Accessors
	sf::String name();
	sf::Sprite* sprite();
	sf::Vector2i pos(); 
	Engine* engine();
	int spriteSize();
	int attribute(sf::String attribute);
	int skill(sf::String skill, bool skillUsed = false);
	int currentResource(sf::String resource);
	int maxResource(sf::String resource);
	AI* ai();

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
	void update();
	void FOV();


	//Combat Functions
	void attack(Entity* target);
	int takeDamage(int damage);
	void die();
	bool died();
	

private:
	static Engine* m_engine;
	sf::String m_name;
	sf::Sprite m_sprite;
	sf::Vector2i m_pos;

	std::unique_ptr<Inventory> m_inventory;

	std::unique_ptr<AttributeComponent> m_attributes;
	std::unique_ptr<SkillComponent> m_skills;
	std::unique_ptr<ResourceComponent> m_resources;
	std::unique_ptr<AI> m_AI;
	
	static int m_spriteSize;
};


#endif
