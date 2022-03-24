#ifndef MINIMIZEREFRACTIVEFUNCTION_HH
#define MINIMIZEREFRACTIVEFUNCTION_HH

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

class MinimizeRefractiveFunction
{
public:
  MinimizeRefractiveFunction(const char *infile);
  virtual ~MinimizeRefractiveFunction();
  double returnvalue(const double* a);
  std::vector<double> returnmeanandpeak(const double* a);
  void Filltofhist(TH1D* h1,TH1D* hlog,const double* a);  
private:
  TFile* file = nullptr;
  TTree* wcsimT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  double nwater;
};
  
#endif
