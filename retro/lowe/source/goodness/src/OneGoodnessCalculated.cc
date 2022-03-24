// c++ STL
#include <cmath>
// geant4-library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "GoodnessManager.hh"
#include "OneGoodnessCalculated.hh"
#include "constants.hh"

double OneGoodnessCalculated::distance_position_pmt() const
{
  CLHEP::Hep3Vector position = vertex.vect();
  CLHEP::Hep3Vector position_pmt = position - pmtposition;
  double d1 = std::sqrt(position_pmt*position_pmt);
  return d1;
}

double OneGoodnessCalculated::distance_position_retro() const
{
  double positionX =vertex.x();
  double positionY =vertex.y();
  double positionZ =vertex.z();
  double pmtX = pmtposition.x();
  double pmtY = pmtposition.y();
  double pmtZ = pmtposition.z();
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
    t = (half_WClength - positionZ)/(pmtZ-positionZ);
    z = half_WClength;
  }
  else{
    t = (-half_WClength - positionZ)/(pmtZ-positionZ);
    z = - half_WClength;
  }
  double x = positionX + (pmtX-positionX)*t;
  double y = positionY + (pmtY-positionY)*t;
  double d2 = std::sqrt((positionX-x)*(positionX-x)+(positionY-y)*(positionY-y)+(positionZ-z)*(positionZ-z));
  return d2;
}

double OneGoodnessCalculated::distance_fly_retro() const{
  double d_position_pmt = distance_position_pmt();
  double d_position_retro = distance_position_retro();
  return (d_position_pmt + 2*d_position_retro);
}


double OneGoodnessCalculated::tof_no_retro() const{
  double tof = hittime - vertex.t() - offset - (distance_position_pmt() - doffset)/v_light_in_water;
  return tof;
}

double OneGoodnessCalculated::tof(double distance) const
{
  double tof = hittime - vertex.t() - offset - (distance - doffset)/v_light_in_water;
  return tof;
}


double OneGoodnessCalculated::tof_on_retro() const{
  double tof = hittime - vertex.t() - offset - (distance_fly_retro() - doffset)/v_light_in_water;
  return tof;
}
