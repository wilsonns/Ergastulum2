#ifndef BSP_H
#define BSP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "RNG.h"
#include "Map.h"

class Map;
class BSP;


struct BSPListener
{
public:
	BSPListener(Map *map);
	bool visitNode(BSP* node);
private:
	Map* m_map;
	int m_roomNum;
	int m_lastX, m_lastY;
};

class BSP
{
public:
	//Constructors & Destructors
	BSP(int x, int y, int width, int height, Map* map);
	BSP(BSP* parent, bool left = false);
	~BSP();

	//Accessors
	

	//Mutators


	//Functions
	void addChild();
	void removeChild();
	bool isLeaf();
	void split(bool horizontal, int position);
	void recursiveSplit(int rooms, int minHorizontalSize, int minVerticalSize,
		float maxHorizontalRatio, float maxVerticalRatio);
	bool traverseInOrder(BSPListener* listener);

protected:
	//Resources
	friend struct BSPListener;

	static Map* m_map;
	int m_x, m_y, m_w, m_h;
	std::unique_ptr<BSP> m_parent;
	std::unique_ptr<BSP> m_leftChild;
	std::unique_ptr<BSP> m_rightChild;
	int m_position;
	int m_level;
	bool m_horizontal;

};

#endif
