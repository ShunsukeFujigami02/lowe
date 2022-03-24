// c++ STL
#include <cmath>
// self-introduced library
#include "fgoodness.hh"

double fgoodness::returnvalue()
{
  ftof->SetHitInfo(info);
  ftof->SetReconstructdata(data);
  ftof->Setdistancefunction(dfunc);
  double toferror = ftof->returnvalue() - data.Get4Vector().t();
  double goodness = std::exp(-0.5*std::pow((toferror/sigma),2.0));
  return goodness;
}


