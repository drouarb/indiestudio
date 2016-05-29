#ifndef  HEIGHT_MAP_HH_
# define HEIGHT_MAP_HH_

# include <string>

# define SCALE_MAP 90
# define HEIGHT_MAP_SCALE (40.0 * SCALE_MAP)

namespace			gauntlet
{
  class				HeightMap
  {
  public:
    HeightMap();
    ~HeightMap();

    bool			load(std::string const & filename);
    unsigned char		at(double x, double y);
    std::pair<double, double>	getSize() const;
    bool			isLoaded() const;

  private:
    unsigned char		*map;
    int				width;
    int				height;

    int				linelength(std::string const & line);
  };
};

#endif
