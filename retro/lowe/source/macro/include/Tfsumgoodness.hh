#ifndef TFSUMGOODNESS_HH
#define TFSUMGOODNESS_HH

#include "Tfunction.hh"

class Tfsumgoodness : public Tfunction
{
public:
  Tfsumgoodness()
  {
  }
  virtual ~Tfsumgoodness()
  {
  }
  void SetvHitinfo(std::vector<Thitinfo> vhitinfoin)
  {
    vhitinfo = vhitinfoin;
  }
  void SetReconstructdata(TReconstructdata datain)
  {
    data = datain;
  }
  virtual double returnvalue() = 0;
  void Setsigma(double sig)
  {
    sigma = sig;
  }
  
  void Setsigmaangle(double sigangle)
  {
    sigmaangle = sigangle;
  }
  
protected:
  std::vector<Thitinfo> vhitinfo;
  TReconstructdata data;
  double sigma = 5.;
  double sigmaangle = 1.;
public:
  ClassDef(Tfsumgoodness,1)
};

class Tfsumgoodnessnoretro : public Tfsumgoodness
{
public:
  Tfsumgoodnessnoretro()
  {
  }
  virtual ~Tfsumgoodnessnoretro()
  {
  }
  double returnvalue();
public:
  ClassDef(Tfsumgoodnessnoretro,1)
};
  
class Tfsumgoodnesssum : public Tfsumgoodness
{
public:
  Tfsumgoodnesssum(){};
  virtual ~Tfsumgoodnesssum(){};
  double returnvalue();
  void Setonretrocorrection(double c)
  {
    onretrocorrection = c;
  }
  
private:
  double onretrocorrection = 1.;
public:
  ClassDef(Tfsumgoodnesssum,1)
};
  
#endif
