#ifndef THETA_I_FUNC_HH
#define THETA_I_FUNC_HH
// c++ STL
#include <memory>
// ROOT library
#include <TVector3.h>
// self-introduced library
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class theta_i_func : public function
{
public:
  theta_i_func()
  {
  }
  virtual ~theta_i_func()
  {
  }
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  double returnvalue();
private:
  hitinfo info;
  Reconstructdata data;
};

#endif
