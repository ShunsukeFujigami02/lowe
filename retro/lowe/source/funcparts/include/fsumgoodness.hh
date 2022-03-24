#ifndef FSUMGOODNESS_HH
#define FSUMGOODNESS_HH

// c++ STL
#include <memory>
#include <list>

// self
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "fgoodness.hh"

class fsumgoodness: public function
{
public:
  fsumgoodness()
  {
  }
  virtual ~fsumgoodness()
  {
  }
  void SetHitInfo(WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom);
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  void Setsigma(double sig)
  {
    sigma = sig;
  }
  void Setsigmaangle(double sigangle)
  {
    sigmaangle = sigangle;
  }
  virtual double returnvalue() = 0;
  virtual double returnvalueminus(const double* a) = 0;
  std::vector<hitinfo> vinfo;  
protected:
  double sigma = 5.;
  double sigmaangle = 1.;
  Reconstructdata data;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
};

class fsumgoodnessnoretro : public fsumgoodness
{
public:
  fsumgoodnessnoretro(){};
  virtual ~fsumgoodnessnoretro(){};
  double returnvalue();
  double returnvalueminus(const double* a);
};

class fsumgoodnesssum : public fsumgoodness
{
public:
  fsumgoodnesssum(){};
  virtual ~fsumgoodnesssum(){};
  double returnvalue();
  void Setonretrocorrection(double c)
  {
    onretrocorrection = c;
  }
  double returnvalueminus(const double* a);
  
private:
  double onretrocorrection = 1.;
};

#endif
