#ifndef LIKELIHOODDIRECTIONCALCULATEMANAGER_HH
#define LIKELIHOODDIRECTIONCALCULATEMANAGER_HH
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "ProcessManager.hh"
#include "OneLikelihoodDirectionCalculateManager.hh"

class LikelihoodDirectionCalculateManager : public ProcessManager
{
public:
  LikelihoodDirectionCalculateManager();
  virtual ~LikelihoodDirectionCalculateManager();
  void Doprocess();
  void Doloopin(int k);
private:
  int ncherenkovdigihits;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
};

#endif
