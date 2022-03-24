#include "Energy.hh"
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <cmath>
#include <memory>
#include "distance_function.hh"
#include "tof.hh"
#include "MinimizedFunction.hh"
#include <fmath.hpp>


void EnergyFunction::SetData(AnalizeFile filein,AnalizeFiledata* datain)
{
  file = filein;
  data = datain;
}

double NeffNoRetro::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50 = 0;
  int N100 = 0;
  double Xiave = 0.;
  Reconstructdata rdata;
  double x = data->reconstructdataminimize->GetParameter(0);
  double y = data->reconstructdataminimize->GetParameter(1);
  double z = data->reconstructdataminimize->GetParameter(2);
  double t = data->reconstructdataminimize->GetParameter(3);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  std::vector<int> hittubeid;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      int tubeId = info.GetTubeId();
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
	  for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	    for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	      {
		if(*iter2  == (*iter - 1))
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
	  Xiave += Xi;
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
	  if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	    {
	      std::cout << "warning: coverage cannot be calculated!" << std::endl;
	      std::cout << "theta_i = " << theta_i << std::endl;
	      std::cout << "phi_i = " << phi_i << std::endl;
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
	  //	  lambdarun = 6160.5;
	  double coveragemean = 0.4041;
	  Neff += ((Xi + epsilontail - epsilondark)* coveragemean/ coverage * std::exp(distance_p_p/lambdarun));     
	}
    }
  Xiave = Xiave/(double)N50;
  std::cout << "average of Xi is " << Xiave << std::endl;
  doubleval.push_back(Neff);
  doubleval.push_back(0.);
  delete fPhotoCoverage;
  return 0.;
}

double NeffNoRetroTrue::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50 = 0;
  int N100 = 0;
  double Xiave = 0.;
  Reconstructdata rdata;
  double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
  double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
  double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
  double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  std::vector<int> hittubeid;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      int tubeId = info.GetTubeId();
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
	  for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	    for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	      {
		if(*iter2  == (*iter - 1))
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
	  Xiave += Xi;
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
	  if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	    {
	      std::cout << "warning: coverage cannot be calculated!" << std::endl;
	      std::cout << "theta_i = " << theta_i << std::endl;
	      std::cout << "phi_i = " << phi_i << std::endl;
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
	  //	  lambdarun = 6160.5;
	  double coveragemean = 0.4041;
	  Neff += ((Xi + epsilontail - epsilondark)* coveragemean/ coverage * std::exp(distance_p_p/lambdarun));     
	}
    }
  Xiave = Xiave/(double)N50;
  std::cout << "average of Xi is " << Xiave << std::endl;
  doubleval.push_back(Neff);
  doubleval.push_back(0.);
  delete fPhotoCoverage;
  return 0.;
}

/*double NeffOnRetro::returnvalue(std::vector<int>& intval,std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  double Nefftype0 = 0.;
  double Nefftype1 = 0.;
  double Nefftype2 = 0.;
  double Nefftype3 = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50noretro = 0;
  int N100noretro = 0;
  int N50onretro = 0;
  int Ntype0 = 0;
  int Ntype1 = 0;
  int Ntype2 = 0;
  int Ntype3 = 0;
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
  std::vector<int> hittubeid;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = 50e-06* 11146 * 4.2/N50onretro;
      double Sr = ((Xi - epsilondarkonretro)*coveragemean/coverage * std::exp(distance_f_r/lambdarun));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neff += (pd*Sd + pr*Sr);
	  Nefftype0 +=(pd*Sd + pr*Sr);
	  Ntype0 += 1;
	}
      if(hittype[k] == 1)
	{
	  Neff += Sr;
	  Nefftype1 += Sr;
	  Ntype1 += 1;
	}
      if(hittype[k] == 2)
	{
	  Neff += Sr;
	  Nefftype2 += Sr;
	  Ntype2 += 1;
	}
      if(hittype[k] == 3)
	{
	  Neff += Sd;
	  Nefftype3 += Sd;
	  Ntype3 += 1;
	}
      if(hittype[k] == 4)
	{;}
      if(hittype[k] == 5)
	{;}
    }
  doubleval.push_back(Neff);
  doubleval.push_back(0.);
  fPhotoCoverage->Close();
  return 0.;
}
*/

/*double NeffOnRetroaddretrotail::returnvalue(std::vector<int>& intval,std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  int N50noretro = 0;
  int N100noretro = 0;
  int N50onretro = 0;
  int N100onretro = 0;
  int Ncor1 = 0;
  int Ncor2 = 0;
  Reconstructdata rdata;
  double x = data->reconstructdataminimize->GetParameter(0);
  double y = data->reconstructdataminimize->GetParameter(1);
  double z = data->reconstructdataminimize->GetParameter(2);
  double t = data->reconstructdataminimize->GetParameter(3);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N100noretro and N50onretro 2: only N50onretro 3: N50noretro and N100onretro 4: N100noretro and N100onretro 5: only N100onretro 6: only N50noretro 7: only N100noretro 8: not any
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  double cd = 248232.;
  double cr = 732.367 + 62166.2*reflectivity;
  double pd = cd/(cd+cr);
  double pr = cr/(cd+cr);
  std::vector<int> hittubeid;
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
	      N100onretro++;
	    }
	  else if(std::abs(toferroronretro) < 50.)
	    {
	      hittype.push_back(3);
	      N50noretro++;
	      N100noretro++;
	      N100onretro++;
	      Ncor2++;
	    }
	  else
	    {
	      hittype.push_back(6);
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
		N100onretro++;
		Ncor1++;
	      }
	    else if(std::abs(toferroronretro) < 50.)
	      {
		hittype.push_back(4);
		N100noretro++;
		N100onretro++;
		Ncor2++;
	      }
	    else
	      {
		hittype.push_back(7);
		N100noretro++;
	      }
	  }
      else
	{
	  if(std::abs(toferroronretro) < 25.)
	    {
	      hittype.push_back(2);
	      N50onretro++;
	      N100onretro++;
	    }
	  else if(std::abs(toferroronretro) < 50.)
	    {
	      hittype.push_back(5);
	      N100onretro++;
	    }
	  else
	    {
	      hittype.push_back(8);
	    }
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      double epsilontailnoretro = (N100noretro - N50noretro - Ncor1 - 11146*4.2*50e-6)/N50noretro;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0;      
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = 50e-06* 11146 * 4.2/N50onretro;
      double epsilontailonretro = (N100onretro - N50onretro - Ncor2 - 11146*4.2*50e-6)/N50onretro;
      if(epsilontailonretro < 0.)
	epsilontailonretro = 0;
      double Sr = ((Xi + epsilontailonretro - epsilondarkonretro)*coveragemean/coverage * std::exp(distance_f_r/lambdarun));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  if((type == 0) || (type == 3))
	    Neff += (pd*Sd + pr*Sr);
	}
      if(hittype[k] == 1)
	{
	  if((type == 0) || (type == 2)){
	    Neff += Sr;
	  }
	}
      if(hittype[k] == 2)
	{
	  if((type == 0) || (type == 2)){
	    Neff += Sr;
	  }
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
      if(hittype[k] == 6)
	{
	  if((type == 0) || (type == 1))
	    Neff += Sd;
	}
      if(hittype[k] == 7)
	{;}
      if(hittype[k] == 8)
	{;}
    }
  delete fPhotoCoverage;
  return Neff;
}
*/
double NeffOnRetroFinal::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  double N50direff = 0.;
  double N100direff = 0.;
  double N50refeff = 0.;
  double N100refeff = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->reconstructdataminimize->GetParameter(0);
  minimizedvalue.emplace_back(x);
  double y = data->reconstructdataminimize->GetParameter(1);
  minimizedvalue.emplace_back(y);
  double z = data->reconstructdataminimize->GetParameter(2);
  minimizedvalue.emplace_back(z);
  double t = data->reconstructdataminimize->GetParameter(3);
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  double costheta = data->reconstructdataminimize->GetParameter(4);
  minimizedvalue.emplace_back(costheta);
  double phi = data->reconstructdataminimize->GetParameter(5);
  minimizedvalue.emplace_back(phi);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdir",file,data,6);
  MinimizedFunction* funcpref = new MinimizedFunction("pref",file,data,6);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivity",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref);
      double nref = pref/(pdir + pref);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref);
      double nref = pref/(pdir + pref);
      double epsilondarknoretro = 50e-06* 11146 * 4.2/N50direff;
      double epsilontailnoretro = (N100direff - N50direff - 11146*4.2*50e-6)/N50direff;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun))* ndir;
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = 50e-06* 11146 * 4.2/N50refeff;
      double epsilontailonretro = (N100refeff - N50refeff -11146*4.2*50e-6)/N50refeff;
      if(epsilontailonretro < 0.)
	epsilontailonretro = 0.;
      double Sr = ((Xi + epsilontailonretro - epsilondarkonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdarunRetro))* nref;
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  //  delete fPhotoCoverage;
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  //  delete funcpdir;
  //  delete funcpref;
  //  delete ravefunc;
  return 0.;
}

double NeffOnRetroFinalver2::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  int N50dir = 0;
  int N50ref = 0;
  double N50direffdirect = 0.;
  double N100direffdirect = 0.;
  double N50direffreflect = 0.;
  double N50refeffreflect = 0.;
  double N100refeffreflect = 0.;
  double N50refeffdirect = 0.;
  double N50direffdark = 0.;
  double N50refeffdark = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->reconstructdataminimize->GetParameter(0);
  minimizedvalue.emplace_back(x);
  double y = data->reconstructdataminimize->GetParameter(1);
  minimizedvalue.emplace_back(y);
  double z = data->reconstructdataminimize->GetParameter(2);
  minimizedvalue.emplace_back(z);
  double t = data->reconstructdataminimize->GetParameter(3);
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  double costheta = data->reconstructdataminimize->GetParameter(4);
  minimizedvalue.emplace_back(costheta);
  double phi = data->reconstructdataminimize->GetParameter(5);
  minimizedvalue.emplace_back(phi);
  double darknumexpected = data->reconstructdataminimize->GetParameter(6);
  minimizedvalue.emplace_back(darknumexpected);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  double lambdaRetroFixed = GetLambda(reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",file,data,7);
  MinimizedFunction* funcpref = new MinimizedFunction("preftime",file,data,7);
  MinimizedFunction* funcpdark = new MinimizedFunction("pdark",file,data,7);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivityBroad",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  funcpdark->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref + pdark);
      double nref = pref/(pdir + pref + pdark);
      double ndark = pdark/(pdir + pref + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50dir++;
	  N50direffdirect += ndir;
	  N50direffreflect += nref;
	  N50direffdark += ndark;
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    N50refeffdark += ndark;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    N50refeffdark += ndark;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direffdirect += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeffreflect += nref;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double epsilondarknoretro = N50direffdark/(double)N50dir;
      double epsilonreflectnoretro = N50direffreflect/(double)N50dir;
      double epsilontailnoretro = (N100direffdirect - N50direffdirect)/(double)N50dir;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro - epsilonreflectnoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = N50refeffdark/(double)N50ref;
      double epsilondirectonretro = N50refeffdirect/(double)N50ref;
      double epsilontailonretro = (N100refeffreflect - N50refeffreflect)/(double)N50ref;
      if(epsilontailonretro < 0.)
	epsilontailonretro = 0.;
      double Sr = ((Xi + epsilontailonretro - epsilondarkonretro - epsilondirectonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdaRetroFixed));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  return 0.;
}

double NeffOnRetroFinalTrue::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  int N50dir = 0;
  int N50ref = 0;
  double N50direffdirect = 0.;
  double N100direffdirect = 0.;
  double N50direffreflect = 0.;
  double N50refeffreflect = 0.;
  double N100refeffreflect = 0.;
  double N50refeffdirect = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
  minimizedvalue.emplace_back(x);
  double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
  minimizedvalue.emplace_back(y);
  double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
  minimizedvalue.emplace_back(z);
  double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
  double truedirx = track->GetPdir(0);
  double truediry = track->GetPdir(1);
  double truedirz = track->GetPdir(2);
  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
  double costheta = dir.cosTheta();
  minimizedvalue.emplace_back(costheta);
  double phi = dir.phi();
  minimizedvalue.emplace_back(phi);
  double darknumexpected = 63.198;
  minimizedvalue.emplace_back(darknumexpected);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdir",file,data,7);
  MinimizedFunction* funcpref = new MinimizedFunction("pref",file,data,7);
  MinimizedFunction* funcpdark = new MinimizedFunction("pdark",file,data,7);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivityBroad",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  funcpdark->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref + pdark);
      double nref = pref/(pdir + pref + pdark);
      double ndark = pdark/(pdir + pref + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50dir++;
	  N50direffdirect += ndir;
	  N50direffreflect += nref;
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direffdirect += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeffreflect += nref;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double epsilondarknoretro = 50e-06* 11146 * 4.2/(double)N50dir;
      double epsilonreflectnoretro = N50direffreflect/(double)N50dir;
      double epsilontailnoretro = (N100direffdirect - N50direffdirect)/(double)N50dir;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro - epsilonreflectnoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = 50e-06* 11146 * 4.2/(double)N50ref;
      double epsilondirectonretro = N50refeffdirect/(double)N50ref;
      double epsilontailonretro = (N100refeffreflect - N50refeffreflect)/(double)N50ref;
      if(epsilontailonretro < 0.)
	epsilontailonretro = 0.;
      double Sr = ((Xi + epsilontailonretro - epsilondarkonretro - epsilondirectonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdarunRetro));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  return 0.;
}

double NeffOnRetroFinalver2True::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  int N50dir = 0;
  int N50ref = 0;
  double N50direffdirect = 0.;
  double N100direffdirect = 0.;
  double N50direffreflect = 0.;
  double N50refeffreflect = 0.;
  double N100refeffreflect = 0.;
  double N50refeffdirect = 0.;
  double N50direffdark = 0.;
  double N50refeffdark = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
  minimizedvalue.emplace_back(x);
  double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
  minimizedvalue.emplace_back(y);
  double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
  minimizedvalue.emplace_back(z);
  double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
  double truedirx = track->GetPdir(0);
  double truediry = track->GetPdir(1);
  double truedirz = track->GetPdir(2);
  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
  double costheta = dir.cosTheta();
  minimizedvalue.emplace_back(costheta);
  double phi = dir.phi();
  minimizedvalue.emplace_back(phi);
  double darknumexpected = 63.198;
  minimizedvalue.emplace_back(darknumexpected);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",file,data,7);
  MinimizedFunction* funcpref = new MinimizedFunction("preftime",file,data,7);
  MinimizedFunction* funcpdark = new MinimizedFunction("pdark",file,data,7);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivityBroad",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  funcpdark->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref + pdark);
      double nref = pref/(pdir + pref + pdark);
      double ndark = pdark/(pdir + pref + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50dir++;
	  N50direffdirect += ndir;
	  N50direffreflect += nref;
	  N50direffdark += ndark;
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    N50refeffdark += ndark;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeffdirect += ndir;
	    N50refeffreflect += nref;
	    N50refeffdark += ndark;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direffdirect += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeffreflect += nref;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double epsilondarknoretro = N50direffdark/(double)N50dir;
      double epsilonreflectnoretro = N50direffreflect/(double)N50dir;
      double epsilontailnoretro = (N100direffdirect - N50direffdirect)/(double)N50dir;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro - epsilonreflectnoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = N50refeffdark/(double)N50ref;
      double epsilondirectonretro = N50refeffdirect/(double)N50ref;
      double epsilontailonretro = (N100refeffreflect - N50refeffreflect)/(double)N50ref;
      if(epsilontailonretro < 0.)
	epsilontailonretro = 0.;
      double Sr = ((Xi + epsilontailonretro - epsilondarkonretro - epsilondirectonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdarunRetro));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  return 0.;
}

double NeffOnRetroFinalver3True::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  int N50dir = 0;
  int N100ref = 0;
  double N50direffdirect = 0.;
  double N100direffdirect = 0.;
  double N50direffreflect = 0.;
  double N100refeffreflect = 0.;
  double N100refeffdirect = 0.;
  double N50direffdark = 0.;
  double N100refeffdark = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
  minimizedvalue.emplace_back(x);
  double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
  minimizedvalue.emplace_back(y);
  double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
  minimizedvalue.emplace_back(z);
  double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
  double truedirx = track->GetPdir(0);
  double truediry = track->GetPdir(1);
  double truedirz = track->GetPdir(2);
  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
  double costheta = dir.cosTheta();
  minimizedvalue.emplace_back(costheta);
  double phi = dir.phi();
  minimizedvalue.emplace_back(phi);
  double darknumexpected = 63.198;
  minimizedvalue.emplace_back(darknumexpected);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",file,data,7);
  MinimizedFunction* funcpref = new MinimizedFunction("preftime",file,data,7);
  MinimizedFunction* funcpdark = new MinimizedFunction("pdark",file,data,7);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivityBroad",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  funcpdark->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref + pdark);
      double nref = pref/(pdir + pref + pdark);
      double ndark = pdark/(pdir + pref + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50dir++;
	  N50direffdirect += ndir;
	  N50direffreflect += nref;
	  N50direffdark += ndark;
	  if(std::abs(toferroronretro) < 50.){
	    N100ref++;
	    N100refeffdirect += ndir;
	    N100refeffreflect += nref;
	    N100refeffdark += ndark;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 50.){
	    N100ref++;
	    N100refeffdirect += ndir;
	    N100refeffreflect += nref;
	    N100refeffdark += ndark;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direffdirect += ndir;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double epsilondarknoretro = N50direffdark/(double)N50dir;
      double epsilonreflectnoretro = N50direffreflect/(double)N50dir;
      double epsilontailnoretro = (N100direffdirect - N50direffdirect)/(double)N50dir;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro - epsilonreflectnoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = N100refeffdark/(double)N100ref;
      double epsilondirectonretro = N100refeffdirect/(double)N100ref;
      //      double epsilontailonretro = (N100refeffreflect - N50refeffreflect)/(double)N50ref;
      //      if(epsilontailonretro < 0.)
      //	epsilontailonretro = 0.;
      double Sr = ((Xi - epsilondarkonretro - epsilondirectonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdarunRetro));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  return 0.;
}

double NeffOnRetroFinalver3::returnvalue(std::vector<double>& doubleval)
{
  TFile* fPhotoCoverage = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root");
  TH2D* hPhotoCoverage = (TH2D*)fPhotoCoverage->Get("hcoverage");
  double Neffdirect = 0.;
  double Neffreflect = 0.;
  int N50dir = 0;
  int N100ref = 0;
  double N50direffdirect = 0.;
  double N100direffdirect = 0.;
  double N50direffreflect = 0.;
  double N100refeffreflect = 0.;
  double N100refeffdirect = 0.;
  double N50direffdark = 0.;
  double N100refeffdark = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  std::vector<int> hittype; // 0: N50noretro and N50onretro 1: N50noretro only 2: N50onretro only 3: not any
  Reconstructdata rdata;
  std::vector<double> minimizedvalue;
  double x = data->reconstructdataminimize->GetParameter(0);
  minimizedvalue.emplace_back(x);
  double y = data->reconstructdataminimize->GetParameter(1);
  minimizedvalue.emplace_back(y);
  double z = data->reconstructdataminimize->GetParameter(2);
  minimizedvalue.emplace_back(z);
  double t = data->reconstructdataminimize->GetParameter(3);
  minimizedvalue.emplace_back(t);
  rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
  double costheta = data->reconstructdataminimize->GetParameter(4);
  minimizedvalue.emplace_back(costheta);
  double phi = data->reconstructdataminimize->GetParameter(5);
  minimizedvalue.emplace_back(phi);
  double darknumexpected = data->reconstructdataminimize->GetParameter(6);
  minimizedvalue.emplace_back(darknumexpected);
  double sigma = 5.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  std::vector<int> hittubeid;
  MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",file,data,7);
  MinimizedFunction* funcpref = new MinimizedFunction("preftime",file,data,7);
  MinimizedFunction* funcpdark = new MinimizedFunction("pdark",file,data,7);
  MinimizedFunction* ravefunc = new MinimizedFunction("effectiveReflectivityBroad",file,data,6);
  MinimizedFunction* reflectcoverage = new MinimizedFunction("ReflectCoverage",file,data,6);
  reflectcoverage->SetPhotoCoverageHist(hPhotoCoverage);
  funcpdir->SetEventNumber(n);
  funcpref->SetEventNumber(n);
  funcpdark->SetEventNumber(n);
  ravefunc->SetEventNumber(n);
  reflectcoverage->SetEventNumber(n);
  double r_ave = ravefunc->returnvaluecontents(minimizedvalue);
  std::cout << "r_ave = " << r_ave << std::endl;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hittubeid.push_back(data->allhitinfo[k].GetTubeId());
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
      double pdir = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double pref = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdir/(pdir + pref + pdark);
      double nref = pref/(pdir + pref + pdark);
      double ndark = pdark/(pdir + pref + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50dir++;
	  N50direffdirect += ndir;
	  N50direffreflect += nref;
	  N50direffdark += ndark;
	  if(std::abs(toferroronretro) < 50.){
	    N100ref++;
	    N100refeffdirect += ndir;
	    N100refeffreflect += nref;
	    N100refeffdark += ndark;
	    hittype.push_back(0);
	  }
	  else{
	    hittype.push_back(1);
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 50.){
	    N100ref++;
	    N100refeffdirect += ndir;
	    N100refeffreflect += nref;
	    N100refeffdark += ndark;
	    hittype.push_back(2);
	  }
	  else{
	    hittype.push_back(3);
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direffdirect += ndir;
	}
    }
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      hitinfo info = data->allhitinfo[k];
      int tubeId = info.GetTubeId();
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
      for(auto iter = hittubeid.begin();iter != hittubeid.end();iter++){
	for(auto iter2 = data->vecNearPMT[tubeId - 1].begin();iter2 != data->vecNearPMT[tubeId - 1].end();iter2++)
	  {
	    if(*iter2  == (*iter - 1))
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
      if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
	{
	  std::cout << "warning: coverage cannot be calculated!" << std::endl;
	  std::cout << "theta_i = " << theta_i << std::endl;
	  std::cout << "phi_i = " << phi_i << std::endl;
	  coverage = 1.;
	}
      else
	{
	  coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
	}
      //      lambdarun = 6160.5;
      double lambdaRetroFixed = GetLambda(reflectivity);
      double coveragemean = 0.4041;
      double rcoverage = reflectcoverage->returnvaluecontentshit(minimizedvalue,k);
      double epsilondarknoretro = N50direffdark/(double)N50dir;
      double epsilonreflectnoretro = N50direffreflect/(double)N50dir;
      double epsilontailnoretro = (N100direffdirect - N50direffdirect)/(double)N50dir;
      if(epsilontailnoretro < 0.)
	epsilontailnoretro = 0.;
      double Sd = ((Xi + epsilontailnoretro - epsilondarknoretro - epsilonreflectnoretro)* coveragemean/coverage * std::exp(distance_p_p/lambdarun));
      if(Sd < 0.)
	Sd = 0.;
      double epsilondarkonretro = N100refeffdark/(double)N100ref;
      double epsilondirectonretro = N100refeffdirect/(double)N100ref;
      //      double epsilontailonretro = (N100refeffreflect - N50refeffreflect)/(double)N50ref;
      //      if(epsilontailonretro < 0.)
      //	epsilontailonretro = 0.;
      double Sr = ((Xi - epsilondarkonretro - epsilondirectonretro)*coveragemean/(coverage*rcoverage) * std::exp(distance_f_r/lambdaRetroFixed));
      if(Sr < 0.)
	Sr = 0.;
      if(hittype[k] == 0)
	{
	  Neffdirect += Sd;
	  Neffreflect += Sr;
	}
      if(hittype[k] == 1)
	{
	  Neffdirect += Sd;
	}
      if(hittype[k] == 2)
	{
	  Neffreflect += Sr;
	}
      if(hittype[k] == 3)
	{
	}
    }
  Neffreflect *= (1/r_ave);
  doubleval.push_back(Neffdirect);
  doubleval.push_back(Neffreflect);
  fPhotoCoverage->Close();
  delete funcpdir;
  delete funcpref;
  delete ravefunc;
  delete reflectcoverage;
  return 0.;
}

double EnergyFunction::GetLambda(double reflectivity){
  return -(reflectivity - 0.3)*1000./0.7 + 13000.;
}
