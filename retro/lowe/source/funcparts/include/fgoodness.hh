#ifndef FGOODNESS_HH
#define FGOODNESS_HH
// c++ STL
#include <memory>

/// self-introduced library
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "tof.hh"
#include "distance_function.hh"

class fgoodness :public function
{
public:
  fgoodness()
  {
  }
  virtual ~fgoodness()
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
  void Settof(std::shared_ptr<tof> tofin)
  {
    ftof = tofin;
  }
  void Setdistance_function(std::shared_ptr<distance_function> d)
  {
    dfunc = d;
  }
  void Setsigma(double sig)
  {
    sigma = sig;
  }
  
  double returnvalue();
private:
  hitinfo info;
  Reconstructdata data;
  double sigma = 5.;
  std::shared_ptr<tof> ftof;
  std::shared_ptr<distance_function> dfunc;
};

#endif
