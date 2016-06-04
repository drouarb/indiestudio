//
// Created by greg on 04/06/16.
//

#ifndef GAUNTLET_FILES_HH
#define GAUNTLET_FILES_HH

#include <string>
#include <map>

namespace gauntlet
{

  class Files
  {
    std::map<std::string, std::string> stringList;

   public:
    void addFiles(const std::string &filename, const std::string &content);
    const std::string &getFile(const std::string &filename) const;
  };

}

#endif //GAUNTLET_FILES_HH
