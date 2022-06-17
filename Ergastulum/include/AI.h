#ifndef AI_H
#define AI_H

#include "SFML/System.hpp"

#include "Pathfinding.h"
#include "Engine.h"

class Engine;
class Character;
struct Node;
class Item;
class InputHandler;

class AI
{
public:
	virtual void update(Character *owner)=0; 
	virtual void engine(Engine* engine)=0;
protected:
	static Engine* m_engine;
};


class PlayerAI : public AI
{
public:	
	PlayerAI();
	PlayerAI(PlayerAI& copy);
	void update(Character* owner);
	void engine(Engine* engine);

private:
};

class DummyAI : public AI
{
public:
	DummyAI();
	DummyAI(DummyAI& copy);
	void update(Character* owner);
	void engine(Engine* engine);
	std::vector<Node*> path;
};

#endif