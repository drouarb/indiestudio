#ifndef  HEIGHT_MAP_HH_
# define HEIGHT_MAP_HH_

# include <string>

# define SCALE_MAP 90
# define HEIGHT_MAP_SCALE (SCALE_MAP / 4)
# define HEIGHT_SCALE (SCALE_MAP / 20)

namespace			gauntlet
{
  class				HeightMap
  {
  public:
    HeightMap();
    ~HeightMap();

    bool			load(std::string const & filename);
    int				at(double x, double y);
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
