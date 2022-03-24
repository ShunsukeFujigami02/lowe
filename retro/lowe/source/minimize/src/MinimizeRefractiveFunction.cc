#include <iostream>
#include <memory>
#include <cmath>
#include "MinimizeRefractiveFunction.hh"
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
#include <TH2D.h>
#include <TRint.h>
#include <TF1.h>
#include <cstring>
#include "distance_function.hh"
#include "tof.hh"

MinimizeRefractiveFunction::MinimizeRefractiveFunction(const char* infile)
{
  file = new TFile(infile);
  wcsimT = (TTree*)file->Get("wcsimT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT = (TTree*)file->Get("wcsimGeoT");
  wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
}

MinimizeRefractiveFunction::~MinimizeRefractiveFunction()
{
  delete file;
  delete wcsimrootevent;
  delete wcsimrootgeom;
}

double MinimizeRefractiveFunction::returnvalue(const double* a)
{
  TH2D* h1 = new TH2D("hminimize","",100,0.,3000.,100,-40.,40.);
  TH2D* h2 = new TH2D("hlog","",100,0.,3000.,100,-40.,40.);
  int nevent = wcsimT->GetEntries();
  for(int i = 0;i < nevent;++i)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      CLHEP::HepLorentzVector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2),-wcsimroottrigger->GetTriggerTime());
      Reconstructdata datatrue;
      datatrue.Set4Vector(vectrue);
      int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
      for(int j = 0;j<ncherenkovdigihits;++j){
	WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
	hitinfo info;
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver3>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	h1->Fill(d_p_p->returnvalue(),ftof->returnvalue() - vectrue.t());
      }
    }
  for(int i = 1;i < h1->GetXaxis()->GetNbins()+1;i++)
    {
      double max = 0.;
      int maxj = 1;
      for(int j = 1;j < h1->GetYaxis()->GetNbins()+1;j++)
	{
	  double binvalue = h1->GetBinContent(i,j);
	  if(max < binvalue)
	    {
	      max = binvalue;
	      maxj = j;
	    }
	}
      if(max > 10.)
	{
	  h2->Fill(h1->GetXaxis()->GetBinCenter(i),h1->GetYaxis()->GetBinCenter(maxj));
	}
    }
  TF1* f1 = new TF1("f1","pol1",0.,3000.);
  h2->Fit(f1,"R");
  double slope = f1->GetParameter(1);
  //  double sigma = 0.00000001;
  delete h1;
  delete h2;
  delete f1;
  return slope;
}

std::vector<double> MinimizeRefractiveFunction::returnmeanandpeak(const double* a)
{
  TH1D* h1 = new TH1D("htof","",400,-40.,40.);
  TH1D* h2 = new TH1D("htoflog","",400,-40.,40.);
  int nevent = wcsimT->GetEntries();
  for(int i = 0;i < nevent;++i)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
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
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver3>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	h1->Fill(ftof->returnvalue() - vectrue.t());
      }
    }
  for(int i = 1; i < h1->GetXaxis()->GetNbins() + 1;i++)
    {
      if(h1->GetBinContent(i) != 0)
	h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
    }
  double meantemp1 = h1->GetXaxis()->GetBinCenter(h1->GetMaximumBin());
  std::cout << "meantemp1 = " << meantemp1 << std::endl;
  TF1* f1 = new TF1("f1","gaus",meantemp1 - 10.,meantemp1 + 10.);
  h1->Fit(f1,"n");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 10.,meantemp + 10.);
  h1->Fit(f2,"n");
  double mean = f2->GetParameter(1);
  double width = f2->GetParameter(2);
  std::vector<double> returnvalue;
  returnvalue.push_back(mean);
  returnvalue.push_back(width);
  delete h1;
  delete h2;
  delete f2;
  delete f1;
  return returnvalue;
}

void MinimizeRefractiveFunction::Filltofhist(TH1D* h1,TH1D* hlog,const double* a)
{
  int nevent = wcsimT->GetEntries();
  for(int i = 0;i < nevent;++i)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
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
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver3>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	h1->Fill(ftof->returnvalue() - vectrue.t());
      }
    }
  for(int i = 1; i < h1->GetXaxis()->GetNbins() + 1;i++)
    {
      if(h1->GetBinContent(i) != 0)
	hlog->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
    }
}
