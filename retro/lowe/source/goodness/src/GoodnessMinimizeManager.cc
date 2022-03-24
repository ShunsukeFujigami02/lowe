// c++ STL
#include <iostream>

// self
#include "GoodnessMinimizeManager.hh"
#include "MyString.hh"

GoodnessMinimizeManager::GoodnessMinimizeManager(const char* infilelikelihood)
  :ProcessManager()
{
  lfile = new TFile(infilelikelihood);
  likelihoodT = (TTree*)lfile->Get("likelihoodT");
  MyString* infiledataname = (MyString*)lfile->Get("infiledataname");
  MyString* infilegoodnessname = (MyString*)lfile->Get("infilegoodnessname");
  lreconstructdata = new TReconstructdata();
  likelihoodT->SetBranchAddress("reconstructdatalikelihood",&lreconstructdata);
  Nevents = likelihoodT->GetEntries();
  gfile = new TFile(infilegoodnessname->Getstring().c_str());
  goodnessT = (TTree*)gfile->Get("goodnessT");
  greconstructdata = new TReconstructdata();
  goodnessT->SetBranchAddress("reconstructdata",&greconstructdata);
  dfile = new TFile(infiledataname->Getstring().c_str());
  
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  std::cout << "input file data is below" << std::endl;
  dfile->Print();
  gfile->Print();
  lfile->Print();
  std::cout << Nevents << "event exist" << std::endl;
}


GoodnessMinimizeManager::~GoodnessMinimizeManager()
{
  if(dfile)
    delete dfile;
  if(wcsimrootevent)
    delete wcsimrootevent;
  if(wcsimrootgeom)
    delete wcsimrootgeom;
  if(gfile)
    delete gfile;
  if(greconstructdata)
    delete greconstructdata;
  if(lfile)
    delete lfile;
  if(lreconstructdata)
    delete lreconstructdata;
}

void GoodnessMinimizeManager::ProcessOneEvent(int i)
{
  wcsimT->GetEntry(i);
  goodnessT->GetEntry(i);
  likelihoodT->GetEntry(i);
  double x = greconstructdata->Get4Vector().X();
  double y = greconstructdata->Get4Vector().Y();
  double z = greconstructdata->Get4Vector().Z();
  double t = greconstructdata->Get4Vector().T();
  CLHEP::HepLorentzVector fitted4vector;
  fitted4vector.set(x,y,z,t);
  currentprocess->Setfitted4Vector(fitted4vector);
  double theta = lreconstructdata->Getdirection().Theta();
  double phi = lreconstructdata->Getdirection().Phi();
  CLHEP::Hep3Vector fitteddirection;
  fitteddirection.setRThetaPhi(1.,theta,phi);
  currentprocess->SetCurrent3Direction(fitteddirection);
  nextmanager->ProcessOne(currentprocess);
}

