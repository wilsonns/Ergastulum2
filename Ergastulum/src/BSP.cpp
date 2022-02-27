#include "BSP.h"

Map* BSP::m_map;



BSPListener::BSPListener(Map *map)
{
	m_map = map;
	m_roomNum = 0;
}



bool BSPListener::visitNode(BSP* node)
{
	if (node->isLeaf())
	{
		int x, y, w, h;
		w = RNG::randInt(2, (node->m_w - 2));
		h = RNG::randInt(2, (node->m_h - 2));
		x = RNG::randInt(node->m_x + 1, node->m_x + node->m_w - w - 1);
		y = RNG::randInt(node->m_y + 1, node->m_y + node->m_h - h - 1);
		m_map->createRoom(m_roomNum == 0,x,y,x+w-1,y+h-1);
		if (m_roomNum != 0)
		{
			m_map->dig(m_lastX, m_lastY,x + w / 2, m_lastY);
			m_map->dig(x + w / 2, m_lastY, x + w / 2, y + h / 2);
		}
		m_lastX = x + w / 2;
		m_lastY = y + h / 2;
		std::cout << "Room:" << m_roomNum << "/x/w/y/h:" << x << "," << x+w-1<< "," << y<< "," << y+h-1 << std::endl;
		std::cout << "Leaf:" << m_roomNum << "/x/w/y/h:" << node->m_x << "," << node->m_w << "," << node->m_y << "," << node->m_h << std::endl;
		m_roomNum++;
		
	}
	return true;
}

//Constructors & Destructors
BSP::BSP(int x, int y, int width, int height, Map* map)
{
	m_x = x;
	m_w = width;
	m_y = y;
	m_h = height;
	m_map = map;
	m_level = 0;
}

BSP::BSP(BSP* parent, bool left)
{
	if (parent->m_horizontal)
	{
		m_x = parent->m_x;
		m_w = parent->m_w;
		m_y = left?parent->m_y:parent->m_position;
		m_h = left?parent->m_position - m_y:
			parent->m_y + parent->m_h - parent->m_position;
	}
	else
	{
		m_y = parent->m_y;
		m_h = parent->m_h;
		m_x = left?parent->m_x : parent->m_position;
		m_w = left?parent->m_position - m_x:
			parent->m_x + parent->m_w - parent->m_position;
	}
	m_level = parent->m_level + 1;
}

BSP::~BSP()
{
	this->removeChild();
}

//Accessors

//Mutators


//Functions
/**Checks if a given node is a Leaf in the tree.*/
void BSP::addChild()
{
	this->m_leftChild = std::make_unique<BSP>(this,true);
	this->m_rightChild = std::make_unique<BSP>(this,false);
}

void BSP::removeChild()
{
	BSP* node = m_leftChild.get();
	BSP* next = m_rightChild.get();
	while(node != nullptr)
	{
		node->removeChild();
		this->m_rightChild.release();
		this->m_leftChild.release();
		node = next;
	}
}

bool BSP::isLeaf()
{
	return m_leftChild.get() == nullptr && m_rightChild.get() == nullptr;
 }

void BSP::split(bool horizontal, int position)
{
	this->m_horizontal = horizontal;
	this->m_position = position;
	this->addChild();
}

void BSP::recursiveSplit(int rooms, int minHorizontalSize, int minVerticalSize,
	float maxHorizontalRatio, float maxVerticalRatio)
{
	if (rooms == 0 || (this->m_w < 2 * minHorizontalSize 
		&& this->m_h < 2 * minVerticalSize))
	{
		return;
	}
	bool horizontal;
	if (m_h < 2 * minVerticalSize 
		|| m_w > m_h * maxHorizontalRatio)
	{
		horizontal = false;
	}
	else if (m_w < 2 * minHorizontalSize 
		|| m_h > m_w * maxVerticalRatio)
	{
		horizontal = true;
	}
	else
	{
		
		horizontal = RNG::randInt(0, 1) == 0;
	}

	int splitPosition;
	if (horizontal)
	{
		splitPosition =	RNG::randInt((m_y + minVerticalSize), (m_y + m_h - minVerticalSize));
	}
	else
	{
		splitPosition = RNG::randInt((m_x + minHorizontalSize), (m_x + m_w - minHorizontalSize));
	}
	split(horizontal, splitPosition);
	m_leftChild.get()->recursiveSplit(rooms-1, minHorizontalSize, minVerticalSize, maxHorizontalRatio, maxVerticalRatio);
	m_rightChild.get()->recursiveSplit(rooms-1, minHorizontalSize, minVerticalSize, maxHorizontalRatio, maxVerticalRatio);
}

bool BSP::traverseInOrder(BSPListener* listener)
{
	if (m_leftChild && !m_leftChild->traverseInOrder(listener))
	{
		return false;
	}
	if (!listener->visitNode(this))
	{
		return false;
	}
	if (m_rightChild && !m_rightChild->traverseInOrder(listener))
	{
		return false;
	}
	return true;
}

