#ifndef TFUNCTION_HH
#define TFUNCTION_HH

#include <TObject.h>
#include <vector>
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Tfunction : public TObject
{
public:
  Tfunction()
  {
  }
  virtual ~Tfunction(){};
  virtual double returnvalue() = 0;
  virtual void SetHitInfo(Thitinfo infoin);
  virtual void SetvHitInfo(std::vector<Thitinfo> vhitinfo);
  virtual void SetReconstructdata(TReconstructdata datain) = 0;
  virtual void Setsigma(double sig);
  virtual void Setsigmaangle(double sigangle);
  virtual void Setonretrocorrection(double c);
  ClassDef(Tfunction,1)
};

#endif
  
