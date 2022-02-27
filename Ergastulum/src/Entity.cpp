#include "Entity.h"

Engine* Entity::m_engine;
int Entity::m_spriteSize;

//Constructors & Destructors
Entity::Entity(sf::String name, sf::Vector2i pos, sf::Sprite sprite)
{
	this->m_name = name;
	this->m_pos = pos;
	this->m_sprite = sprite;
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
	
	//Create unique_ptrs
	this->m_attributes = std::make_unique<AttributeComponent>();
	this->m_skills = std::make_unique<SkillComponent>();
	this->m_resources = std::make_unique<ResourceComponent>();

	this->m_inventory = std::make_unique<Inventory>(10);

	m_attributes.get()->attribute("Strength",10);
	m_attributes.get()->attribute("Dexterity", 10);
	m_attributes.get()->attribute("Intelect", 10);
	m_attributes.get()->attribute("Vitality", 10);
	m_attributes.get()->attribute("DR", 0);
	m_attributes.get()->attribute("Speed", 90 + attribute("Dexterity"));

	m_skills.get()->skill("Melee", 0);
	m_skills.get()->skill("Dodge", 0);


	m_resources.get()->maxLevel("Health",attribute("Strength")*3+attribute("Vitality")*2);
	m_resources.get()->currentLevel("Health", m_resources.get()->maxLevel("Health"));
	m_resources.get()->maxLevel("Energy",attribute("Vitality") * 10);
	m_resources.get()->currentLevel("Energy", m_resources.get()->maxLevel("Energy"));

	std::cout << "Entity created." << std::endl;
}

Entity::Entity(const Entity& copy)
{
	this->m_name = copy.m_name;
	this->m_pos = copy.m_pos;
	this->m_sprite = copy.m_sprite;
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
	
	std::cout << "Entity copied!" << std::endl;
}

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

/**Returns a given attribute's level.*/
int Entity::attribute(sf::String attribute)
{
	return m_attributes.get()->attribute(attribute);
}

/**Returns a given skill's level and, if it was used, gives some XP to it.*/
int Entity::skill(sf::String skill, bool skillUsed)
{
	//PENDING: Need to have different XP levels for different activities
	if (skillUsed)
	{
		m_skills.get()->skillUsed(skill, 10);
	}
	return 	m_skills.get()->skill(skill);
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
/**Offsets the entity's postion on the grid.*/
void Entity::move(sf::Vector2i offset)
{
	engine()->currentMap()->tile(sf::Vector2i(m_pos.x, m_pos.y))->occupant(nullptr);
	m_pos.x += offset.x;
	m_pos.y += offset.y;
	engine()->currentMap()->tile(sf::Vector2i(m_pos.x, m_pos.y))->occupant(this);
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
/**Updates the entity.*/
void Entity::update()
{
	if (m_AI.get())
	{
		m_AI.get()->update(this);
	}
	return;
}


/**Compute the Field of View from a given character.*/
void Entity::FOV()
{
	for (unsigned short int i = 0; i < 360; i++)
	{
		int x = pos().x;
		int y = pos().y;
		unsigned int nx = 0;
		unsigned int ny = 0;
		float degree = i * 0.0174532f;
		nx = round(cos(degree) * 3) + x;
		ny = round(sin(degree) * 3) + y;

		int d = diagonalDistance(x, y, nx, ny);
		for (int j = 0; j < d;j++)
		{
			int tx = lerp(x, nx, j / ((float)d));
			int ty = lerp(y, ny, j / ((float)d));

			if (tx < 0 || tx > engine()->currentMap()->width() - 1)
			{
				continue;
			}
			if (ty < 0 || ty > engine()->currentMap()->height() - 1)
			{
				continue;
			}
			engine()->currentMap()->tile(sf::Vector2i(tx, ty))->explored(true);
			engine()->currentMap()->tile(sf::Vector2i(tx, ty))->visible(true);

			if (engine()->currentMap()->tile(sf::Vector2i(tx, ty))->opaque())
			{
				break;
			}
		}
	}
}

//Combat Functions
/** The character attacks another one.
* Entity* target is the entity to be attacked by this one.*/
void Entity::attack(Entity* target)
{
	int sides;
	int dice;

	dice = (attribute("Dexterity")/ 4) + (skill("Melee",true) / 2);
	sides = attribute("Dexterity");
	
	int hit = 0;
	for (int i = 0; i < dice; i++)
	{
		hit += RNG::randInt(1, sides);
	}

	int toHit = 0;
	for (int i = 0; i < target->skill("Dodge",true);i++)
	{
		toHit += RNG::randInt(1, 10);
	}


		
	if (hit > toHit)
	{
		int damage = RNG::randInt(0,attribute("Strength"));

		damage = target->takeDamage(damage);
		if (damage < 1)
		{
			engine()->gui()->addMessage(this->name() + " attacks " + target->name() + ", but the attack glances off.",
				engine()->gui()->font("Arial"), sf::Color::Black);
		}
		else
		{
			engine()->gui()->addMessage(this->name() + " attacks " + target->name() + ", causing " + std::to_string(damage)
				+ " damage!", engine()->gui()->font("Arial"), sf::Color::Red);
			if (target->died())
			{
				engine()->gui()->addMessage(target->name() + " dies!", engine()->gui()->font("Arial"), sf::Color(200, 50, 50));
			}
		}
	}
	else
	{
		engine()->gui()->addMessage(this->name() + " attacks " + target->name() + ", but misses.", engine()->gui()->font("Arial"), sf::Color::Black);
	}
}


/**Processes int damage and returns it after calculating how DR impacts damage*/
int Entity::takeDamage(int damage)
{
	damage -= attribute("DR");
	if (damage <= 0)
	{
		damage = 0;
		return damage;
	}
	currentResource("Health",(-1)*damage);
	die();
	return damage;
}

/**Kills a character if their HP gets < 0.*/
void Entity::die()
{
	if (currentResource("Health") < 1)
	{
		ai(nullptr);
		this->sprite()->rotate(90.f);
		this->sprite()->move(spriteSize(), 0);
		engine()->currentMap()->tile(pos())->occupant(nullptr);
	}
}

/**Checks if a character's HP is < 0;*/
bool Entity::died()
{
	return currentResource("Health") < 1;
}
