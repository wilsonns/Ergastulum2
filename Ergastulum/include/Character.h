#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

class AttributeComponent;
class SkillComponent;
class Item;
class Inventory;

class Character : public Entity
{
public:
	enum ItemSlot {
		HEAD,
		TORSO,
		WEAPON
	};
	//Constructors & Destructors
	Character(sf::String name, sf::Vector2i pos, sf::Texture* texture);
	Character(const Character& copy);
	Character();
	Character(const json& file, sf::String mob, sf::Vector2i pos);
	~Character();



	//Accessors
	int skill(sf::String skill, bool skillUsed = false);
	Item* equippedItem(unsigned int slot);
	//Mutators
	void equippedItem(unsigned int slot, Item* item);

	//Combat Functions
	void attack(Character* target);
	int takeDamage(int damage);
	void die();
	bool died();

	//Functions
	void update();
	void move(sf::Vector2i offset);


private:
	std::unique_ptr<SkillComponent> m_skills;
	std::map<unsigned int, Item*> m_equippedItems;

protected:
};




#endif