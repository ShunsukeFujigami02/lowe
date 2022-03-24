#ifndef FUNCMAP_HH
#define FUNCMAP_HH

#include <functional>
#include <map>
#include <cmath>

std::map<const char*,std::function<double(double,double)>> funcmap {
  {"plus",[](auto e1,auto e2){return e1 + e2;}}
  ,{"minus",[](auto e1,auto e2){return e1 - e2;}}
  ,{"multi",[](auto e1,auto e2){return e1 * e2;}}
  ,{"divide",[](auto e1,auto e2){return e1/e2;}}
  ,{"gamma",[](auto e1,auto e2){return std::log(e1/e2)/std::log(10.);}}
};

#endif
