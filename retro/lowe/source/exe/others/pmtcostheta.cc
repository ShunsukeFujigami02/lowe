#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "theta_i_func.hh"
#include "config.hh"
int main()
{
  char* infile = Getchar("INFILE");;
  TFile*file = new TFile(infile);
  TTree* wcsimT =(TTree*)file->Get("wcsimT");
  WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile *fout = new TFile(Getchar("OUTFILE"),"RECREATE");
  TTree *tree = new TTree("pmtcosthetaT","title");
  std::vector<double> pmtcostheta;
  tree->Branch("pmtcostheta",&pmtcostheta);
  int n_event = wcsimT->GetEntries();
  for(int i = 0;i<n_event;++i){
    wcsimT->GetEntry(i);
    WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    CLHEP::HepLorentzVector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2),-wcsimroottrigger->GetTriggerTime());
    Reconstructdata datatrue;
    datatrue.Set4Vector(vectrue);
    int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
    for(int j = 0;j<ncherenkovdigihits;++j){
      WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
      hitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      std::shared_ptr<theta_i_func> ftheta_i_func = std::make_shared<theta_i_func>();
      ftheta_i_func->SetHitInfo(info);
      ftheta_i_func->SetReconstructdata(datatrue);
      pmtcostheta.push_back(std::cos(ftheta_i_func->returnvalue()));
    }
    tree->Fill();
    pmtcostheta.clear();
  }
  fout->Write();
  fout->Close();
}
