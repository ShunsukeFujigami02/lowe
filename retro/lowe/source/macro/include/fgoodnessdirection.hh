#ifndef FGOODNESSDIRECTION_HH
#define FGOODNESSDIRECTION_HH
// c++ STL
#include <memory>
// self
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class fgoodnessdirection : public function
{
public:
  fgoodnessdirection()
  {
  }
  virtual ~fgoodnessdirection()
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
  void Setsigmaangle(double sig)
  {
    sigmaangle = sig;
  }
  
  double returnvalue();
  void Setnoretromode()
  {
    cherenkovangle = 0.7224;
    noretromode = true;
  }
  void Setonretromode()
  {
    cherenkovangle = 2.4191;
    noretromode = false;
  }
private:
  hitinfo info;
  Reconstructdata data;
  double sigmaangle = 1.;
  double cherenkovangle = 0.7224; // (RAD)
  bool noretromode = true;
};

#endif
