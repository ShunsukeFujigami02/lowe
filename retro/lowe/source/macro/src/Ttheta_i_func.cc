// geant4 library
#include <TVector3.h>
// self-introduced library
#include "Ttheta_i_func.hh"

ClassImp(Ttheta_i_func)

double Ttheta_i_func::returnvalue()
{
  TVector3 vector = info.Get3Orientation();
  TVector3 hminusv = info.Get3Position() - data.Get3Position();
  TVector3 orientation = info.Get3Orientation();
  return orientation.Angle(-hminusv);
}

