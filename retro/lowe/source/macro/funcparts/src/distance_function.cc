// c++ STL
#include <cmath>

// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "distance_function.hh"
double distance_position_pmt::returnvalue()
{
  CLHEP::Hep3Vector position_pmt = data.Get3Position() - info.Get3Position();
  double d = std::sqrt(position_pmt*position_pmt);
  return d;
}

double distance_position_retro::returnvalue()
{
  double positionX = data.Get3Position().x();
  double positionY = data.Get3Position().y();
  double positionZ = data.Get3Position().z();
  double pmtX = info.GetPosition(0);
  double pmtY = info.GetPosition(1);
  double pmtZ = info.GetPosition(2);
  double WCradius = info.GetWCradius();
  double WClength = info.GetWClength();
  double half_WClength = WClength/2.;
  double a = (pmtX-positionX)*(pmtX-positionX)+(pmtY-positionY)*(pmtY-positionY);
  double b = positionX*(positionX-pmtX)+positionY*(positionY-pmtY);
  double c = positionX*positionX+positionY*positionY-WCradius*WCradius;
  double t;
  if(a != 0){
    t = (b-sqrt(b*b-a*c))/a;
  }
  else{
    t = -c/(2*b);
  }
  double z = positionZ + (pmtZ - positionZ)*t;
  if(-half_WClength < z && half_WClength > z){

}
  else if(z > half_WClength){
    t = (half_WClength - positionX)/(pmtZ-positionX);
    z = half_WClength;
  }
  else{
    t = (-half_WClength - positionX)/(pmtZ-positionX);
    z = - half_WClength;
  }
  double x = positionX + (pmtX-positionX)*t;
  double y = positionY + (pmtY-positionY)*t;
  double d2 = std::sqrt((positionX-x)*(positionX-x)+(positionY-y)*(positionY-y)+(positionZ-z)*(positionZ-z));
  return d2;
}

double distance_fly_retro::returnvalue()
{
  distance_position_pmt d_position_pmt;
  d_position_pmt.SetHitInfo(info);
  d_position_pmt.SetReconstructdata(data);
  distance_position_retro d_position_retro;
  d_position_retro.SetHitInfo(info);
  d_position_retro.SetReconstructdata(data);
  double d_p_p = d_position_pmt.returnvalue();
  double d_p_r = d_position_retro.returnvalue();
  return (d_p_p + 2* d_p_r);
}

