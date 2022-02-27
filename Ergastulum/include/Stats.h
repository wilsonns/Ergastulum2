#ifndef STATS_H
#define STATS_H

#include <random>
#include <iostream>
#include <map>
#include <SFML/System.hpp>



class Stats
{
public:
	//Constructors & Destructors
	Stats(int level);
	Stats();
	~Stats();
	//Accessors
	virtual int level();

	//Mutators
	virtual void levelUp();

	//Functions


protected:
	int m_level;
};

class Skill : public Stats
{
public:
	//Constructors & Destructors
	Skill(int level);
	Skill();
	~Skill();

	//Accessors
	int level();

	//Mutators
	void levelUp();

	//Functions
	void sumExperience(int experience);
	
private:
	int m_experience;
	int m_experienceToNext;
};

class Attribute: public Stats
{
public:
	//Constructors & Destructors
	Attribute(int level);
	Attribute();
	~Attribute();
	
	//Accessors
	int level();

	//Mutators

	//Functions

};

class Resource :public Stats
{
public:
	//Constructors & Destructors
	Resource(int level);
	Resource();
	~Resource();
	//Accessors
	int currentLevel();
	int maxLevel();
	//Mutators
	void currentLevel(int offset);
	void maxLevel(int level);
	
	//Functions

private:
	int m_maxLevel;
};

class SkillComponent
{
public:
	//Constructors & Destructors
	SkillComponent(sf::String, int level);
	SkillComponent();
	~SkillComponent();

	//Accessors
	int skill(sf::String skill);
	
	//Mutators
	void skill(sf::String skill, int level);

	//Functions
	bool skillUsed(sf::String skill, int experience);

private:
	std::map<sf::String, Skill> m_skills;

};

class AttributeComponent
{
public:
	//Constructors & Destructors
	AttributeComponent();
	~AttributeComponent();
	
	
	//Accessors
	int attribute(sf::String attribute);

	//Mutators
	void attribute(sf::String attribute, int level);
	
	//Functions

	

private:
	std::map<sf::String, Attribute> m_attributes;
};

class ResourceComponent
{	
public:
	//Constructors & Destructors
	ResourceComponent();
	~ResourceComponent();

	//Accessors
	int currentLevel(sf::String resource);
	int maxLevel(sf::String resource);

	//Mutators
	void currentLevel(sf::String resource,int offset);
	void maxLevel(sf::String resource, int level);

	//Functions

private:
	std::map<sf::String, Resource> m_resources;
};
#endif