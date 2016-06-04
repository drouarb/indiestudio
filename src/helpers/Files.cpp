//
// Created by greg on 04/06/16.
//

#include "Files.hh"

const std::string &gauntlet::Files::getFile(const std::string &filename) const
{
  return this->stringList.at(filename);
}

void gauntlet::Files::addFiles(const std::string &filename,
			       const std::string &content)
{
  this->stringList[filename] = content;
}

