#ifndef TDISTANCE_FUNCTION_HH
#define TDISTANCE_FUNCTION_HH

// self-introduced library
#include "Tfunction.hh"
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Tdistance_function : public Tfunction
{
public:
  Tdistance_function()
  {
  }
  virtual ~Tdistance_function()
  {
  }
  void SetHitInfo(Thitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(TReconstructdata datain)
  {
    data = datain;
  }
  virtual double returnvalue() = 0;
protected:
  Thitinfo info;
  TReconstructdata data;
public:
  ClassDef(Tdistance_function,1)
};

class Tdistance_position_pmt : public Tdistance_function
{
public:
  Tdistance_position_pmt(){};
  virtual ~Tdistance_position_pmt()
  {
  }
  double returnvalue();
public:
  ClassDef(Tdistance_position_pmt,1)
};

class Tdistance_position_retro : public Tdistance_function
{
public:
  Tdistance_position_retro()
  {
  }
  ;
  virtual ~Tdistance_position_retro()
  {
  }
  double returnvalue();
public:
  ClassDef(Tdistance_position_retro,1)
};


class Tdistance_fly_retro : public Tdistance_function
{
public:
  Tdistance_fly_retro()
  {
  }
  virtual ~Tdistance_fly_retro()
  {
  }
  double returnvalue();
public:
  ClassDef(Tdistance_fly_retro,1)
};

#endif
