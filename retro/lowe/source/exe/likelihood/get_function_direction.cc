// c++ STL
#include <vector>
#include <cmath>

// ROOT library
#include <TFile.h>
#include <TTree.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"
#include "get_function_direction_func.hh"

int main(){
  Config_func_dir config;
  TFile* file = new TFile(config.infile);
  TTree* wcsimT = (TTree*)file->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  TTree* wcsimGeoT = (TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile* fout = new TFile(config.outfile,"recreate");
  TTree* tree = new TTree(config.outtree,"title");
  TTree* vtree = new TTree(config.outtree_v,"title");
  double theta_i;
  double costheta_i;
  std::vector<double> vtheta_i;
  std::vector<double> vcostheta_i;
  tree->Branch("theta_i",&theta_i);
  tree->Branch("costheta_i",&costheta_i);
  vtree->Branch("vtheta_i",&vtheta_i);
  vtree->Branch("vcostheta_i",&vcostheta_i);
  int N = wcsimT->GetEntries();
  for(int i = 0;i < N;i++){
    wcsimT->GetEntry(i);
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
    for(int k = 0;k < ncherenkovdigihits;k++){
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((wcsimroottrigger->GetCherenkovDigiHits())->At(k));
      theta_i = gettheta_i(hit,wcsimrootgeom,config.truevertex,config.truedirection);
      costheta_i = std::cos(theta_i);
      tree->Fill();
    }
    setvtheta_i(vtheta_i,wcsimroottrigger,wcsimrootgeom,config.truevertex,config.truedirection);
    setvcostheta_i(vcostheta_i,wcsimroottrigger,wcsimrootgeom,config.truevertex,config.truedirection);
    vtree->Fill();
  }
  fout->Write();
  fout->Close();
}
