#ifndef ROTATION3D_HH
#define ROTATION3D_HH

#include <TMatrixD.h>
#include <TVector3.h>
#include <CLHEP/Vector/ThreeVector.h>
TMatrixD rotation3D(TVector3 nvec);

TMatrixD rotation3D(CLHEP::Hep3Vector nvec);

TVector3 cross(TMatrixD m,TVector3 vec);

CLHEP::Hep3Vector cross(TMatrixD m,CLHEP::Hep3Vector vec);

#endif
