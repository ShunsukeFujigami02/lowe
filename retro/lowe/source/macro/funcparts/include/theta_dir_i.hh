#ifndef THETA_DIR_I_HH
#define THETA_DIR_I_HH

// self-introduced library
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class theta_dir_i : public function
{
public:
  theta_dir_i()
  {
  }
  virtual ~theta_dir_i()
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
