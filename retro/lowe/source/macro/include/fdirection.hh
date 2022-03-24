#ifndef FDIRECTION_HH
#define FDIRECTION_HH
#include <memory>
#include "function.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class fdirection : public function
{
public:
  fdirection()
  {
  }
  
  virtual ~fdirection()
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
  double returnvalue() = 0; 
protected:
  hitinfo info;
  Reconstructdata data;
};

class fdirprototypenoretro : public fdirection
{
public:
  fdirprototypenoretro(){};
  virtual ~fdirprototypenoretro(){};
  double returnvalue();
};

class fdirprototypeonretro : public fdirection
{
public:
  fdirprototypeonretro(){};
  virtual ~fdirprototypeonretro(){};
  double returnvalue();
};

class fdirbydatanoretro : public fdirection
{
public:
  fdirbydatanoretro(){};
  virtual ~fdirbydatanoretro(){};
  double returnvalue();
};

class fdirbydataonretro : public fdirection
{
public:
  fdirbydataonretro(){};
  virtual ~fdirbydataonretro(){};
  double returnvalue();
};


#endif
  
