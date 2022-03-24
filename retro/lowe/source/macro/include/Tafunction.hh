#ifndef TAFUNCTION_HH
#define TAFUNCTION_HH

#include "Tfunction.hh"
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Tafunction : public Tfunction
{
public:
  Tafunction()
  {
  }
  
  virtual ~Tafunction()
  {
  }
  void SetHitInfo(Thitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(TReconstructdata datain)
  {
    data = datain;
  }
  virtual double returnvalue() = 0; 
private:
  Thitinfo info;
  TReconstructdata data;
public:
  ClassDef(Tafunction,1)
};
  
class Tafuncprototype : public Tafunction
{
public:
  Tafuncprototype()
  {
  }
  virtual ~Tafuncprototype()
  {
  }

  double returnvalue()
  {
    return 1.;
  }
public:
  ClassDef(Tafuncprototype,1)
};

#endif  
