#ifndef GOODNESSVERBOSECALCULATEMANAGER_HH
#define GOODNESSVERBOSECALCULATEMANAGER_HH

// self-introduced library
#include "ProcessManager.hh"

class GoodnessVerboseCalculateManager : public ProcessManager
{
public:
  GoodnessVerboseCalculateManager();
  virtual ~GoodnessVerboseCalculateManager();
  void SetParameters();
  void Doprocess();
  void Setup();
  void SetHit(WCSimRootCherenkovDigiHit* h)
  {
    hit = h;
  }
  void Setsigma(double sig)
  {
    sigma = sig;
  }
  
private:
  WCSimRootGeom* wcsimrootgeom = nullptr;
  WCSimRootCherenkovDigiHit* hit;
  double sigma;
};

#endif  
