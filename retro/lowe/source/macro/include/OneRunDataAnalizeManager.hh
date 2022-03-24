#ifndef ONERUNDATAANALIZEMANAGER_HH
#define ONERUNDATAANALIZEMANAGER_HH

// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self
#include "TReconstructdata.hh"
#include "Thitinfo.hh"
#include "constants.hh"
#include "OneDataParameters.hh"

class OneRunDataAnalizeManager : public TObject
{
public:
  OneRunDataAnalizeManager();
  OneRunDataAnalizeManager(const char* filename);
  void Setdatafile(const char* filename);
  virtual ~OneRunDataAnalizeManager();
  void GetEntry(int ievent);
  double Getxvtx(int ievent)
  {
    wcsimT->GetEntry(ievent);
    return wcsimrootevent->GetTrigger(0)->GetVtx(0);
  }
  double Getyvtx(int ievent)
  {
    wcsimT->GetEntry(ievent);
    return wcsimrootevent->GetTrigger(0)->GetVtx(1);
  }
  double Getzvtx(int ievent)
  {
    wcsimT->GetEntry(ievent);
    return wcsimrootevent->GetTrigger(0)->GetVtx(2);
  }
  double Getxdir(int ievent)
  {
    wcsimT->GetEntry(ievent);
    WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    return wcsimroottrack->GetDir(0);
  }
  double Getydir(int ievent)
  {
    wcsimT->GetEntry(ievent);
    WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    return wcsimroottrack->GetDir(1);
  }
  double Getzdir(int ievent)
  {
    wcsimT->GetEntry(ievent);
    WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    return wcsimroottrack->GetDir(2);
  }
  TVector3 Getdirection(int ievent)
  {
    wcsimT->GetEntry(ievent);
    WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    TVector3 vec(wcsimroottrack->GetDir(0),wcsimroottrack->GetDir(1),wcsimroottrack->GetDir(2));
    return vec;
  }
  
  double GetTriggerTime(int ievent)
  {
    wcsimT->GetEntry(ievent);
    return wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  }
  double GetEfficiency();
  double Gethittimeraw(int ievent,int jhit)
  {
    GetEntry(ievent);
    return vhitinfo.at(jhit).HitTime();
  }
  double Gettofnoretrotrue(int ievent,int jhit);
  double Gettofonretrotrue(int ievent,int jhit);
  double Gettoferrornoretrotrue(int ievent,int jhit);
  double Gettoferroronretrotrue(int ievent,int jhit);
  double Gethittimetrue(int ievent,int jhit)
  {
    wcsimT->GetEntry(ievent);
    return vhitinfo.at(jhit).HitTime() - offset + wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  }

  OneDataParameters* GetDataParameters()
  {
    return onedataparameters;
  }
  int ncherenkovdigihits;
  int Getncherenkovdigihits(int ievent)
  {
    return vncherenkovdigihits[ievent];
  }
  TReconstructdata reconstructdatatrue;
  std::vector<Thitinfo> vhitinfo;
  std::vector<int> vncherenkovdigihits;
private:
  TFile* dfile = nullptr;
  TTree* wcsimT;
  TTree* wcsimGeoT;
  WCSimRootEvent* wcsimrootevent;
  WCSimRootGeom* wcsimrootgeom;
  int neventdata;
  OneDataParameters* onedataparameters = nullptr;
public:
  ClassDef(OneRunDataAnalizeManager,1)
};

#endif
