#include "FOV.h"

void ShadowCastingFOV::castLight(FOVMap* map, int povX, int povY, int distance, float viewSlopeHigh, float viewSlopeLow, int maxRadius, int octant)
{
    bool lightWalls = true;
    const int xx = matrixTable[octant][0];  //
    const int xy = matrixTable[octant][1];  // Those 4 variables are used to convert the coordinates inside the octant to
    const int yx = matrixTable[octant][2];  //  coordinates in the map grid
    const int yy = matrixTable[octant][3];  //
    const int radiusSquared = maxRadius * maxRadius;

    if (viewSlopeHigh < viewSlopeLow)
    {
        return;//Invalid slope, cancel
    }

    if (distance > maxRadius)
    {
        return;//We've reached the limit of the FOV, cancel
    }

    bool previousCellBlocked = false;
    for (int angle = distance; angle >= 0; --angle)
    {
        const float cellSlopeHigh = (angle + .5f) / (distance - .5f);
        const float cellSlopeLow = (angle - .5f) / (distance + .5f);
        const float previousCellSlopeLow = (angle + .5f) / (distance + .5f);
        const int mapX = povX + angle * xx + distance * xy;
        const int mapY = povY + angle * yx + distance * yy;
        if (cellSlopeLow > viewSlopeHigh)
        {
            continue;//tile is not in view yet
        }
        else if (cellSlopeHigh < viewSlopeLow)
        {
            break;//tile will no longer be in view
        }
        
        const int mapIndex = mapX + mapY * map->m_width;
        
        if (angle * angle + distance * distance <= radiusSquared && (lightWalls || !map->cells[mapIndex].get()->m_opaque))
        {
            map->cells[mapIndex].get()->m_isInFov = true;
        }
        if (previousCellBlocked && !map->cells[mapIndex].get()->isWall()) // wall -> floor
        {
            viewSlopeHigh = previousCellSlopeLow; //Reduce the view size
        }
        if (!previousCellBlocked && map->cells[mapIndex].get()->isWall()) //floor -> wall
        {
            castLight(map, povX, povY, distance + 1, viewSlopeHigh, cellSlopeHigh, maxRadius, octant);
        }
        previousCellBlocked = map->cells[mapIndex].get()->m_opaque;
    }
    if (!previousCellBlocked)
    {
        castLight(map, povX, povY, distance + 1, viewSlopeHigh, viewSlopeLow, maxRadius, octant);
    }
}

void ShadowCastingFOV::computeFov(FOVMap* map,Map *gameMap, int povX, int povY, int maxRadius)
{
    for (int j = 0; j < map->m_height;j++)
    {
        for (int i = 0; i < map->m_width;i++)
        {
            map->cells[i + j * map->m_width].get()->m_isInFov = false;
            map->cells[i+j*map->m_width].get()->m_opaque = gameMap->tile(sf::Vector2i(i, j))->opaque();
        }
    }
    for (int octant = 0; octant < 8;++octant)
    {
        castLight(map, povX, povY, 1, 1.0, 0.0, maxRadius, octant);
    }
    map->cells[povX + povY * (map->m_width)].get()->m_isInFov = true;
    for (int j = 0; j < map->m_height;j++)
    {
        for (int i = 0; i < map->m_width;i++)
        {
            gameMap->tile(sf::Vector2i(i, j))->visible(map->cells[i + j * map->m_width].get()->m_isInFov);
            if (map->cells[i + j * map->m_width].get()->m_isInFov)
            {
                gameMap->tile(sf::Vector2i(i, j))->explored(true);
            }
        }
    }
}