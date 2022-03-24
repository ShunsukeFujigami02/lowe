// c++ STL
#include <vector>

// ROOT library
#include <TFile.h>
#include <TTree.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"

int main(){
  Config_N200 config;
  TFile* fin = new TFile(config.infile);
  TTree* wcsimT = (TTree*)fin->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  TFile* fout = new TFile(config.outfile,"recreate");
  TTree* tree = new TTree(config.outtree,"title");
  int nhits_N200;
  int ncherenkovdigihits;
  std::vector<double> vtime;
  tree->Branch("nhits_N200",&nhits_N200);
  tree->Branch("ncherenkovdigihits",&ncherenkovdigihits);
  tree->Branch("time",&vtime);
  int N = wcsimT->GetEntries();
  for(int i = 0;i < N;i++){
    wcsimT->GetEntry(i);
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
    nhits_N200 = 0;
    for(int k = 0;k < ncherenkovdigihits;k++){
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      double time = hit->GetT() - 950.;
      vtime.emplace_back(time);
      if(time > -200. && time < 0){
	nhits_N200++;
      }
    }
    tree->Fill();
    for(int j = 0;j < ncherenkovdigihits;j++){
      vtime.pop_back();
    }
  }
  fout->Write();
  fout->Close();
}
