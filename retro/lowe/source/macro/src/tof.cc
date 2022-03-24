// self-introduced library
#include "constants.hh"

double tof(double time ,double d1){
  double doffset = 1.95775611238980325e+01;
  double tof = time-(d1 - doffset)/v_light_in_water;
  return tof;
}
