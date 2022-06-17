#include "Pathfinding.h"

std::vector<std::unique_ptr<Node>> Pathfinding::m_nodes;
int Pathfinding::m_width = 0;
std::list<Node*> Pathfinding::m_open;
std::list<Node*> Pathfinding::m_closed;
Map* Pathfinding::m_map;

//Constructors & Destructors
Pathfinding::Pathfinding()
{
}

//Functions
void Pathfinding::initPathfinding(Map* map)
{
	m_map = map;
	m_width = map->width();
	m_nodes.clear();
	for (int y = 0; y < map->height();y++)
	{
		for (int x = 0; x < map->width();x++)
		{
			m_nodes.push_back(std::make_unique<Node>(sf::Vector2i(x, y)));
		}
	}
	Node* current;
	for (int y = 0; y < map->height();y++)
	{
		for (int x = 0; x < map->width();x++)
		{
			current = nodeAt(sf::Vector2i(x, y));
			//ADJACENTS
			if (y > 0)
			{
				current->m_neighbours.push_back(nodeAt(sf::Vector2i(x, y - 1)));
			}
			if (y < map->height()-1)
			{
				current->m_neighbours.push_back(nodeAt(sf::Vector2i(x, y + 1)));
			}
			if (x > 0)
			{
				current->m_neighbours.push_back(nodeAt(sf::Vector2i(x-1, y)));
			}
			if (x < map->width() - 1)
			{
				current->m_neighbours.push_back(nodeAt(sf::Vector2i(x +1, y)));
			}
			//DIAGONALS

		}
	}
}

Node* Pathfinding::nodeAt(sf::Vector2i pos)
{
	return m_nodes[pos.x + pos.y * m_width].get();
}

bool Pathfinding::compareF(Node l, Node r)
{
	return l.m_f < r.m_f;
}

bool Pathfinding::isInList(std::list<Node*>& list, Node* node)
{

	bool found = (std::find(list.begin(), list.end(), node) != list.end());
	return found;
}


std::vector<Node*> Pathfinding::findPath(sf::Vector2i start, sf::Vector2i goal)
{
	/**Pathfinding LOOP
	* 1 - resets all nodes , clean open and closed lists
	* 2 - insert the start node in the open list and sets it as the current node
	* 3 - initialize the loop: process the current node, removing it from the open list and
	* adding it to the closed list. All of its neighbours are inserted into open list.
	* 4 - sort the open list so the lowest F valu is at the beggining of the list.
	* 5 - Repeat step 3 until the open list is empty(no path was found) OR until the current node equals goal node
	* 6 - If the goal is found, trace back the path from the goal to the start using the parent node
	* 7 - return a inverse vector as the path
	*/

	//1
	for (std::vector<std::unique_ptr<Node>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		(*it)->m_f = 0;
		(*it)->m_g = 0;
		(*it)->m_h = 0;
		(*it)->m_parent = nullptr;

	}

	m_open.clear();
	m_closed.clear();

	//2
	Node* begin = nodeAt(start);
	Node* current = nodeAt(start);

	m_open.push_back(current);

	//3
	Node* target = nodeAt(goal);

	auto* targetEntity = m_map->tile(target->m_pos)->occupant();

	while (!m_open.empty())
	{
		m_open.sort([](const Node* lhs, const Node* rhs) {return lhs->m_f < rhs->m_f;});
		current = m_open.front();
		m_open.pop_front();
		m_closed.push_back(current);

		for (auto& neighbour : current->m_neighbours)
		{
			if ((m_map->isWalkable(m_map->tile(sf::Vector2i(neighbour->m_pos.x, neighbour->m_pos.y)))
				|| m_map->tile(sf::Vector2i(neighbour->m_pos.x, neighbour->m_pos.y))->occupant() == targetEntity) &&
				!isInList(m_open, neighbour) && !isInList(m_closed, neighbour))
			{
				neighbour->m_parent = current;
				neighbour->m_g = calculateG(neighbour);
				neighbour->m_h = calculateH(neighbour, target);
				neighbour->m_f = calculateF(neighbour);
				m_open.push_back(neighbour);
			}
			else if ((m_map->isWalkable(m_map->tile(sf::Vector2i(neighbour->m_pos.x, neighbour->m_pos.y)))
				|| m_map->tile(sf::Vector2i(neighbour->m_pos.x, neighbour->m_pos.y))->occupant() == targetEntity) &&
				isInList(m_open, neighbour) && !isInList(m_closed, neighbour))
			{
				if (neighbour->m_parent->m_g > calculateG(current))
				{
					neighbour->m_g = calculateG(neighbour);
					neighbour->m_f = calculateF(neighbour);
					neighbour->m_parent = current;
				}
			}
		}
		if (m_open.empty())
		{
			break;
		}
		if (current == target)
		{
			std::vector<Node*> path;
			for (int i = 0; current != begin; i++)
			{
				path.push_back(current);
				current = current->m_parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

	}
	std::vector<Node*> path;
	return path;
}
