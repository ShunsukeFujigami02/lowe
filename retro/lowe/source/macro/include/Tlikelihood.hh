#ifndef TLIKELIHOOD_HH
#define TLIKELIHOOD_HH
// c++ STL
#include <memory>

// self-introduced library
#include "Thitinfo.hh"
#include "TReconstructdata.hh"
#include "Tfdirection.hh"
#include "Tafunction.hh"
#include "Tfunction.hh"

class Tlikelihood : public Tfunction
{
public:
  Tlikelihood()
  {
  }
  
  virtual ~Tlikelihood()
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
  void Setfdirectionnoretro(Tfdirection* fdir)
  {
    fdirnoretro = fdir;
  }
  void Setafunctionnoretro(Tafunction* afunc)
  {
    afuncnoretro = afunc;
  }
    void Setfdirectiononretro(Tfdirection* fdir)
  {
    fdironretro = fdir;
  }
  void Setafunctiononretro(Tafunction* afunc)
  {
    afunconretro = afunc;
  }
  double returnvalue() = 0;
protected:
  Thitinfo info;
  TReconstructdata data;
  Tfdirection* fdirnoretro;
  Tafunction* afuncnoretro;
  Tfdirection* fdironretro;
  Tafunction* afunconretro;
public:
  ClassDef(Tlikelihood,1)
};

class Tlikelihoodnoretro : public Tlikelihood
{
public:
  Tlikelihoodnoretro(){};
  virtual ~Tlikelihoodnoretro(){};
  double returnvalue();
public:
  ClassDef(Tlikelihoodnoretro,1)
};

class Tlikelihoodonretro : public Tlikelihood
{
public:
  Tlikelihoodonretro(){};
  virtual ~Tlikelihoodonretro(){};
  double returnvalue();
public:
  ClassDef(Tlikelihoodonretro,1)
};

class Tlikelihoodsum : public Tlikelihood
{
public:
  Tlikelihoodsum(){};
  virtual ~Tlikelihoodsum(){};
  double returnvalue();
public:
  ClassDef(Tlikelihoodsum,1)
};

#endif
