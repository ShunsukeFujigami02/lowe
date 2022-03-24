#ifndef TTHETA_I_FUNC_HH
#define TTHETA_I_FUNC_HH

// ROOT library
#include <TVector3.h>
// self-introduced library
#include "Tfunction.hh"
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Ttheta_i_func : public Tfunction
{
public:
  Ttheta_i_func()
  {
  }
  virtual ~Ttheta_i_func()
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
  double returnvalue();
private:
  Thitinfo info;
  TReconstructdata data;
public:
  ClassDef(Ttheta_i_func,1)
};

#endif
