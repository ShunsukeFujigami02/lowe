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
#include "distance_function.hh"
#include "tof.hh"
#include "theta_dir_i.hh"
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
  TTree *tree = new TTree("toferrorT","title");
  std::vector<double> tof_nretro;
  std::vector<double> tof_onretro;
  std::vector<double> distance_noretro;
  std::vector<double> distance_onretro;
  std::vector<double> tof_nretrover2;
  std::vector<double> tof_onretrover2;
  std::vector<double> costheta_i;
  std::vector<double> CylLoc;
  std::vector<double> PMTacceptancecosangle;
  tree->Branch("tof_nretro",&tof_nretro);
  tree->Branch("tof_onretro",&tof_onretro);
  tree->Branch("distance_noretro",&distance_noretro);
  tree->Branch("distance_onretro",&distance_onretro);
  tree->Branch("costheta_i",&costheta_i);
  tree->Branch("CylLoc",&CylLoc);
  tree->Branch("PMTacceptancecosangle",&PMTacceptancecosangle);
  int n_event = wcsimT->GetEntries();
  std::cout << Getdouble("NWATER") << std::endl;
  double doffset = 1.95775611238980325e+01;
  for(int i = 0;i<n_event;++i){
    wcsimT->GetEntry(i);
    WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    CLHEP::HepLorentzVector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2),-wcsimroottrigger->GetTriggerTime());
    WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(0);
    CLHEP::Hep3Vector dirtrue(wcsimroottrack->GetDir(0),wcsimroottrack->GetDir(1),wcsimroottrack->GetDir(2));
    Reconstructdata datatrue;
    datatrue.Set4Vector(vectrue);
    datatrue.Setdirection(dirtrue);
    int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
    for(int j = 0;j<ncherenkovdigihits;++j){
      WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
      hitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
      CylLoc.emplace_back(pmt.GetCylLoc());
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->SetHitInfo(info);
      ftof->SetReconstructdata(datatrue);
      std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt>();
      d_p_p->SetHitInfo(info);
      d_p_p->SetReconstructdata(datatrue);
      distance_noretro.emplace_back(d_p_p->returnvalue() - doffset);
      ftof->Setdistancefunction(d_p_p);
      ftof->Setnwater(Getdouble("NWATER"));
      tof_nretro.emplace_back(ftof->returnvalue() - vectrue.t());
      std::shared_ptr<tof> ftof2 = std::make_shared<tof>();
      ftof2->SetHitInfo(info);
      ftof2->SetReconstructdata(datatrue);
      std::shared_ptr<distance_function> d_f_r = std::make_shared<distance_fly_retro>();
      d_f_r->SetHitInfo(info);
      d_f_r->SetReconstructdata(datatrue);
      distance_onretro.emplace_back(d_f_r->returnvalue() - doffset);
      ftof2->Setdistancefunction(d_f_r);
      ftof2->Setnwater(Getdouble("NWATER"));
      tof_onretro.emplace_back(ftof2->returnvalue() - vectrue.t());
      std::shared_ptr<theta_dir_i> t_i_f = std::make_shared<theta_dir_i>();
      t_i_f->SetHitInfo(info);
      t_i_f->SetReconstructdata(datatrue);
      costheta_i.emplace_back(std::cos(t_i_f->returnvalue()));
      CLHEP::Hep3Vector truepos(vectrue.x(),vectrue.y(),vectrue.z());
      CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
      CLHEP::Hep3Vector pmtorientation(pmt.GetOrientation(0),pmt.GetOrientation(1),pmt.GetOrientation(2));
      PMTacceptancecosangle.emplace_back(std::cos(pmtorientation.angle(truepos - pmtposition)));
      
    }
    tree->Fill();
    tof_nretro.clear();
    tof_onretro.clear();
    distance_noretro.clear();
    distance_onretro.clear();
    costheta_i.clear();
    CylLoc.clear();
    PMTacceptancecosangle.clear();
  }
  fout->Write();
  fout->Close();
}
