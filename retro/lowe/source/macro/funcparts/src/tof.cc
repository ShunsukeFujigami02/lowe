// self-introduced library
#include "constants.hh"

double tof(double time ,double d1){
  double tof = time-d1/v_light_in_water;
  return tof;
}
