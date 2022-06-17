#include "Character.h"

#include <memory>

#include "Color.h"
#include "GUI.h"
#include "Menu.h"
#include "Map.h"
#include "AI.h"
#include "Stats.h"
#include "Inventory.h"
#include "Item.h"
#include "AnimationComponent.h"

Character::Character()
{

}

Character::~Character()
{

}

Character::Character(sf::String name, sf::Vector2i pos, sf::Texture* texture)
{
	
	this->m_name = name;
	this->m_pos = pos;
	/*this->m_sprite = sprite;
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
	*/

	//Create unique_ptrs
	this->m_attributes = std::make_unique<AttributeComponent>();
	this->m_skills = std::make_unique<SkillComponent>();
	this->m_resources = std::make_unique<ResourceComponent>();
	this->m_animation = std::make_unique<AnimationComponent>(texture, spriteSize(), 0.6f);
	this->m_inventory = std::make_unique<Inventory>(10);

	m_attributes.get()->attribute("Strength", 10);
	m_attributes.get()->attribute("Dexterity", 10);
	m_attributes.get()->attribute("Intelect", 10);
	m_attributes.get()->attribute("Vitality", 10);
	m_attributes.get()->attribute("DR", 0);
	m_attributes.get()->attribute("Speed", 90 + attribute("Dexterity"));

	m_skills.get()->skill("Melee", 0);
	m_skills.get()->skill("Dodge", 0);


	m_resources.get()->maxLevel("Health", attribute("Strength") * 3 + attribute("Vitality") * 2);
	m_resources.get()->currentLevel("Health", m_resources.get()->maxLevel("Health"));
	m_resources.get()->maxLevel("Energy", attribute("Vitality") * 10);
	m_resources.get()->currentLevel("Energy", m_resources.get()->maxLevel("Energy"));

	std::cout << "Character created." << std::endl;
}

Character::Character(const Character& copy)
{
	this->m_name = copy.m_name;
	this->m_pos = copy.m_pos;
	//this->m_animation = std::make_unique<AnimationComponent>(copy.m_animation.get());


	std::cout << "Character copied!" << std::endl;
}

Character::Character(const json& file, sf::String mob, sf::Vector2i pos)
{
	this->m_name = file.at(mob).at("name");
	this->m_pos = pos;
	this->m_animation = std::make_unique<AnimationComponent>(m_engine->texture(file.at(mob).at("name")),m_spriteSize, 0.5f);
	/*
	this->m_sprite = m_engine->sprite(file.at(mob).at("sprite"), "Entities");
	this->m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
	*/

	//Create unique_ptrs
	this->m_attributes = std::make_unique<AttributeComponent>();
	this->m_skills = std::make_unique<SkillComponent>();
	this->m_resources = std::make_unique<ResourceComponent>();

	this->m_inventory = std::make_unique<Inventory>(file.at(mob).at("inventory"));

	m_attributes.get()->attribute("Strength", RNG::randInt(file.at(mob).at("attributes").at("Strength").at(0), file.at(mob).at("attributes").at("Strength").at(1)));
	m_attributes.get()->attribute("Dexterity", RNG::randInt(file.at(mob).at("attributes").at("Dexterity").at(0), file.at(mob).at("attributes").at("Dexterity").at(1)));
	m_attributes.get()->attribute("Intelect", RNG::randInt(file.at(mob).at("attributes").at("Intelect").at(0), file.at(mob).at("attributes").at("Intelect").at(1)));
	m_attributes.get()->attribute("Vitality", RNG::randInt(file.at(mob).at("attributes").at("Vitality").at(0), file.at(mob).at("attributes").at("Vitality").at(1)));
	m_attributes.get()->attribute("DR", RNG::randInt(file.at(mob).at("attributes").at("DR").at(0), file.at(mob).at("attributes").at("DR").at(1)));
	m_attributes.get()->attribute("Speed", 90 + attribute("Dexterity"));

	for (auto const& skilllvl : file.at(mob).at("skills").items())
	{
		m_skills.get()->skill(skilllvl.key(), RNG::randInt(skilllvl.value().at(0), skilllvl.value().at(1)));
	}

	m_resources.get()->maxLevel("Health", attribute("Strength") * 3 + attribute("Vitality") * 2);
	m_resources.get()->currentLevel("Health", m_resources.get()->maxLevel("Health"));
	m_resources.get()->maxLevel("Energy", attribute("Vitality") * 10);
	m_resources.get()->currentLevel("Energy", m_resources.get()->maxLevel("Energy"));
}


/**Returns a given attribute's level.*/

/**Returns a given skill's level and, if it was used, gives some XP to it.*/
int Character::skill(sf::String skill, bool skillUsed)
{
	//PENDING: Need to have different XP levels for different activities
	if (skillUsed)
	{
		m_skills.get()->skillUsed(skill, 10);
	}
	return 	m_skills.get()->skill(skill);
}


Item* Character::equippedItem(unsigned int slot)
{
	return m_equippedItems[slot];
}

//Mutators
void Character::equippedItem(unsigned int slot, Item* item)
{
	m_equippedItems[slot] = item;
}

//Function
/**Offsets the entity's postion on the grid.*/
void Character::move(sf::Vector2i offset)
{
	engine()->currentMap()->tile(sf::Vector2i(m_pos.x, m_pos.y))->occupant(nullptr);
	m_pos.x += offset.x;
	m_pos.y += offset.y;
	engine()->currentMap()->tile(sf::Vector2i(m_pos.x, m_pos.y))->occupant(this);
	m_sprite.setPosition((float)m_pos.x * m_spriteSize, (float)m_pos.y * m_spriteSize);
}


/**Updates the entity.*/
void Character::update()
{
	if (m_AI.get())
	{
		m_AI.get()->update(this);
	}
	return;
}

//Combat Functions
/** The character attacks another one.
* Character* target is the Character to be attacked by this one.*/
void Character::attack(Character* target)
{
	int sides;
	int dice;

	dice = (attribute("Dexterity") / 4) + (skill("Melee", true) / 2);
	sides = attribute("Dexterity");

	int hit = 0;
	for (int i = 0; i < dice; i++)
	{
		hit += RNG::randInt(1, sides);
	}
	if (this->m_equippedItems[WEAPON] != nullptr)
	{
		hit += equippedItem(WEAPON)->attribute("Attack");
	}
	int toHit = 0;
	for (int i = 0; i < target->skill("Dodge", true);i++)
	{
		toHit += RNG::randInt(1, 10);
	}



	if (hit > toHit)
	{
		int damage = RNG::randInt(0, attribute("Strength"));
		if (this->m_equippedItems[WEAPON] != nullptr)
		{
			damage += equippedItem(WEAPON)->attribute("Damage");
		}
		damage = target->takeDamage(damage);
		if (damage < 1)
		{
			engine()->gui()->menu("gameInterface")->addMessage(this->name() + " attacks " + target->name() + ", but the attack glances off.",
				engine()->gui()->font("Arial"), Color::Black, Color::Black);
		}
		else
		{
			engine()->gui()->menu("gameInterface")->addMessage(this->name() + " attacks " + target->name() + ", causing " + std::to_string(damage)
				+ " damage!", engine()->gui()->font("Arial"), Color::Red, Color::Red);
			if (target->died())
			{
				engine()->gui()->menu("gameInterface")->addMessage(target->name() + " dies!", engine()->gui()->font("Arial"), Color::DarkRed, Color::DarkRed);
			}
		}
	}
	else
	{
		engine()->gui()->menu("gameInterface")->addMessage(this->name() + " attacks " + target->name() + ", but misses.", engine()->gui()->font("Arial"), Color::Black, Color::Black);
	}
}


/**Processes int damage and returns it after calculating how DR impacts damage*/
int Character::takeDamage(int damage)
{
	damage -= attribute("DR");
	if (damage <= 0)
	{
		damage = 0;
		return damage;
	}
	currentResource("Health", (-1) * damage);
	die();
	return damage;
}

/**Kills a character if their HP gets < 0.*/
void Character::die()
{
	if (currentResource("Health") < 1)
	{
		ai(nullptr);
		this->m_animation.get()->die();
		engine()->currentMap()->tile(pos())->occupant(nullptr);
	}
}

/**Checks if a character's HP is < 0;*/
bool Character::died()
{
	return currentResource("Health") < 1;
}
