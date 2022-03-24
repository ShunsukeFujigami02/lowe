#ifndef TTHETA_DIR_I_HH
#define TTHETA_DIR_I_HH

// self-introduced library
#include "Tfunction.hh"
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Ttheta_dir_i : public Tfunction
{
public:
  Ttheta_dir_i()
  {
  }
  virtual ~Ttheta_dir_i()
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
  ClassDef(Ttheta_dir_i,1)
};

#endif
