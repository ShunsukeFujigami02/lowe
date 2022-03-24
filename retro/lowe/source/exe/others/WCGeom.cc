#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include "WCSimRootGeom.hh"
#include "constants2.h"
#include "distance_position_pmt.h"
#include "distance_retro_pmt.h"
void WCGeom()
{
  TFile *file = new TFile("data/wcsim_on_retro_electron_5MeV_10000event.root");
  TTree *wcsimGeoT = (TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile *fout = new TFile("analize/geom_SK.root","recreate");
  TTree *tree = new TTree("geom_SK","title");
  int tubeId;
  double pmtX;
  double pmtY;
  double pmtZ;
  int CylLoc;
  double WCradius;
  double WClength;
  double WCPMTradius;
  double d1;
  double d2;
  tree->Branch("tubeId",&tubeId);
  tree->Branch("pmtX",&pmtX);
  tree->Branch("pmtY",&pmtY);
  tree->Branch("pmtZ",&pmtZ);
  tree->Branch("CylLoc",&CylLoc);
  tree->Branch("WCradius",&WCradius);
  tree->Branch("WClength",&WClength);
  tree->Branch("WCPMTradius",&WCPMTradius);
  tree->Branch("d1",&d1);
  tree->Branch("d2",&d2);
  int wcnumpmt = wcsimrootgeom->GetWCNumPMT();
  constants2(wcsimrootgeom,WCradius,WClength);
  double half_WClength = WClength/2;
  double position[3] = {0.,0.,0.};
  WCPMTradius = wcsimrootgeom->GetWCPMTRadius();
  int CylLoc_reflect;
  for(int i = 0;i<wcnumpmt;++i){
    tubeId = i;
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(i);
    pmtX = pmt.GetPosition(0);
    pmtY = pmt.GetPosition(1);
    pmtZ = pmt.GetPosition(2);
    CylLoc = pmt.GetCylLoc();
    d1 = distance_position_pmt(position,pmtX,pmtY,pmtZ);
    d2 = distance_retro_pmt(position,pmtX,pmtY,pmtZ,WCradius,half_WClength,CylLoc_reflect);
    tree->Fill();
  }
  fout->Write();
  fout->Close();
}

int main()
{
  WCGeom();
  return 0;
}
