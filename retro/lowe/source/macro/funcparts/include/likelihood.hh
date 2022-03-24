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
protected:
  hitinfo info;
  Reconstructdata data;
  std::shared_ptr<fdirection> fdirnoretro;
  std::shared_ptr<afunction> afuncnoretro;
  std::shared_ptr<fdirection> fdironretro;
  std::shared_ptr<afunction> afunconretro;
  
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
