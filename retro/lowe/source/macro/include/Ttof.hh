#ifndef TTOF_HH
#define TTOF_HH

// c++ STL
#include <memory>


// self-introduced library
#include "Thitinfo.hh"
#include "TReconstructdata.hh"
#include "Tdistance_function.hh"
#include "constants.hh"
class Ttof : public Tfunction
{
public:
  Ttof(){};
  virtual ~Ttof(){};
  void SetHitInfo(Thitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(TReconstructdata datain)
  {
    data = datain;
  }
  void Setdistancefunction(Tdistance_function* dfunc)
  {
    this->dfunc = dfunc;
  }
  virtual double returnvalue()
  {
    dfunc->SetHitInfo(info);
    dfunc->SetReconstructdata(data);
    double tof = info.HitTime() - offset - dfunc->returnvalue()/(v_light/nwater);
    return tof;
  }
  void Setnwater(double n)
  {
    nwater = n;
  }
  
private:
  Thitinfo info;
  TReconstructdata data;
  Tdistance_function* dfunc;
  double nwater;
public:
  ClassDef(Ttof,1)
};

#endif
