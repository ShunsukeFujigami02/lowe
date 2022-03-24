#include "Energy.hh"
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <cmath>
#include <memory>
#include "distance_function.hh"
#include "tof.hh"
#include <fmath.hpp>

void EnergyFunction::SetData(AnalizeFile filein,AnalizeFiledata* datain)
{
  file = filein;
  data = datain;
}

double NeffNoRetro::returnvalue()
{
  TFile* fNearPMT = new TFile("/rhome/fujigami/retro/lowe/NearPMT.root");
  TTree* tNearPMT = (TTree*)fNearPMT->Get("NearPMT");
  std::vector<int>* iNearPMT = nullptr;
  TBranch* biNearPMT = nullptr;
  tNearPMT->SetBranchAddress("iNearPMT",&iNearPMT,&biNearPMT);
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50 = 0;
  int N100 = 0;
  Reconstructdata rdata;
  double x = data->reconstructdataminimize->GetParameter(0);
  double y = data->reconstructdataminimize->GetParameter(1);
  double z = data->reconstructdataminimize->GetParameter(2);
  double t = data->reconstructdataminimize->GetParameter(3);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferror = ftof->returnvalue() - rdata.Get4Vector().t();
      if((toferror < 25.) && (toferror > -25.))
	{
	  N50++;
	}
      if((toferror < 50.) && (toferror > -50.))
	{
	  N100++;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int CylLoc = info.GetCylLoc();
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      d_p_p->SetHitInfo(info);
      d_p_p->SetReconstructdata(rdata);
      double distance_p_p = d_p_p->returnvalue();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(info);
      ftof->SetReconstructdata(rdata);
      double toferror = ftof->returnvalue() - rdata.Get4Vector().t();
      if((toferror < 25.) && (toferror > -25.))
	{
	  int hitnum = 0;
	  for(int l = 0;l < ncherenkovdigihits;l++)
	    {
	      int tubeId = data->allhitinfo[l].GetTubeId();
	      for(size_t m = 0;m < iNearPMT->size();m++)
		{
		  if(iNearPMT->at(m) == (tubeId - 1))
		    hitnum++;
		}
	    }
	  double xi = (double)hitnum/9.;
	  double Xi = 0.;
	  if(xi < 0.01)
	    Xi = 1.;
	  else if(xi < 0.99)
	    Xi = -std::log(1-xi)/xi;
	  else
	    Xi = 3.;
	  double epsilondark = 50e-06* 11146 * 4.2/N50;
	  double epsilontail = (N100 - N50 - 11146*4.2*50e-6)/N50;
	  CLHEP::Hep3Vector orientation = info.Get3Orientation();
	  CLHEP::Hep3Vector hitdirection = rdata.Get3Position() - info.Get3Position();
	  double theta_i = hitdirection.angle(orientation);
	  double phi_i = 0.;
	  if(CylLoc == 1)
	    {
	      CLHEP::Hep3Vector rotationaxis(0.,0.,1.);
	      CLHEP::Hep3Vector rotatedhitdirection = hitdirection.rotate(rotationaxis,-orientation.phi());
	      phi_i = std::atan(rotatedhitdirection.y()/rotatedhitdirection.z());
	    }
	  else
	    {
	      phi_i = hitdirection.phi();
	    }
	  double pi = std::acos(-1.);
	  if(phi_i < 0.)
	    {
	      phi_i = phi_i + pi;
	    }
	  if(phi_i > pi/2.)
	    {
	      phi_i = phi_i - pi/2.;
	    }
	  double coverage = 0.;
	  int bintheta = hPhotoCoverage->GetXaxis()->FindBin(theta_i*180./pi);
	  int binphi = hPhotoCoverage->GetYaxis()->FindBin(phi_i*180./pi);
	  if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1))
	    {
	      coverage = 1.;
	    }
	  else
	    {
	      coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	    }
	  //	  std::cout << "theta = " << theta_i*180./pi << std::endl;
	  //	  std::cout << "phi = " << phi_i*180./pi << std::endl;
	  //	  std::cout << "coverage = " << coverage << std::endl;
	  //	  std::cout << "distance_p_p = " << distance_p_p << std::endl;
	  double lambdarun = 10000.;
	  double coveragemean = 0.4041;
	  Neff += ((Xi + epsilontail - epsilondark)* coveragemean/ coverage * std::exp(distance_p_p/lambdarun));     
	}
    }
  delete fNearPMT;
  delete fPhotoCoverage;
  return Neff;
}

double NeffOnRetro::returnvalue()
{
  TFile* fNearPMT = new TFile("/rhome/fujigami/retro/lowe/NearPMT.root");
  TTree* tNearPMT = (TTree*)fNearPMT->Get("NearPMT");
  std::vector<int>* iNearPMT = nullptr;
  TBranch* biNearPMT = nullptr;
  tNearPMT->SetBranchAddress("iNearPMT",&iNearPMT,&biNearPMT);
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50noretro = 0;
  int N100noretro = 0;
  int N50onretro = 0;
  int Ncor = 0;
  Reconstructdata rdata;
  double x = data->reconstructdataminimize->GetParameter(0);
  double y = data->reconstructdataminimize->GetParameter(1);
  double z = data->reconstructdataminimize->GetParameter(2);
  double t = data->reconstructdataminimize->GetParameter(3);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N100noretro and N50onretro 2: only N50onretro 3: only N50noretro 4: only N100noretro 5: not any
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  double cd = 248232.;
  double cr = 732.367 + 62166.2*reflectivity;
  double pd = cd/(cd+cr);
  double pr = cr/(cd+cr);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      if(std::abs(toferrornoretro) < 25.)
	{
	  if(std::abs(toferroronretro) < 25.)
	    {
	      hittype.push_back(0);
	      N50noretro++;
	      N100noretro++;
	      N50onretro++;
	    }
	  else
	    {
	      hittype.push_back(3);
	      N50noretro++;
	      N100noretro++;
	    }
	}
      else if(std::abs(toferrornoretro) < 50.)
	  {
	    if(std::abs(toferroronretro) < 25.)
	      {
		hittype.push_back(1);
		N100noretro++;
		N50onretro++;
		Ncor++;
	      }
	    else
	      {
		hittype.push_back(4);
		N100noretro++;
	      }
	  }
      else
	{
	  if(std::abs(toferroronretro) < 25.)
	    {
	      hittype.push_back(2);
	      N50onretro++;
	    }
	  else
	    {
	      hittype.push_back(5);
	    }
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int CylLoc = info.GetCylLoc();
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      d_p_p->SetHitInfo(info);
      d_p_p->SetReconstructdata(rdata);
      double distance_p_p = d_p_p->returnvalue();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      d_f_r->SetHitInfo(info);
      d_f_r->SetReconstructdata(rdata);
      double distance_f_r = d_f_r->returnvalue();
      int hitnum = 0;
      for(int l = 0;l < ncherenkovdigihits;l++)
	{
	  int tubeId = data->allhitinfo[l].GetTubeId();
	  for(size_t m = 0;m < iNearPMT->size();m++)
	    {
	      if(iNearPMT->at(m) == (tubeId - 1))
		hitnum++;
	    }
	}
      double xi = (double)hitnum/9.;
      double Xi = 0.;
      if(xi < 0.01)
	Xi = 1.;
      else if(xi < 0.99)
	Xi = -std::log(1-xi)/xi;
      else
	Xi = 3.;
      CLHEP::Hep3Vector orientation = info.Get3Orientation();
      CLHEP::Hep3Vector hitdirection = rdata.Get3Position() - info.Get3Position();
      double theta_i = hitdirection.angle(orientation);
      double phi_i = 0.;
      if(CylLoc == 1)
	{
	  CLHEP::Hep3Vector rotationaxis(0.,0.,1.);
	  CLHEP::Hep3Vector rotatedhitdirection = hitdirection.rotate(rotationaxis,-orientation.phi());
	  phi_i = std::atan(rotatedhitdirection.y()/rotatedhitdirection.z());
	}
      else
	{
	  phi_i = hitdirection.phi();
	}
      double pi = std::acos(-1.);
      if(phi_i < 0.)
	{
	  phi_i = phi_i + pi;
	}
      if(phi_i > pi/2.)
	{
	  phi_i = phi_i - pi/2.;
	}
      double coverage = 0.;
      int bintheta = hPhotoCoverage->GetXaxis()->FindBin(theta_i*180./pi);
      int binphi = hPhotoCoverage->GetYaxis()->FindBin(phi_i*180./pi);
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1))
	{
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      double lambdarun = 10000.;
      double coveragemean = 0.4041;
      double epsilondarknoretro = 50e-06* 11146 * 4.2/N50noretro;
      double epsilontailnoretro = (N100noretro - N50noretro - Ncor - 11146*4.2*50e-6)/N50noretro;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      double epsilondarkonretro = 50e-06* 11146 * 4.2/N50onretro;
      double Sr = ((Xi - epsilondarkonretro)*coveragemean/coverage * std::exp(distance_f_r/lambdarun));
      if(hittype[k] == 0)
	{
	  if((type == 0) || (type == 3))
	    Neff += (pd*Sd + pr*Sr);
	}
      if(hittype[k] == 1)
	{
	  if((type == 0) || (type == 2))
	    Neff += Sr;
	}
      if(hittype[k] == 2)
	{
	  if((type == 0) || (type == 2))
	    Neff += Sr;
	}
      if(hittype[k] == 3)
	{
	  if((type == 0) || (type == 1))
	    Neff += Sd;
	}
      if(hittype[k] == 4)
	{;}
      if(hittype[k] == 5)
	{;}
    }
  delete fNearPMT;
  delete fPhotoCoverage;
  return Neff;
}
