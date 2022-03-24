#ifndef GOODNESS_MANAGER_HH
#define GOODNESS_MANAGER_HH

// ROOT library
#include <TFile.h>
#include <TTree.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "GoodnessParameters.hh"
#include "GoodnessRunAction.hh"
#include "GoodnessRun.hh"
#include "GoodnessEventManager.hh"
#include "GoodnessEvent.hh"
class GoodnessManager
{
public:
  static GoodnessManager* GetGoodnessManager();
private:
  static GoodnessManager* fgoodnessmanager;
public:
  GoodnessManager() = delete;
  GoodnessManager(const char* infile);
  virtual ~GoodnessManager();
  void Run(int Nevent);
  void SetParameters();
  void ProcessOneEvent(int i_event);
  GoodnessParameters* GetGoodnessParameters(){return goodnessparameters;}
  void SetGoodnessParameters(GoodnessParameters* parameters){goodnessparameters = parameters;}
  void SetGoodnessRunAction(GoodnessRunAction* goodnessrunaction_in)
  {
    goodnessrunaction = goodnessrunaction_in;
  }
  void SetGoodnessEventAction(GoodnessEventAction* goodnesseventaction_in);
  WCSimRootEvent* GetWCSimRootEvent(){return wcsimrootevent;}
  WCSimRootGeom* GetWCSimRootGeom(){return wcsimrootgeom;}
private:
  TFile* file = nullptr;
  TTree* wcsimT = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  GoodnessRunAction* goodnessrunaction = nullptr;
  GoodnessEventAction* goodnesseventaction = nullptr;
  GoodnessRun* goodnessrun = nullptr;
  GoodnessEvent* currentevent = nullptr;
  GoodnessEventManager goodnesseventmanager;
  GoodnessParameters* goodnessparameters = nullptr;
  int nevent;
  
};

#endif
