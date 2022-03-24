#ifndef PROCESSMANAGER_HH
#define PROCESSMANAGER_HH

// c++ STL
#include <memory>
// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"
// self-introduced library
#include "Process.hh"
#include "VAction.hh"
#include "TReconstructdata.hh"

class ProcessManager : public std::enable_shared_from_this<ProcessManager>
{
public:
  static std::shared_ptr<ProcessManager> GetProcessManager(int i)
  {
    return vprocessmanager.at(i);
  }
private:
  static std::vector<std::shared_ptr<ProcessManager>> vprocessmanager;
public:
  ProcessManager();
  virtual ~ProcessManager(){};
  void SetProcessManager();
  void Run(int N);
  virtual void Doprocess() = 0;
  virtual void ProcessOneEvent(int i);
  virtual void ProcessOne(std::shared_ptr<Process> process);
  virtual WCSimRootEvent* GetWCSimRootEvent()
  {
    return nullptr;  
  }
  
  virtual WCSimRootGeom* GetWCSimRootGeom()
  {
    return nullptr;
  }
  
  virtual void SetHit(WCSimRootCherenkovDigiHit* hit);
  virtual TReconstructdata* GetTReconstructdata()
  {
    return nullptr;
  }
  
  void SetAction(std::shared_ptr<VAction> action_in)
  {
    action = action_in;
  }
  void SetNextManager(std::shared_ptr<ProcessManager> manager)
  {
    nextmanager = manager;
  }
  void SetProcess(std::shared_ptr<Process> process)
  {
    currentprocess = process;
  }
  
  
protected:
  std::shared_ptr<ProcessManager> nextmanager = nullptr;
  std::shared_ptr<VAction> action = nullptr;
  std::shared_ptr<Process> currentprocess = nullptr;
};

#endif
