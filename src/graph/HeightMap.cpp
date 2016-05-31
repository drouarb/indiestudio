#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include "HeightMap.hh"

gauntlet::HeightMap::HeightMap()
{
  map = NULL;
}

gauntlet::HeightMap::~HeightMap()
{
  if (map)
    delete [] map;
}

bool
gauntlet::HeightMap::load(std::string const & filename)
{
  std::ifstream is(filename);
  if (!is)
    return (false);

  std::string tmp;
  if (!getline(is, tmp))
    return (false);
  is >> tmp;
  height = stoi(tmp);
  is >> tmp;
  width = stoi(tmp);
  is >> tmp;

  map = new int [width * height];
  for (int i = 0; i < width * height && !is.eof(); ++i)
    {
      is >> tmp;
      map[i] = stoi(tmp);
    }

  return (true);
}

int
gauntlet::HeightMap::at(double x, double y)
{
  if (!map)
    throw (std::runtime_error("HeightMap not loaded"));

  int hm_x = (int)floor(x / HEIGHT_MAP_SCALE);
  int hm_y = (int)floor(y / HEIGHT_MAP_SCALE);
  if (hm_x >= width || hm_x < 0 || hm_y >= height || hm_y < 0)
    throw (std::invalid_argument("HeightMap coordinates"));
  return (map[hm_x * height + hm_y]);
}

std::pair<double, double>
gauntlet::HeightMap::getSize() const
{
  if (!map)
    throw (std::runtime_error("HeightMap not loaded"));
  return (std::pair<double, double>((double)width * HEIGHT_MAP_SCALE,
				    (double)height * HEIGHT_MAP_SCALE));
}

bool
gauntlet::HeightMap::isLoaded() const
{
  return (map != NULL);
}
