#ifndef GOODNESSVERBOSEMANAGER_HH
#define GOODNESSVERBOSEMANAGER_HH

// ROOT library
#include <TFile.h>
#include <TTree.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "ProcessManager.hh"
#include "TReconstructdata.hh"

class GoodnessVerboseManager : public ProcessManager
{
public:
  GoodnessVerboseManager() = delete;
  GoodnessVerboseManager(const char* infiledata,const char* infilegoodness);
  virtual ~GoodnessVerboseManager();
  void Doprocess()
  {
  }
  void ProcessOneEvent(int i);
  WCSimRootEvent* GetWCSimRootEvent()
  {
    return wcsimrootevent;
  }
  WCSimRootGeom* GetWCSimRootGeom()
  {
    return wcsimrootgeom;
  }
  TReconstructdata* GetTReconstructdata()
  {
    return reconstructdataverbose;
  }
  
private:
  TFile* dfile = nullptr;
  TTree* wcsimT = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  TFile* gfile = nullptr;
  TTree* goodnessT = nullptr;
  TReconstructdata* reconstructdata = nullptr;
  TReconstructdata* reconstructdataverbose = nullptr;
  TBranch* branch = nullptr;
  int Nevents;
};

#endif
