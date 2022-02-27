#include "Stats.h"



/////////
//STATS//
/////////
//Constructors & Destructors
Stats::Stats(int level)
{
	m_level = level;
}

Stats::Stats()
{

}

Stats::~Stats()
{

}

//Accessors
int Stats::level()
{
	return m_level;
}

//Mutators
void Stats::levelUp()
{
	m_level += 1;
}

//Functions


/////////
//SKILL//
/////////

//Constructors & Destructors
Skill::Skill(int level)
{
	m_level = level;
	m_experienceToNext = pow((100 * m_level), 1.5);
}

Skill::Skill()
{
	m_level = 1;
	m_experienceToNext = pow((100 * m_level), 1.5);
}

Skill::~Skill()
{

}

//Accessors
int Skill::level()
{
	return m_level;
}

//Mutators
void Skill::levelUp()
{
	m_level += 1;
}

//Functions
void Skill::sumExperience(int experience)
{
	m_experience += experience;
	if (m_experience >= m_experienceToNext)
	{
		levelUp();
		int carryOver = m_experienceToNext - m_experience;
		m_experienceToNext = pow((100 * m_level), 1.5);
		m_experience = carryOver;

	}
}


/////////////
//ATTRIBUTE//
/////////////

//Constructors & Destructors
Attribute::Attribute(int level)
{
	m_level = level;
}

Attribute::Attribute()
{
	m_level = 0;
}

Attribute::~Attribute()
{

}

//Accessors
int Attribute::level()
{
	return m_level;
}

//Mutators

//Functions
////////////
//RESOURCE//
////////////

//Constructors & Destructors
Resource::Resource(int level)
{
	m_maxLevel = level;
	m_level = level;
}

Resource::Resource()
{
	m_maxLevel = 0;
	m_level = m_maxLevel;

}

Resource::~Resource()
{

}

//Accessors
int Resource::currentLevel()
{
	return m_level;
}

int Resource::maxLevel()
{
	return m_maxLevel;
}

//Mutators
void Resource::currentLevel(int offset)
{
	m_level += offset;
	if (m_level > m_maxLevel)
	{
		m_level = m_maxLevel;
	}
	if (m_level < 0)
	{
		m_level = 0;
	}
}

void Resource::maxLevel(int level)
{
	m_maxLevel = level;
	if (m_level > m_maxLevel)
	{
		m_level = m_maxLevel;
	}
}

//Functions

//////////////////
//SKILLCOMPONENT//
//////////////////
//Constructors & Destructors
SkillComponent::SkillComponent(sf::String, int level)
{

}

SkillComponent::SkillComponent()
{

}

SkillComponent::~SkillComponent()
{

}

//Accessors
int SkillComponent::skill(sf::String skill)
{
	return m_skills[skill].level();
}

//Mutators
void SkillComponent::skill(sf::String skill, int level)
{
	if (level > 0)
	{
		for (int i = 0; i < level; i++)
		{
			m_skills[skill].levelUp();
		}
	}
}

//Functions
bool SkillComponent::skillUsed(sf::String skill, int experience)
{
	m_skills[skill].sumExperience(experience);
	return true;
}



//////////////////////
//ATTRIBUTECOMPONENT//
//////////////////////
//Constructors & Destructors
AttributeComponent::AttributeComponent()
{

}

AttributeComponent::~AttributeComponent()
{

}

//Accessors
int AttributeComponent::attribute(sf::String attribute)
{
	return m_attributes[attribute].level();
}

//Mutators
void AttributeComponent::attribute(sf::String attribute, int level)
{
	if (level > 0)
	{
		for (int i = 0; i < level; i++)
		{
			m_attributes[attribute].levelUp();
		}
	}
}

//Functions



/////////////////////
//RESOURCECOMPONENT//
/////////////////////
//Constructors & Destructors
ResourceComponent::ResourceComponent()
{

}

ResourceComponent::~ResourceComponent()
{

}

//Accessors
int ResourceComponent::currentLevel(sf::String resource)
{
	return m_resources[resource].currentLevel();
}

int ResourceComponent::maxLevel(sf::String resource)
{
	return m_resources[resource].maxLevel();
}

//Mutators
void ResourceComponent::currentLevel(sf::String resource, int offset)
{
	m_resources[resource].currentLevel(offset);
}

void ResourceComponent::maxLevel(sf::String resource, int level)
{
	m_resources[resource].maxLevel(level);
}

//Functions