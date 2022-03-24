// geant4 library
#include <CLHEP/Vector/ThreeVector.h>

// self-introduced library
#include "theta_i_func.hh"

double theta_i_func::returnvalue()
{
  CLHEP::Hep3Vector vector = info.Get3Orientation();
  CLHEP::Hep3Vector hminusv = info.Get3Position() - data.Get3Position();
  CLHEP::Hep3Vector orientation = info.Get3Orientation();
  return orientation.angle(-hminusv);
}

