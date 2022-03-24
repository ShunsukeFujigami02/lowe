#ifndef MINIMIZE6DIMMANAGER_HH
#define MINIMIZE6DIMMANAGER_HH

// ROOT library
#include <TFile.h>
#include <TTree.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self
#include "TReconstructdata.hh"
#include "ProcessManager.hh"

class Minimize6dimManager : public ProcessManager
{
public:
  Minimize6dimManager() = delete;
  Minimize6dimManager(const char* infilelikelihood);
  virtual ~Minimize6dimManager();
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
  
private:
  TFile* dfile = nullptr;
  TTree* wcsimT = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  TFile* gfile = nullptr;
  TTree* goodnessT = nullptr;
  TReconstructdata* greconstructdata = nullptr;
  int Nevents;
  TFile* lfile = nullptr;
  TTree* likelihoodT = nullptr;
  TReconstructdata* lreconstructdata = nullptr;
};

#endif
