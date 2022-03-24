#ifndef ONELIKELIHOODDIRECTIONCALCULATEMANAGER_HH
#define ONELIKELIHOODDIRECTIONCALCULATEMANAGER_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "ProcessManager.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "likelihood.hh"
#include "fdirection.hh"
#include "afunction.hh"

class OneLikelihoodDirectionCalculateManager : public ProcessManager
{
public:
  OneLikelihoodDirectionCalculateManager(const char* likelihoodtype);
  virtual ~OneLikelihoodDirectionCalculateManager();
  void SetParameters();
  void Doprocess();
  void Setup();
  void SetHit(WCSimRootCherenkovDigiHit* h)
  {
    hit = h;
  }
  void Setlikelihoodfuncnoretro(std::shared_ptr<likelihood> lhin)
  {
    ln = lhin;
  }
  void Setlikelihoodfunconretro(std::shared_ptr<likelihood> lhin)
  {
    lo = lhin;
  }
  
  void Setfdirectionnoretro(std::shared_ptr<fdirection> f)
  {
    fn = f;
  }
  void Setfdirectiononretro(std::shared_ptr<fdirection> f)
  {
    fo = f;
  }
  void Setafunctionnoretro(std::shared_ptr<afunction> a)
  {
    an = a;
  }
  void Setafunctiononretro(std::shared_ptr<afunction> a)
  {
    ao = a;
  }
  
private:
  WCSimRootGeom* wcsimrootgeom = nullptr;
  double WCradius;
  double WClength;
  WCSimRootCherenkovDigiHit* hit;
  std::shared_ptr<likelihood> ln;
  std::shared_ptr<likelihood> lo;
  std::shared_ptr<fdirection> fn;
  std::shared_ptr<fdirection> fo;
  std::shared_ptr<afunction> an;
  std::shared_ptr<afunction> ao;
  std::string ltype;
};

#endif
