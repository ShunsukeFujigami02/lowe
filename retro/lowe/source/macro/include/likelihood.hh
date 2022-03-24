#ifndef LIKELIHOOD_HH
#define LIKELIHOOD_HH
// c++ STL
#include <memory>

// self-introduced library
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "fdirection.hh"
#include "afunction.hh"
class likelihood : public function
{
public:
  likelihood()
  {
  }
  
  virtual ~likelihood()
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
  void Setfdirectionnoretro(std::shared_ptr<fdirection> fdir)
  {
    fdirnoretro = fdir;
  }
  void Setafunctionnoretro(std::shared_ptr<afunction> afunc)
  {
    afuncnoretro = afunc;
  }
    void Setfdirectiononretro(std::shared_ptr<fdirection> fdir)
  {
    fdironretro = fdir;
  }
  void Setafunctiononretro(std::shared_ptr<afunction> afunc)
  {
    afunconretro = afunc;
  }
  double returnvalue() = 0;
  void Settimewindownoretro(double t)
  {
    timewindownoretro = t;
  }
  void Settimewindowonretro(double t)
  {
    timewindowonretro = t;
  }
  void Settoferrornoretro(double t)
  {
    toferrornoretro = t;
  }
  void Settoferroronretro(double t)
  {
    toferroronretro = t;
  }
  
protected:
  hitinfo info;
  Reconstructdata data;
  std::shared_ptr<fdirection> fdirnoretro;
  std::shared_ptr<afunction> afuncnoretro;
  std::shared_ptr<fdirection> fdironretro;
  std::shared_ptr<afunction> afunconretro;
  double toferrornoretro;
  double toferroronretro;
  double timewindownoretro;
  double timewindowonretro;
};

class likelihoodnoretro : public likelihood
{
public:
  likelihoodnoretro(){};
  virtual ~likelihoodnoretro(){};
  double returnvalue();
};

class likelihoodonretro : public likelihood
{
public:
  likelihoodonretro(){};
  virtual ~likelihoodonretro(){};
  double returnvalue();
};

class likelihoodsum : public likelihood
{
public:
  likelihoodsum(){};
  virtual ~likelihoodsum(){};
  double returnvalue();
};

#endif
