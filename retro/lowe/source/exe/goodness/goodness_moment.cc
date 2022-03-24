// c++ STL
#include <vector>
#include <cstring>
#include <iostream>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"
#include "runoption.hh"

int main(){
  Config_goodness_moment config;
  std::string nameretro = config.name_retro;
  runoption::sigma = config.sigma;
  TFile* fin_g = new TFile(config.infile_goodness);
  TTree* tin = (TTree*)fin_g->Get(config.intree);
  std::cout << tin->GetEntries() << std::endl;
  int ncherenkovdigihits_in;
  double max_goodness_in;
  double max_goodness_noretro_in;
  double max_goodness_onretro_in;
  double max_x_in;
  double max_y_in;
  double max_z_in;
  double max_t_in;
  tin->SetBranchAddress("max_goodness",&max_goodness_in);
  std::cout << "0.3" << std::endl;
  tin->SetBranchAddress("ncherenkovdigihits",&ncherenkovdigihits_in);
  tin->SetBranchAddress("max_goodness_noretro",&max_goodness_noretro_in);
  tin->SetBranchAddress("max_goodness_onretro",&max_goodness_onretro_in);
  tin->SetBranchAddress("max_x",&max_x_in);
  tin->SetBranchAddress("max_y",&max_y_in);
  tin->SetBranchAddress("max_z",&max_z_in);
  tin->SetBranchAddress("max_t",&max_t_in);
  std::cout << "0.4" << std::endl;
  TFile* fin_d = new TFile(config.infile_data);
  TTree* wcsimT = (TTree*)fin_d->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree* wcsimGeoT = (TTree*)fin_d->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  runoption::wcsimrootgeom = wcsimrootgeom;
  TFile* fout = new TFile(config.outfile,"RECREATE");
  TTree* tree = new TTree(config.outtree,"title");
  int ncherenkovdigihits_out;
  double max_goodness_out;
  double max_goodness_noretro_out;
  double max_goodness_onretro_out;
  double max_x_out;
  double max_y_out;
  double max_z_out;
  double max_t_out;
  std::vector<int> vhitTUBEID;
  std::vector<int> vhitdirorref;
  std::vector<double> vhitgoodness;
  double costheta;
  double phi;
  tree->Branch("ncherenkovdigihits",&ncherenkovdigihits_out);
  tree->Branch("max_goodness",&max_goodness_out);
  tree->Branch("max_goodness_noretro",&max_goodness_noretro_out);
  tree->Branch("max_goodness_onretro",&max_goodness_onretro_out);
  tree->Branch("max_x",&max_x_out);
  tree->Branch("max_y",&max_y_out);
  tree->Branch("max_z",&max_z_out);
  tree->Branch("max_t",&max_t_out);
  tree->Branch("vhitTUBEID",&vhitTUBEID);
  tree->Branch("vhitdirorref",&vhitdirorref);
  tree->Branch("vhitgoodness",&vhitgoodness);
  tree->Branch("costheta",&costheta);
  tree->Branch("phi",&phi);
  int N = tin->GetEntries();
  for(int i = 0;i < N;i++){
    tin->GetEntry(i);
    wcsimT->GetEntry(i);
    TLorentzVector vector(max_x_in,max_y_in,max_z_in,max_t_in);
    TVector3 vertex(max_x_in,max_y_in,max_z_in);
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    runoption::wcsimroottrigger = wcsimroottrigger;
    for( int k = 0;k < ncherenkovdigihits_in ;++k){
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((runoption::wcsimroottrigger->GetCherenkovDigiHits())->At(k));
      double time = hit->GetT();
      int tubeId = hit->GetTubeId();
      vhitTUBEID.push_back(tubeId);
      WCSimRootPMT pmt = runoption::wcsimrootgeom->GetPMT(tubeId-1);
      TVector3 pmt_position(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
      if(nameretro == "on"){
	vhitdirorref.push_back(dirorref(vector,pmt_position,time));
	vhitgoodness.push_back(one_goodness_compare(vector,pmt_position,time));
      }
      else{
	vhitdirorref.push_back(0);
	vhitgoodness.push_back(one_goodness_no_retro(vector,pmt_position,time));
      }
    }
    auto vhitTUBEID_iter = vhitTUBEID.begin();
    auto vhitgoodness_iter = vhitgoodness.begin();
    int l = 0;
    TVector3 sum(0.,0.,0.);
    double goodnesssum = 0.;
    for(auto vhitdirorref_iter = vhitdirorref.begin();vhitdirorref_iter != vhitdirorref.end();vhitdirorref_iter++,vhitTUBEID_iter++,vhitgoodness_iter++,l++){
      if(*vhitdirorref_iter == 0){
	WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((runoption::wcsimroottrigger->GetCherenkovDigiHits())->At(l));
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = runoption::wcsimrootgeom->GetPMT(tubeId-1);
	TVector3 pmt_position(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
	sum += ((*vhitgoodness_iter)*pmt_position);
	goodnesssum += (*vhitgoodness_iter);
      }
    }
    TVector3 hitcenter(sum.X()/goodnesssum,sum.Y()/goodnesssum,sum.Z()/goodnesssum);
    TVector3 moment = hitcenter - vertex;
    costheta = moment.CosTheta();
    phi = moment.Phi();
    ncherenkovdigihits_out = ncherenkovdigihits_in;
    max_goodness_out = max_goodness_in;
    max_goodness_noretro_out = max_goodness_noretro_in;
    max_goodness_onretro_out = max_goodness_onretro_in;
    max_x_out = max_x_in;
    max_y_out = max_y_in;
    max_z_out = max_z_in;
    max_t_out = max_t_in;
    tree->Fill();
    for(int l = 0;l < ncherenkovdigihits_in ;++l){
      vhitdirorref.pop_back();
      vhitTUBEID.pop_back();
      vhitgoodness.pop_back();
    }
  }
  fout->Write();
  fout->Close();
  return 0;
}
