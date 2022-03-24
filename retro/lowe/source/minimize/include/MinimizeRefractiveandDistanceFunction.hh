#ifndef MINIMIZEREFRACTIVEANDDISTANCEFUNCTION_HH
#define MINIMIZEREFRACTIVEANDDISTANCEFUNCTION_HH

#include <TFile.h>
#include <TTree.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

class MinimizeRefractiveandDistanceFunction
{
public:
  MinimizeRefractiveandDistanceFunction(const char *infile);
  virtual ~MinimizeRefractiveandDistanceFunction();
  double returnpeakmean(const double* a);
  double returnpeakwidth(const double* a);
  std::vector<double> returnvalue(const double* a);
  std::vector<double> returnvaluecutanglepeak(const double* a);
  std::vector<double> returnvaluecutanglepeakaddflyparticle(const double* a);
  double returnminimizedfunctioncutanglepeakaddflyparticle(const double* a);
private:
  TFile* file = nullptr;
  TTree* wcsimT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
};
  
#endif
