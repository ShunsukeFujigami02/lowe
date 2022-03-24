// c++ STL
#include <cmath>
// self
#include "fgoodnessdirection.hh"
#include "theta_dir_i.hh"

double fgoodnessdirection::returnvalue()
{
  theta_dir_i ftheta_dir_i;
  ftheta_dir_i.SetHitInfo(info);
  ftheta_dir_i.SetReconstructdata(data);
  double angle = ftheta_dir_i.returnvalue();
  double angleerror = angle - cherenkovangle;
  double g = std::exp(-0.5*std::pow(angleerror/sigmaangle,2.0));
  return g;
}

