#include <iostream>
#include <stdexcept>
#include <math.h>
#include "world/PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(const std::string &filePath)
{
    if (!heightmap.load(filePath))
        {
            throw (std::runtime_error("Wrong height map"));
        }
    sizeX = heightmap.getSize().first;
    sizeY = heightmap.getSize().second;
}

PhysicCollideLayer::~PhysicCollideLayer()
{ }

std::pair<double, double>    PhysicCollideLayer::getSize() const
{
    return (std::make_pair(sizeX, sizeY));
}

bool PhysicCollideLayer::isWall(const std::pair<double, double> &oldPos,
                                const std::pair<double, double> &wantedPos)
{
    return (ABS(heightmap.at(heightmap.getSize().first - 1 - oldPos.first,
                             heightmap.getSize().second - 1 - oldPos.second) -
                heightmap.at(heightmap.getSize().first - 1 - wantedPos.first,
                             heightmap.getSize().second - 1 - wantedPos.second))
            >= WALL_MIN_HEIGHT);
}

bool    PhysicCollideLayer::checkCoordSizeCanPass(const std::pair<double, double> &oldPos,
                                                  const std::pair<double, double> &wantedPos_real,
                                                  const std::pair<double, double> &size)
{
    if (oldPos.first == wantedPos_real.first && oldPos.second == wantedPos_real.second)
        return (true);

    if (ABS(heightmap.at(heightmap.getSize().first - 1 - oldPos.first,
                         heightmap.getSize().second - 1 - oldPos.second) -
            heightmap.at(heightmap.getSize().first - 1 - wantedPos_real.first,
                         heightmap.getSize().second - 1 - wantedPos_real.second))
            / sqrt(pow(oldPos.first - wantedPos_real.first, 2) + pow(oldPos.second - wantedPos_real.second, 2))
            > MOVEMENT_MAX_HEIGHT)
        {
            return (false);
        }

    std::pair<double, double> start;
    std::pair<double, double> end;

    std::pair<double, double> wantedPos = wantedPos_real;

    //for size
    double extra_points = sqrt(pow(size.first, 2) + pow(size.second, 2)) / HEIGHT_MAP_SCALE;

    if (ABS(oldPos.first - wantedPos.first) > ABS(oldPos.second - wantedPos.second))
        {
            inc.first = (oldPos.first < wantedPos.first ? 1 : -1);
            inc.second = ABS((oldPos.second - wantedPos.second) /
                             (oldPos.first - wantedPos.first));
            if (oldPos.second > wantedPos.second)
                inc.second *= -1;
            inc.first *= HEIGHT_MAP_SCALE;
            inc.second *= HEIGHT_MAP_SCALE;

            nb_points = (int) (floor(ABS((oldPos.first - wantedPos.first) / inc.first) + extra_points)) + 1;
        }
    else
        {
            inc.second = (oldPos.second < wantedPos.second ? 1 : -1);
            inc.first = ABS((oldPos.first - wantedPos.first) /
                            (oldPos.second - wantedPos.second));
            if (oldPos.first > wantedPos.first)
                inc.first *= -1;
            inc.first *= HEIGHT_MAP_SCALE;
            inc.second *= HEIGHT_MAP_SCALE;

            nb_points = (int) (floor(ABS((oldPos.second - wantedPos.second) / inc.second) + extra_points)) + 1;
        }

    start.second = oldPos.second + size.second / 2;
    end.second = oldPos.second - size.second / 2;
    if (oldPos.second < wantedPos.second)
        {
            if (oldPos.first < wantedPos.first)
                {
                    start.first = oldPos.first - size.first / 2;
                    end.first = oldPos.first + size.first / 2;
                }
            else
                {
                    start.first = oldPos.first + size.first / 2;
                    end.first = oldPos.first - size.first / 2;
                }
        }
    else
        {
            if (oldPos.first < wantedPos.first)
                {
                    start.first = oldPos.first + size.first / 2;
                    end.first = oldPos.first - size.first / 2;
                }
            else
                {
                    start.first = oldPos.first - size.first / 2;
                    end.first = oldPos.first + size.first / 2;
                }
        }
    return (doOnLine(start, end, &PhysicCollideLayer::checkLine));
}

bool PhysicCollideLayer::doOnLine(std::pair<double, double> start,
                                  std::pair<double, double> end,
                                  bool (PhysicCollideLayer::*func)
                                          (std::pair<double, double>))
{
    double inc_y;
    double inc_x;

    if (ABS(start.first - end.first) > ABS(start.second - end.second))
        {
            inc_y = ABS((end.second - start.second) / (end.first - start.first));
            if (start.second > end.second)
                inc_y *= -1;
            inc_x = (start.first < end.first ? 1 : -1);
            inc_x *= HEIGHT_MAP_SCALE;
            inc_y *= HEIGHT_MAP_SCALE;

            if (start.first < end.first)
                while (start.first <= end.first)
                    {
                        if (!(this->*func)(start))
                            return (false);
                        start.second += inc_y;
                        start.first += inc_x;
                    }
            else
                while (start.first >= end.first)
                    {
                        if (!(this->*func)(start))
                            return (false);
                        start.second += inc_y;
                        start.first += inc_x;
                    }
        }
    else
        {
            inc_y = (start.second < end.second ? 1 : -1);
            inc_x = ABS((end.first - start.first) / (end.second - start.second));
            if (start.first > end.first)
                inc_x *= -1;
            inc_x *= HEIGHT_MAP_SCALE;
            inc_y *= HEIGHT_MAP_SCALE;

            if (start.second < end.second)
                while (start.second <= end.second)
                    {
                        if (!(this->*func)(start))
                            return (false);
                        start.second += inc_y;
                        start.first += inc_x;
                    }
            else
                while (start.second >= end.second)
                    {
                        if (!(this->*func)(start))
                            return (false);
                        start.second += inc_y;
                        start.first += inc_x;
                    }
        }
    return (true);
}

bool PhysicCollideLayer::checkLine(std::pair<double, double> point)
{
    lastPoint = point;
    std::pair<double, double> dest;
    dest.first = point.first + inc.first * nb_points;
    dest.second = point.second + inc.second * nb_points;

    if (point.first < 0 || point.first >= sizeX ||
        point.second < 0 || point.second >= sizeY ||
        dest.first < 0 || dest.first >= sizeX ||
        dest.second < 0 || dest.second >= sizeY)
        return (false);

    return (doOnLine(point, dest, &PhysicCollideLayer::checkPoint));
}

bool PhysicCollideLayer::checkPoint(std::pair<double, double> point)
{
    if (isWall(lastPoint, point))
        return (false);
    lastPoint = point;
    return (true);
}

const unsigned char *PhysicCollideLayer::getLayer() const
{
    return (layer);
}
