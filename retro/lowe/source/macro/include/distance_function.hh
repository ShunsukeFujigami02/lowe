#ifndef DISTANCE_FUNCTION_HH
#define DISTANCE_FUNCTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class distance_function : public function
{
public:
  distance_function()
  {
  }
  virtual ~distance_function()
  {
  }
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  virtual double returnvalue() = 0;
protected:
  hitinfo info;
  Reconstructdata data;
};

class distance_position_pmt : public distance_function
{
public:
  distance_position_pmt(){};
  virtual ~distance_position_pmt()
  {
  }
  double returnvalue();
};

class distance_position_retro : public distance_function
{
public:
  distance_position_retro()
  {
  }
  ;
  virtual ~distance_position_retro()
  {
  }
  double returnvalue();
};


class distance_fly_retro : public distance_function
{
public:
  distance_fly_retro()
  {
  }
  virtual ~distance_fly_retro()
  {
  }
  double returnvalue();
};
#endif
