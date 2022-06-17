#include "Entity.h"

#include "Color.h"

#include "Engine.h"
#include "AI.h"
#include "Stats.h"
#include "AnimationComponent.h"

#include "HelperFunctions.h"

Engine* Entity::m_engine;
int Entity::m_spriteSize;

//Constructors & Destructors
Entity::Entity()
{

}

Entity::~Entity()
{

}

//Accessors
/**Returns the entitie's name.*/
sf::String Entity::name()
{
	return m_name;
}

/**Returns the entity's sprite.*/
sf::Sprite *Entity::sprite() 
{
	return &m_sprite;
}

/**Returns the entity's position on the grid.*/
sf::Vector2i Entity::pos()
{
	return m_pos;
}

Engine* Entity::engine()
{
	return m_engine;
}


int Entity::spriteSize()
{
	return m_spriteSize;
}


int Entity::attribute(sf::String attribute)
{
	return m_attributes.get()->attribute(attribute);
}

int Entity::currentResource(sf::String resource)
{
	return m_resources.get()->currentLevel(resource);
}

int Entity::maxResource(sf::String resource)
{
	return m_resources.get()->maxLevel(resource);

}

/**Returns the AI*/
AI* Entity::ai()
{
	return m_AI.get();
}

Inventory* Entity::inventory()
{
	return m_inventory.get();
}


//Mutators
/**Sets the entity name.*/
void Entity::name(sf::String name)
{
	this->m_name = name;
}

/**Sets the entity's sprite*/
void Entity::sprite(sf::Sprite sprite) 
{
	m_sprite = sprite;
}

/**Sets the entity's absolute position on the grid*/
void Entity::pos(sf::Vector2i pos)
{
	m_pos = pos;
	m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
}

/**Sets the static m_engine.*/
void Entity::engine(Engine* engine)
{
	m_engine = engine;
}

/**Sets a static spriteSize to be used by all the sprites.*/
void Entity::spriteSize(int spriteSize)
{
	m_spriteSize = spriteSize;
}

/**Sets a new AI*/
void Entity::ai(std::unique_ptr<AI> ai)
{
	if (m_AI.get() == nullptr)
	{
		*m_AI.get() = *ai.get();
	}
	m_AI.swap(ai);
}


void Entity::currentResource(sf::String resource, int offset)
{
	m_resources.get()->currentLevel(resource, offset);
}

void Entity::maxResource(sf::String resource, int level)
{
	m_resources.get()->maxLevel(resource, level);
}

//Functions


void Entity::update(float elapsedTime)
{
	m_animation.get()->update(sf::Vector2f(), 0, elapsedTime);
}

void Entity::render(sf::RenderTarget* window, float elapsedTime)
{
	m_animation.get()->update(sf::Vector2f((float)pos().x * spriteSize(), (float)pos().y * spriteSize()), 0, elapsedTime);
	m_animation.get()->render(window);
}