#ifndef FOV_H
#define FOV_H	


#include <vector>
#include <tuple>
#include <memory>
#include <iostream>

#include "Map.h"

class Map;

struct Cell
{

    int m_x, m_y;
    bool m_opaque = false;
    bool m_isInFov = false;

    Cell(int x, int y)
    {
        this->m_x = x;
        this->m_y = x;
    }
    bool isWall()
    {
        return m_opaque ? true : false;
    }
    bool isFloor()
    {
        return m_opaque ? false : true;
    }
    void reveal()
    {
        m_isInFov = true;
    }
};

struct FOVMap
{
    std::vector<std::unique_ptr<Cell>> cells;
    int m_height, m_width;
    FOVMap(int width, int height)
    {
        m_height = height;
        m_width = width;
        for (int y = 0; y < height;y++)
        {
            for (int x = 0;x < width;x++)
            {
                cells.push_back(std::make_unique<Cell>(x, y));
            }
        }
    }
};

static const int matrixTable[8][4] = {
    { 1,  0,  0,  1},
    { 0,  1,  1,  0},
    { 0, -1,  1,  0},
    {-1,  0,  0,  1},
    {-1,  0,  0, -1},
    { 0, -1, -1,  0},
    { 0,  1, -1,  0},
    { 1,  0,  0, -1},
};



class ShadowCastingFOV
{
public:
    static void castLight(FOVMap* map, int povX, int povY, int distance, float viewSlopeHigh, float viewSlopeLow, int maxRadius, int octant);
    static void computeFov(FOVMap* map, Map* gameMap, int povX, int povY, int maxRadius);
private:

};


#endif