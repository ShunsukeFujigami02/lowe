#ifndef TFGOODNESSDIRECTION_HH
#define TFGOODNESSDIRECTION_HH

#include "Tfunction.hh"

class Tfgoodnessdirection : public Tfunction
{
public:
  Tfgoodnessdirection()
  {
  }
  virtual ~Tfgoodnessdirection()
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
  void Setsigmaangle(double sigangle)
  {
    sigmaangle = sigangle;
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
    noretromode =false;
  }
private:
  Thitinfo info;
  TReconstructdata data;
  double sigmaangle = 1.;
  double cherenkovangle = 0.7224; // (RAD)
  bool noretromode = true;
public:
  ClassDef(Tfgoodnessdirection,1)
};

#endif
  
