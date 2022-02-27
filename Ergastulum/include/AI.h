#ifndef AI_H
#define AI_H

#include "SFML/System.hpp"

#include "Pathfinding.h"
#include "Engine.h"

class Engine;
class Entity;
struct Node;

class AI
{
public:
	virtual void update(Entity *owner)=0; 
	virtual void engine(Engine* engine)=0;
protected:
	static Engine* m_engine;
};


class PlayerAI : public AI
{
public:	
	PlayerAI();
	PlayerAI(PlayerAI& copy);
	void update(Entity* owner);
	void engine(Engine* engine);
private:
};

class DummyAI : public AI
{
public:
	DummyAI();
	DummyAI(DummyAI& copy);
	void update(Entity* owner);
	void engine(Engine* engine);
	std::vector<Node*> path;
};

#endif