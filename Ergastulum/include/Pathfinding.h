#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <list>

#include "SFML/System.hpp"
#include "Map.h"

class Map;

struct Node
{
	Node(sf::Vector2i pos)
	{
		m_pos = pos;
		m_f = 0;
		m_g = 0;
		m_h = 0;
		m_parent = nullptr;
	}
	sf::Vector2i m_pos;/**Position of the node*/
	int m_f;
	int m_g;
	int m_h;
	Node* m_parent;
	bool operator ==(const Node& other)
	{
		return m_pos.x == other.m_pos.x && m_pos.x == other.m_pos.y;
	}

	bool operator !=(const Node& other)
	{
		return m_pos.x != other.m_pos.x || m_pos.x != other.m_pos.y;
	}

	Node operator =(const Node& other)
	{
		m_pos.x = other.m_pos.x;
		m_pos.y = other.m_pos.y;
	}

	bool operator <(const Node& other)
	{
		return m_f < other.m_f;
	}
	
	std::vector<Node*> m_neighbours;

};

class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();


	
	//Functions
	static void initPathfinding(Map* map);
	static Node* nodeAt(sf::Vector2i pos);
	static bool compareF(Node l, Node r);
	static bool isInList(std::list<Node*>& list, Node* node);
	static std::vector<Node*> findPath(sf::Vector2i start, sf::Vector2i goal);
	static inline int calculateF(Node* node)
	{
		return node->m_f = (node->m_g + node->m_h);
	}
	static inline int calculateG(Node* node)
	{
		return node->m_g = node->m_parent->m_g + 10;
	}
	static inline int calculateH(Node* current, Node* goal)
	{
		int dx = current->m_pos.x - goal->m_pos.x;
		int dy = current->m_pos.y - goal->m_pos.y;
		float distance = sqrtf((float)(dx * dx + dy * dy));
		return (int)(distance * 10);
	}

	//Assets
	static std::vector<std::unique_ptr<Node>> m_nodes;
	static std::list<Node*> m_open;
	static std::list<Node*> m_closed;
	static int m_width;
	static Map* m_map;
};

#endif