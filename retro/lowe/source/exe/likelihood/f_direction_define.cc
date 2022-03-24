// c++ STL
#include <memory>
#include <cstring>
#include <cmath>
#include <iostream>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TVector3.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "config.hh"
#include "runoption.hh"
#include "goodness_data.hh"
#include "WCGoodness_calculate.hh"
#include "distance_pmt.hh"
#include "tof.hh"

int main(){
  Config_f_direction_define config;
  TFile* file = new  TFile(config.infile);
  TTree* wcsimT =(TTree*)file->Get("wcsimT");
  WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile *fout = new TFile(config.outfile,"RECREATE");
  int numbin = 50;
  double fdarkrate = 0.000001*4.2;
  double time_window = 20.;
  double numpmt = wcsimrootgeom->GetWCNumPMT();
  TH1D* h1 = new TH1D("costheta_distribution_N20",";costheta;# of hit",numbin,-1.,1.);
  TH1D* h2 = new TH1D("costheta_distribution_N20_subtructdarkrate",";costehta;# of hit",numbin,-1.,1.);
  TH1D* h3 = new TH1D("cherenkovhit_ratio",";costheta;ratio",numbin,-1.,1.);
  TH1D* h4 = new TH1D("costheta_distribution_N20_onretro","costheta;# of hit",numbin,-1.,1.);
  TH1D* h5 = new TH1D("costheta_distribution_N20_onretro_subtructdarkrate","costheta;# of hit",numbin,-1.,1.);
  int N = wcsimT->GetEntries();
  double darkrate_onebin = fdarkrate * 2. * time_window * N * numpmt / numbin;
  std::cout << darkrate_onebin << std::endl;
  for(int i = 0;i < N; i++){
    wcsimT->GetEntry(i);
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    std::shared_ptr<runoption> option { new runoption(wcsimrootgeom,wcsimroottrigger)};
    std::string s_gfuncname = config.gfuncname;
    option->gfunc = (option->gfuncmap).at(s_gfuncname);
    std::string s_ogfuncname = config.ogfuncname;
    option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
    option->sigma = config.sigma;
    goodness_data data = WCGoodness_calculate(config.range,option);
    double t = data.GetT();
    int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
    for(int k = 0;k < ncherenkovdigihits;k++){
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
      double time = hit->GetT();
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      TVector3 pmt_position(pmtX,pmtY,pmtZ); 
      TVector3 hminusv = pmt_position - config.truevertex;
      TVector3 dvec(1.,0.,0.);
      double theta_dir_i = dvec.Angle(hminusv);
      double d1 = distance_position_pmt(config.truevertex,pmt_position);
      double d2 = distance_retro_pmt(config.truevertex,pmt_position,option);
      double toferror = tof(time - option->offset,d1) - t;
      double toferror_onretro = tof(time - option->offset,2*d2-d1) - t;
      if(toferror > -20. && toferror < 20.){
	h1->Fill(std::cos(theta_dir_i));
	h2->Fill(std::cos(theta_dir_i));
      }
      if(toferror_onretro > -20. && toferror_onretro < 20.){
	h4->Fill(std::cos(theta_dir_i));
	h5->Fill(std::cos(theta_dir_i));
      }
    }
  }
  double first_bin_center = -1.+ 1./numbin;
  double bin_width = 2./numbin;
  double end_bin_center = 1. - 1./numbin;
  for(double bin_value = first_bin_center;bin_value <= end_bin_center;bin_value+=bin_width){
    h2->Fill(bin_value,-darkrate_onebin);
    h5->Fill(bin_value,-darkrate_onebin);
  }
  h3->Divide(h2,h1,1,1);
  fout->Write();
  fout->Close();
  return 0;
}
