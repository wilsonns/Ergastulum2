#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <random>
#include <iostream>
#include <map>
#include <SFML/System.hpp>

#include "Entity.h"

struct Attribute
{
	Attribute(int baseLevel, int currentLevel, int maxLevel = 99, int minLevel= 0);
	Attribute();
	Attribute operator++()
	{
		this->m_baseLevel++;
		return *this;
	}
	int m_currentLevel;
	int m_baseLevel;
	int m_maxLevel;
	int m_minLevel;
};

class AttributeComponent
{
public:
	AttributeComponent();
	~AttributeComponent();
	
	Attribute attribute(sf::String name);
	void attribute(sf::String name, int level);


private:
	std::map<sf::String, Attribute> m_attributes;
};

#endif