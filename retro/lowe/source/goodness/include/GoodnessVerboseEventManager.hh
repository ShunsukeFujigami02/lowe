#ifndef GOODNESSVERBOSEEVENTMANAGER_HH
#define GOODNESSVERBOSEEVENTMANAGER_HH

// self-introduced library
#include "ProcessManager.hh"

class GoodnessVerboseEventManager : public ProcessManager
{
public:
  GoodnessVerboseEventManager();
  virtual ~GoodnessVerboseEventManager();
  void Doprocess();
  void Doloopin(int k);
private:
  int ncherenkovdigihits;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
};

#endif
  
