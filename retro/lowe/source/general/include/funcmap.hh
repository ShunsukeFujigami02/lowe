#ifndef FUNCMAP_HH
#define FUNCMAP_HH
// c++ STL
#include <cstring>
#include <map>
#include <memory>

// self-introduced library
#include "distance_function.hh"
#include "likelihood.hh"
#include "fdirection.hh"
#include "afunction.hh"

class funcmap
{
public:
  funcmap();
  virtual ~funcmap(){}
  void setup();
  std::map<std::string,std::shared_ptr<likelihood>> lfuncmap;
  std::map<std::string,std::shared_ptr<distance_function>> distancefuncmap;
  std::map<std::string,std::shared_ptr<fdirection>> fdirmap;
  std::map<std::string,std::shared_ptr<afunction>> afuncmap;
};

#endif
