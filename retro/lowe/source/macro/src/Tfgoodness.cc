#include "Tfgoodness.hh"
#include <cmath>

ClassImp(Tfgoodness)

double Tfgoodness::returnvalue()
{
  tof->SetHitInfo(info);
  tof->SetReconstructdata(data);
  tof->Setdistancefunction(dis);
  double toferror = tof->returnvalue() - data.Get4Vector().T();
  double goodness = std::exp(-0.5*std::pow((toferror/sigma),2.0));
  return goodness;
}

