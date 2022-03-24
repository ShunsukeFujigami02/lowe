// ROOT library
#include <TVector3.h>

// self-introduced library
#include "Ttheta_dir_i.hh"

ClassImp(Ttheta_dir_i)

double Ttheta_dir_i::returnvalue()
{
  TVector3 hminusv = info.Get3Position() - data.Get3Position();
  return data.Getdirection().Angle(hminusv);
}


