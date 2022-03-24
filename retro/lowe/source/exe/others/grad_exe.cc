// c++ STL
#include <iostream>
#include <cstring>

// ROOT library
#include <TFile.h>
#include <TTree.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"
#include "runopgrad.hh"
#include "grad_data.hh"

int main(){
  Config_grad config;
  TFile* ffirst = new TFile(config.infile_first);
  TTree* tfirst = (TTree*)ffirst->Get(config.intree_first);
  double max_x;
  double max_y;
  double max_z;
  double max_t;
  double theta;
  double phi;
  tfirst->SetBranchAddress("max_x",&max_x);
  tfirst->SetBranchAddress("max_y",&max_y);
  tfirst->SetBranchAddress("max_z",&max_z);
  tfirst->SetBranchAddress("max_t",&max_t);
  tfirst->SetBranchAddress("theta",&theta);
  tfirst->SetBranchAddress("phi",&phi);
  int nevents = tfirst->GetEntries();
  TFile* fin_d = new TFile(config.infile_data);
  TTree* wcsimGeoT = (TTree*)fin_d->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  runopgrad::wcsimrootgeom = wcsimrootgeom;
  wcsimGeoT->GetEntry(0);
  TTree* wcsimT = (TTree*)fin_d->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  TFile* fout = new TFile(config.outfile,"RECREATE");
  TTree* tree = new TTree(config.outtree,"title");
  double x_final;
  double y_final;
  double z_final;
  double t_final;
  double theta_final;
  double costheta_final;
  double phi_final;
  tree->Branch("x",&x_final);
  tree->Branch("y",&y_final);
  tree->Branch("z",&z_final);
  tree->Branch("t",&t_final);
  tree->Branch("theta",&theta_final);
  tree->Branch("costheta",&costheta_final);
  tree->Branch("phi",&phi_final);
  for(int i = 0;i < nevents;i++)
    {
      tfirst->GetEntry(i);
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      runopgrad::wcsimroottrigger = wcsimroottrigger;
      grad_data first(max_x,max_y,max_z,max_t,theta,phi);
      grad_data final = runopgrad::loopfunc(first);
      x_final = final.X();
      y_final = final.Y();
      z_final = final.Z();
      t_final = final.T();
      theta_final = final.Theta();
      costheta_final = final.CosTheta();
      tree->Fill();
    }
  fout->Write();
  fout->Close();
}
