// c++ STL
#include <cmath>
#include <iostream>
// ROOT library
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <TPave.h>
#include <TArc.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "eventdisplay.hh"
#include "constants.hh"

ClassImp(Eventdisplay)

Eventdisplay::Eventdisplay(const char* infile,char* name,char* title,int nevent,int xbin,int ybin):TNamed(name,title)
{
  Set(infile,nevent,xbin,ybin);
}

void Eventdisplay::Set(const char* infile,int nevent,int xbin,int ybin){
  TFile* file = new TFile(infile);
  TTree* wcsimT = (TTree*)file->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  WCradius = wcsimrootgeom->GetWCCylRadius();
  WClength = wcsimrootgeom->GetWCCylLength();
  a1 = TArc(0.,WCradius + WClength/2.,WCradius);
  a2 = TArc(0.,-WCradius - WClength/2.,WCradius);
  p1 = TPave(-PI*WCradius,-WClength/2.,PI*WCradius,WClength/2.);
  a1.SetFillStyle(0);
  a2.SetFillStyle(0);
  p1.SetFillStyle(0);
  hall.SetNameTitle("hall","all pmt");
  hall.SetBins(xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  hcharge.SetNameTitle("hcharge","eventdisplay of charge");
  hcharge.SetBins(xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  htime.SetNameTitle("htime","eventdisplay of time");
  htime.SetBins(xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  hhit.SetNameTitle("hhit","eventdisplay of hit");
  hhit.SetBins(xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  wcsimT->GetEntry(nevent);
  int NumPMT = wcsimrootgeom->GetWCNumPMT();
  for(int iall = 0;iall < NumPMT;++iall){
    WCSimRootPMT pmt_all = wcsimrootgeom->GetPMT(iall);
    double pmtX_all = pmt_all.GetPosition(0);
    double pmtY_all = pmt_all.GetPosition(1);
    double pmtZ_all = pmt_all.GetPosition(2);
    double pmtS_all = -WCradius*atan2(pmtY_all,pmtX_all);
    if((pmt_all.GetCylLoc()) == 0){
      hall.Fill(-pmtY_all,-(pmtX_all)+WClength/2+WCradius);
    }
    else if((pmt_all.GetCylLoc()) == 1){
      hall.Fill(pmtS_all,pmtZ_all);
    }
    else{
      hall.Fill(-pmtY_all,pmtX_all-WClength/2-WCradius);
    }
  }
  WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0;k < ncherenkovdigihits;++k){
    WCSimRootCherenkovDigiHit *Digihit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
    double hittime = Digihit->GetT();
    double hitcharge = Digihit->GetQ();
    int tubeId = Digihit->GetTubeId();
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmtposition = TVector3(pmtX,pmtY,pmtZ);
    double pmtS = -WCradius*std::atan2(pmtY,pmtX);
    if((pmt.GetCylLoc()) == 0){
      hhit.Fill(-pmtY,-pmtX+WClength/2+WCradius);
      Gethcharge()->Fill(-pmtY,-pmtX+WClength/2+WCradius,hitcharge);
      htime.Fill(-pmtY,-pmtX+WClength/2+WCradius,hittime);
    }
    if((pmt.GetCylLoc()) == 1){
      hhit.Fill(pmtS,pmtZ);
      Gethcharge()->Fill(pmtS,pmtZ,hitcharge);
      htime.Fill(pmtS,pmtZ,hittime);
    }
    if((pmt.GetCylLoc()) == 2){
      hhit.Fill(-pmtY,pmtX-WClength/2-WCradius);
      Gethcharge()->Fill(-pmtY,pmtX-WClength/2-WCradius,hitcharge);
      htime.Fill(-pmtY,pmtX-WClength/2-WCradius,hittime);
    }
  }
  delete wcsimrootevent;
  delete wcsimrootgeom;
  file->Close();
}
  

Eventdisplay::~Eventdisplay()
{}

void Eventdisplay::Drawall(Option_t* option)
{
  hall.Draw(option);
  a1.Draw("same");
  a2.Draw("same");
  p1.Draw("same");
}

void Eventdisplay::Drawcharge(Option_t* option)
{
  hcharge.Draw(option);
  a1.Draw("same");
  a2.Draw("same");
  p1.Draw("same");
}

void Eventdisplay::Drawtime(Option_t* option)
{
  htime.Draw(option);
  a1.Draw("same");
  a2.Draw("same");
  p1.Draw("same");
}

void Eventdisplay::Drawhit(Option_t* option)
{
  hhit.Draw(option);
  a1.Draw("same");
  a2.Draw("same");
  p1.Draw("same");
}

Bool_t Eventdisplay::Add(Eventdisplay* eventdisplay1,Eventdisplay* eventdisplay2,Double_t c1,Double_t c2){
  Bool_t kcharge = hcharge.Add(eventdisplay1->Gethcharge(),eventdisplay2->Gethcharge(),c1,c2);
  Bool_t ktime = htime.Add(eventdisplay1->Gethtime(),eventdisplay2->Gethtime(),c1,c2);
  Bool_t khit = hhit.Add(eventdisplay1->Gethhit(),eventdisplay2->Gethhit(),c1,c2);
  return (kcharge && ktime && khit);
}

Bool_t Eventdisplay::Add(Eventdisplay* eventdisplay1,Double_t c1){
  Bool_t kcharge = hcharge.Add(eventdisplay1->Gethcharge(),c1);
  Bool_t ktime = htime.Add(eventdisplay1->Gethtime(),c1);
  Bool_t khit = hhit.Add(eventdisplay1->Gethhit(),c1);
  return (kcharge && ktime && khit);
}

Eventdisplay* Eventdisplay::Sum(const char* infile,char* name,char* title,int nevents,int xbin,int ybin){
  TFile* file = new TFile(infile);
  TTree* wcsimT = (TTree*)file->Get("wcsimT");
  int N = wcsimT->GetEntries();
  if(N < nevents || nevents < 1){
    std::cout << "Error: invalid number of events!" << std::endl;
    throw "Eventdisplay* Eventdisplay::Sum(const char*,char*,char*,int,int,int)";
  }
  file->Close();
  Eventdisplay* edis = new Eventdisplay(infile,name,title,0,xbin,ybin);
  Eventdisplay* edis2 = new Eventdisplay(name,title);
  for(int ientry = 1;ientry < nevents; ++ientry){
    edis2->Set(infile,ientry,xbin,ybin);
    bool a = edis->Add(edis2);
    if(!a){
      throw "Eventdisplay* Eventdisplay::Sum(const char*,char*,char*,int,int,int)";
    }
  }
  return edis;
}
			  

