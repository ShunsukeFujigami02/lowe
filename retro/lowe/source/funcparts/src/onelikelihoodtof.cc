#include <cmath>
#include "onelikelihoodtof.hh"

double onelikelihoodtof::returnvalue()
{
  ftof.SetHitInfo(info);
  ftof.SetReconstructdata(data);
  ftof.Setdistancefunction(fdistance_function);
  double toferror = ftof.returnvalue() - data.Get4Vector().t();
  double p = ptoferror->p(toferror);
  return std::log(p);
}

