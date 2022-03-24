#include <iostream>

#include "OneRunDataAnalizeManager.hh"
#include "Tdistance_function.hh"
#include "Ttof.hh"

ClassImp(OneRunDataAnalizeManager)

OneRunDataAnalizeManager::OneRunDataAnalizeManager()
{
}

OneRunDataAnalizeManager::OneRunDataAnalizeManager(const char* filename)
{
  Setdatafile(filename);
}

void OneRunDataAnalizeManager::Setdatafile(const char* filename)
{
  if(dfile)
    {
      std::cout << "data file is already exist!" << std::endl;
      throw "OneRunDataAnalizeManager::Setdatafile(TFile* datafile)";
    }
  dfile = new TFile(filename);
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  neventdata = wcsimT->GetEntries();
  for(int i = 0; i < neventdata; i++)
    {
      wcsimT->GetEntry(i);
      vncherenkovdigihits.push_back(wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits());
    }
  std::string sfilename = filename;
  onedataparameters = new OneDataParameters();
  onedataparameters->Setpair(sfilename);
  onedataparameters->SetValue();
}

OneRunDataAnalizeManager::~OneRunDataAnalizeManager()
{
  if(wcsimrootevent)
    delete wcsimrootevent;
  if(wcsimrootgeom)
    delete wcsimrootgeom;
  if(dfile)
    delete dfile;
  if(onedataparameters)
    delete onedataparameters;
}

void OneRunDataAnalizeManager::GetEntry(int ievent)
{
  vhitinfo.clear();
  vhitinfo.shrink_to_fit();
  wcsimT->GetEntry(ievent);
  WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(0);
  TLorentzVector vec;
  vec.SetX(wcsimroottrigger->GetVtx(0));
  vec.SetY(wcsimroottrigger->GetVtx(1));
  vec.SetZ(wcsimroottrigger->GetVtx(2));
  vec.SetT((-1)*wcsimroottrigger->GetTriggerTime());
  reconstructdatatrue.Set4Vector(vec);
  TVector3 truedir(wcsimroottrack->GetDir(0),wcsimroottrack->GetDir(1),wcsimroottrack->GetDir(2));
  reconstructdatatrue.Setdirection(truedir);
  for(int j = 0; j < vncherenkovdigihits[ievent]; j++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
      Thitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      vhitinfo.push_back(info);
    }
}

double OneRunDataAnalizeManager::GetEfficiency()
{
  int ntrigger = 0;
  for(int i = 0; i < neventdata; i++)
    {
      if(vncherenkovdigihits[i] != 0)
	{
	  ntrigger++;
	}
    }
  double efficiency = (double)ntrigger/(double)neventdata;
  return efficiency;
}


double OneRunDataAnalizeManager::Gettofnoretrotrue(int ievent,int jhit)
{
  GetEntry(ievent);
  Tdistance_position_pmt tdistance;
  tdistance.SetHitInfo(vhitinfo[jhit]);
  tdistance.SetReconstructdata(reconstructdatatrue);
  Ttof tof;
  tof.SetHitInfo(vhitinfo[jhit]);
  tof.SetReconstructdata(reconstructdatatrue);
  tof.Setdistancefunction(&tdistance);
  double time = tof.returnvalue();
  return time;
}

double OneRunDataAnalizeManager::Gettoferrornoretrotrue(int ievent,int jhit)
{
  GetEntry(ievent);
  Tdistance_position_pmt tdistance;
  tdistance.SetHitInfo(vhitinfo[jhit]);
  tdistance.SetReconstructdata(reconstructdatatrue);
  Ttof tof;
  tof.SetHitInfo(vhitinfo[jhit]);
  tof.SetReconstructdata(reconstructdatatrue);
  tof.Setdistancefunction(&tdistance);
  double time = tof.returnvalue() + wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  return time;
}


double OneRunDataAnalizeManager::Gettofonretrotrue(int ievent,int jhit)
{
  GetEntry(ievent);
  Tdistance_fly_retro tdistance;
  tdistance.SetHitInfo(vhitinfo[jhit]);
  tdistance.SetReconstructdata(reconstructdatatrue);
  Ttof tof;
  tof.SetHitInfo(vhitinfo[jhit]);
  tof.SetReconstructdata(reconstructdatatrue);
  tof.Setdistancefunction(&tdistance);
  double time = tof.returnvalue();
  return time;
}

double OneRunDataAnalizeManager::Gettoferroronretrotrue(int ievent,int jhit)
{
  GetEntry(ievent);
  Tdistance_fly_retro tdistance;
  tdistance.SetHitInfo(vhitinfo[jhit]);
  tdistance.SetReconstructdata(reconstructdatatrue);
  Ttof tof;
  tof.SetHitInfo(vhitinfo[jhit]);
  tof.SetReconstructdata(reconstructdatatrue);
  tof.Setdistancefunction(&tdistance);
  double time = tof.returnvalue() + wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  return time;
}
