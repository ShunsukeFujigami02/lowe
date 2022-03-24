#include "rotation3D.hh"

TMatrixD rotation3D(TVector3 nvecz)
{
  nvecz.SetMag(1.);
  TVector3 ex(1.,0.,0.);
  TVector3 ey(0.,1.,0.);
  TVector3 nvecx = ex - (ex*nvecz)* nvecz;
  nvecx.SetMag(1.);
  TVector3 nvecy = ey - (ey*nvecz)* nvecz - (ey* nvecx)* nvecx;
  nvecy.SetMag(1.);
  TMatrixD m(3,3);
  m(0,0) = nvecx.X();
  m(1,0) = nvecx.Y();
  m(2,0) = nvecx.Z();
  m(0,1) = nvecy.X();
  m(1,1) = nvecy.Y();
  m(2,1) = nvecy.Z();
  m(0,2) = nvecz.X();
  m(1,2) = nvecz.Y();
  m(2,2) = nvecz.Z();
  double d1,d2;
  m.Determinant(d1,d2);
  if(d1 < 0.)
    {
      m(0,0) = nvecy.X();
      m(1,0) = nvecy.Y();
      m(2,0) = nvecy.Z();
      m(0,1) = nvecx.X();
      m(1,1) = nvecx.Y();
      m(2,1) = nvecx.Z();
    }
  m.Invert();
  return m;
}

TMatrixD rotation3D(CLHEP::Hep3Vector nvecz){
  nvecz.setMag(1.);
  CLHEP::Hep3Vector ex(1.,0.,0.);
  CLHEP::Hep3Vector ey(0.,1.,0.);
  CLHEP::Hep3Vector nvecx = ex - (ex*nvecz)* nvecz;
  nvecx.setMag(1.);
  CLHEP::Hep3Vector nvecy = ey - (ey*nvecz)* nvecz - (ey* nvecx)* nvecx;
  nvecy.setMag(1.);
  TMatrixD m(3,3);
  m(0,0) = nvecx.x();
  m(1,0) = nvecx.y();
  m(2,0) = nvecx.z();
  m(0,1) = nvecy.x();
  m(1,1) = nvecy.y();
  m(2,1) = nvecy.z();
  m(0,2) = nvecz.x();
  m(1,2) = nvecz.y();
  m(2,2) = nvecz.z();
  double d1,d2;
  m.Determinant(d1,d2);
  if(d1 < 0.)
    {
      m(0,0) = nvecy.x();
      m(1,0) = nvecy.y();
      m(2,0) = nvecy.z();
      m(0,1) = nvecx.x();
      m(1,1) = nvecx.y();
      m(2,1) = nvecx.z();
    }
  m.Invert();
  return m;
}

TVector3 cross(TMatrixD m,TVector3 vec)
{
  double vecx = vec.x();
  double vecy = vec.y();
  double vecz = vec.z();
  double x = m(0,0)* vecx + m(0,1)* vecy + m(0,2) * vecz;
  double y = m(1,0)* vecx + m(1,1)* vecy + m(1,2) * vecz;
  double z = m(2,0)* vecx + m(2,1)* vecy + m(2,2) * vecz;
  return TVector3(x,y,z);
}

CLHEP::Hep3Vector cross(TMatrixD m,CLHEP::Hep3Vector vec)
{
  double vecx = vec.x();
  double vecy = vec.y();
  double vecz = vec.z();
  double x = m(0,0)* vecx + m(0,1)* vecy + m(0,2) * vecz;
  double y = m(1,0)* vecx + m(1,1)* vecy + m(1,2) * vecz;
  double z = m(2,0)* vecx + m(2,1)* vecy + m(2,2) * vecz;
  return CLHEP::Hep3Vector(x,y,z);
}

  
