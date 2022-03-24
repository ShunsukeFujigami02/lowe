#ifndef TFGOODNESS_HH
#define TFGOODNESS_HH

#include "Tfunction.hh"
#include "Ttof.hh"
#include "Tdistance_function.hh"

class Tfgoodness : public Tfunction
{
public:
  Tfgoodness()
  {
  }
  virtual ~Tfgoodness()
  {
  }
  void Setsigma(double sig)
  {
    sigma = sig;
  }
  void Settof(Ttof* tofin)
  {
    tof = tofin;
  }
  void Setdistancefunction(Tdistance_function* dis_in)
  {
    dis = dis_in;
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
  double sigma = 5.;
  Ttof* tof;
  Tdistance_function* dis;
public:
  ClassDef(Tfgoodness,1)
};

#endif
  
	        
  
