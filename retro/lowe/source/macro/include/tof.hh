#ifndef TOF_HH
#define TOF_HH

// c++ STL
#include <memory>


// self-introduced library
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "distance_function.hh"
#include "constants.hh"
class tof : public function
{
public:
  tof(){};
  virtual ~tof(){};
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  void Setdistancefunction(std::shared_ptr<distance_function> dfunc)
  {
    this->dfunc = dfunc;
  }
  virtual double returnvalue()
  {
    dfunc->SetHitInfo(info);
    dfunc->SetReconstructdata(data);
    double tof = info.HitTime() - offset - (dfunc->returnvalue() - doffset)/(v_light/nwater);
    return tof;
  }
  void Setnwater(double n)
  {
    nwater = n;
  }
  
private:
  hitinfo info;
  Reconstructdata data;
  double nwater = 1.38072381233779451;
  double doffset = 1.95775611238980325e+01;
  std::shared_ptr<distance_function> dfunc;
};

#endif
