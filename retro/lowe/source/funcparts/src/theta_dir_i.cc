// geant4 library
#include <CLHEP/Vector/ThreeVector.h>


// self-introduced library
#include "theta_dir_i.hh"

double theta_dir_i::returnvalue()
{
  CLHEP::Hep3Vector hminusv = info.Get3Position() - data.Get3Position();
  return data.Getdirection().angle(hminusv);
}


