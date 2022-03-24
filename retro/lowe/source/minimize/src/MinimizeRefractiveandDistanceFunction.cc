#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include "MinimizeRefractiveandDistanceFunction.hh"
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
#include <TH2D.h>
#include <TRint.h>
#include <TF1.h>
#include <cstring>
#include "distance_function.hh"
#include "tof.hh"
#include "theta_dir_i.hh"
#include <TFitResult.h>

MinimizeRefractiveandDistanceFunction::MinimizeRefractiveandDistanceFunction(const char* infile)
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

MinimizeRefractiveandDistanceFunction::~MinimizeRefractiveandDistanceFunction()
{
  delete file;
  delete wcsimrootevent;
  delete wcsimrootgeom;
}

double MinimizeRefractiveandDistanceFunction::returnpeakmean(const double* a)
{
  TH1D* h1 = new TH1D("htof","",400,-40.,40.);
  TH1D* h2 = new TH1D("htoflog","",400,-40.,40.);
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
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver2>();
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
  TF1* f1 = new TF1("f1","gaus",-10.,10.);
  h2->Fit(f1,"Rn");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn");
  double mean = f2->GetParameter(1);
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return mean;
}

double MinimizeRefractiveandDistanceFunction::returnpeakwidth(const double* a)
{
  TH1D* h1 = new TH1D("htof","",400,-40.,40.);
  TH1D* h2 = new TH1D("htoflog","",400,-40.,40.);
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
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver2>();
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
  TF1* f1 = new TF1("f1","gaus",-10.,10.);
  h2->Fit(f1,"Rn+");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn+");
  double width = f2->GetParameter(2);
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return width;
}

std::vector<double> MinimizeRefractiveandDistanceFunction::returnvalue(const double* a)
{
  TH1D* h1 = new TH1D("htof","",400,-40.,40.);
  TH1D* h2 = new TH1D("htoflog","",400,-40.,40.);
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
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver2>();
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
  TF1* f1 = new TF1("f1","gaus",-10.,10.);
  h2->Fit(f1,"Rn");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn");
  double mean = f2->GetParameter(1);
  double width = f2->GetParameter(2);
  std::vector<double> returnvalue;
  returnvalue.push_back(mean);
  returnvalue.push_back(width);
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return returnvalue;
}

std::vector<double> MinimizeRefractiveandDistanceFunction::returnvaluecutanglepeak(const double* a)
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
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_ver2>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	std::shared_ptr<theta_dir_i> t_i_f = std::make_shared<theta_dir_i>();
	t_i_f->SetHitInfo(info);
	t_i_f->SetReconstructdata(datatrue);
	double costheta = std::cos(t_i_f->returnvalue());
	if(std::abs(costheta - 0.75) < 0.02) 
	  h1->Fill(ftof->returnvalue() - vectrue.t());
      }
    }
  for(int i = 1; i < h1->GetXaxis()->GetNbins() + 1;i++)
    {
      if(h1->GetBinContent(i) != 0)
	h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
    }
  TF1* f1 = new TF1("f1","gaus",-10.,10.);
  h2->Fit(f1,"Rn");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn");
  double mean = f2->GetParameter(1);
  double width = f2->GetParameter(2);
  std::vector<double> returnvalue;
  returnvalue.push_back(mean);
  returnvalue.push_back(width);
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return returnvalue;
}

std::vector<double> MinimizeRefractiveandDistanceFunction::returnvaluecutanglepeakaddflyparticle(const double* a)
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
      datatrue.Setdflyparticle(a[3]);
      int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
      for(int j = 0;j<ncherenkovdigihits;++j){
	WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
	hitinfo info;
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_afterfly>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	std::shared_ptr<theta_dir_i> t_i_f = std::make_shared<theta_dir_i>();
	t_i_f->SetHitInfo(info);
	t_i_f->SetReconstructdata(datatrue);
	double costheta = std::cos(t_i_f->returnvalue());
	if(std::abs(costheta - 0.75) < 0.02) 
	  h1->Fill(ftof->returnvalue() - a[3]/v_light - vectrue.t());
      }
    }
  for(int i = 1; i < h1->GetXaxis()->GetNbins() + 1;i++)
    {
      if(h1->GetBinContent(i) != 0)
	h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
    }
  TF1* f1 = new TF1("f1","gaus",-10.,10.);
  h2->Fit(f1,"Rn");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("f2","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn");
  double mean = f2->GetParameter(1);
  double width = f2->GetParameter(2);
  std::vector<double> returnvalue;
  returnvalue.push_back(mean);
  returnvalue.push_back(width);
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return returnvalue;
}

double MinimizeRefractiveandDistanceFunction::returnminimizedfunctioncutanglepeakaddflyparticle(const double* a)
{
  TH1D* h1 = new TH1D("htof","",400,-40.,40.);
  TH1D* h2 = new TH1D("htoflog","",400,-40.,40.);
  int nevent = wcsimT->GetEntries();
  std::cout << "n = " << a[0] << std::endl;
  std::cout << "doffsetwall = " << a[1] << std::endl;
  std::cout << "doffsetcap = " << a[2] << std::endl;
  std::cout << "dflyparticle = " << a[3] << std::endl;
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
      datatrue.Setdflyparticle(a[3]);
      int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
      for(int j = 0;j<ncherenkovdigihits;++j){
	WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
	hitinfo info;
	info.Setdoffsetwall(a[1]);
	info.Setdoffsetcap(a[2]);
	info.Sethit(hit,wcsimrootgeom);
	int tubeId = hit->GetTubeId();
	WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	std::shared_ptr<tof> ftof = std::make_shared<tof>();
	ftof->SetHitInfo(info);
	ftof->SetReconstructdata(datatrue);
	std::shared_ptr<distance_function> d_p_p = std::make_shared<distance_position_pmt_afterfly>();
	d_p_p->SetHitInfo(info);
	d_p_p->SetReconstructdata(datatrue);
	ftof->Setdistancefunction(d_p_p);
	ftof->Setnwater(a[0]);
	std::shared_ptr<theta_dir_i> t_i_f = std::make_shared<theta_dir_i>();
	t_i_f->SetHitInfo(info);
	t_i_f->SetReconstructdata(datatrue);
	double costheta = std::cos(t_i_f->returnvalue());
	if(std::abs(costheta - 0.75) < 0.02) 
	  h1->Fill(ftof->returnvalue() - a[3]/v_light - vectrue.t());
      }
    }
  for(int i = 1; i < h1->GetXaxis()->GetNbins() + 1;i++)
    {
      if(h1->GetBinContent(i) != 0)
	h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
    }
  TF1* f1 = new TF1("ffirst","gaus",-10.,10.);
  h2->Fit(f1,"Rn");
  double meantemp = f1->GetParameter(1);
  TF1* f2 = new TF1("fsecond","gaus",meantemp - 5.,meantemp + 5.);
  h2->Fit(f2,"Rn");
  double mean = f2->GetParameter(1);
  std::cout << "mean = " << mean << std::endl;
  double width = f2->GetParameter(2);
  std::cout << "width = " << width << std::endl;
  double meansigma = 1.;
  double meanerror = mean*mean/(meansigma*meansigma);
  double widtherror = 1.;
  double widthsigma = (width - 10.)/widtherror;
  double v = -std::exp(-meanerror/2.) + std::exp(widthsigma);
  std::cout << "value = " << v << std::endl;
  delete h1;
  delete h2;
  delete f1;
  delete f2;
  return v;
}
