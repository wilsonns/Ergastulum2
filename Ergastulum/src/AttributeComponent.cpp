#include "AttributeComponent.h"



Attribute::Attribute(int baseLevel, int currentLevel, int maxLevel, int minLevel)
{
	this->m_currentLevel = currentLevel;
	this->m_baseLevel = baseLevel;
	this->m_maxLevel = maxLevel;
	this->m_minLevel = minLevel;
}

Attribute::Attribute()
{
	this->m_currentLevel = 1;
	this->m_baseLevel = 1;
	this->m_maxLevel = 99;
	this->m_minLevel = 0;
}

AttributeComponent::AttributeComponent()
{

}

AttributeComponent::~AttributeComponent()
{

}


Attribute AttributeComponent::attribute(sf::String name)
{
	return this->m_attributes[name];
}

void AttributeComponent::attribute(sf::String name, int level)
{
	this->m_attributes[name].m_baseLevel = level;
}