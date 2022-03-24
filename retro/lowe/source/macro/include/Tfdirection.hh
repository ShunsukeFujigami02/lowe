#ifndef TFDIRECTION_HH
#define TFDIRECTION_HH

#include "Tfunction.hh"
#include "Thitinfo.hh"
#include "TReconstructdata.hh"

class Tfdirection : public Tfunction
{
public:
  Tfdirection()
  {
  }
  
  virtual ~Tfdirection()
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
  ClassDef(Tfdirection,1)
};

class Tfdirprototypenoretro : public Tfdirection
{
public:
  Tfdirprototypenoretro(){};
  virtual ~Tfdirprototypenoretro(){};
  double returnvalue();
  ClassDef(Tfdirprototypenoretro,1)
};

class Tfdirprototypeonretro : public Tfdirection
{
public:
  Tfdirprototypeonretro(){};
  virtual ~Tfdirprototypeonretro(){};
  double returnvalue();
  ClassDef(Tfdirprototypeonretro,1)
};

class Tfdirbydatanoretro : public Tfdirection
{
public:
  Tfdirbydatanoretro(){};
  virtual ~Tfdirbydatanoretro(){};
  double returnvalue();
public:
  ClassDef(Tfdirbydatanoretro,1)
};

class Tfdirbydataonretro : public Tfdirection
{
public:
  Tfdirbydataonretro(){};
  virtual ~Tfdirbydataonretro(){};
  double returnvalue();
public:
  ClassDef(Tfdirbydataonretro,1)
};


#endif
  
