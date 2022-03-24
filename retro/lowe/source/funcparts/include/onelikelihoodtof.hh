#ifndef ONELIKELIHOODTOF_HH
#define ONELIKELIHOODTOF_HH

#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "tof.hh"
#include "distance_function.hh"
#include "fptoferror.hh"

class onelikelihoodtof : public function
{
public:
  onelikelihoodtof(){}
  virtual ~onelikelihoodtof()
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
  void Setfptoferror(std::shared_ptr<fptoferror> ptoferrorin)
  {
    ptoferror = ptoferrorin;
  }
  void Setdistance_function(std::shared_ptr<distance_function> fdistance_functionin)
  {
    fdistance_function = fdistance_functionin;
  }
  double returnvalue();
private:
  std::shared_ptr<fptoferror> ptoferror;
  std::shared_ptr<distance_function> fdistance_function;
  tof ftof;
  hitinfo info;
  Reconstructdata data;
};

#endif
  
