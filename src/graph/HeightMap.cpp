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
  width = stoi(tmp);
  is >> tmp;
  height = stoi(tmp);
  is >> tmp;

  if (map)
    {
      delete [] map;
      map = NULL;
    }

  height = 0;
  width = -1;
  std::string content = "";
  while (getline(is, line))
    {
      if (line != "")
	{
	  if (width == -1)
	    width = linelength(line);
	  else if (linelength(line) != width)
	    return (false);
	  content += line + "\n";
	  height++;
	}
    }
  map = new unsigned char [height * width];
  int i = 0;
  std::stringstream ss;
  ss.str(content);
  std::string c;
  while (!ss.eof())
  map = new unsigned char [width * height];
  for (int i = 0; i < width * height && !is.eof(); ++i)
    {
      is >> tmp;
      map[i] = stoi(tmp);
    }

  return (true);
}

unsigned char
gauntlet::HeightMap::at(double x, double y)
{
  if (!map)
    throw (std::runtime_error("HeightMap not loaded"));

  int hm_x = (int)floor(x / HEIGHT_MAP_SCALE);
  int hm_y = (int)floor(y / HEIGHT_MAP_SCALE);
  if (hm_x >= width || hm_x < 0 || hm_y >= height || hm_y < 0)
    throw (std::invalid_argument("HeightMap coordinates"));
  return (map[hm_y * width + hm_x]);
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
