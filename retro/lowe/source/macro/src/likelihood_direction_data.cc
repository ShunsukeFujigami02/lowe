#include "likelihood_direction_data.hh"

ClassImp(l_dir_data)

l_dir_data::l_dir_data()
:likelihood(-10000000.),costheta(0.),phi(0.)
{}

l_dir_data::l_dir_data(double costheta_in,double phi_in,double likelihood_in)
  :likelihood(likelihood_in),costheta(costheta_in),phi(phi_in)
{}

void l_dir_data::Setdata(l_dir_data data)
{
  SetL(data.GetL());
  SetCosTheta(data.GetCosTheta());
  SetPhi(data.GetPhi());
}

