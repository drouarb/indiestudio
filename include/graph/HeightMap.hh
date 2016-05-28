#ifndef  HEIGHT_MAP_HH_
# define HEIGHT_MAP_HH_

# define HEIGHT_MAP_SCALE 1.0

# include <string>

namespace			gauntlet
{
  class				HeightMap
  {
  public:
    HeightMap();
    ~HeightMap();

    bool			load(std::string const & filename);
    unsigned char		at(double x, double y);

  private:
    unsigned char		*map;
    int				width;
    int				height;

    int				linelength(std::string const & line);
  };
};

#endif
