#ifndef GETFUNCTIONDIRECTIONFUNC_HH
#define GETFUNCTIONDIRECTIONFUNC_HH
// c++ STL
#include <vector>

// ROOT library
#include <TVector.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// a group of function about theta_i
// theta_i is vertex to hit direction angle against particle direction
// this library is created for the exe/get_function_direction.cc

double gettheta_i(WCSimRootCherenkovDigiHit* hit,WCSimRootGeom *wcsimrootgeom,TVector3 truevertex,TVector3 truedirection);

// return theta_i for one hit

void setvtheta_i(std::vector<double> vtheta_i,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,TVector3 truevertex,TVector3 truedirection);

// input theta_i value given std::vector vtheta_i over one event hit

void setvcostheta_i(std::vector<double> vcostheta_i,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,TVector3 truevertex,TVector3 truedirection);

// input costheta_i value given std::vector vcostheta_i over one event hit


#endif
