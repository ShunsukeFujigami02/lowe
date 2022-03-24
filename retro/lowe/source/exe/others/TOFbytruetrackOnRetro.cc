#include <TRint.h>
#include <TFile.h>
#include <TTree.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include <TH1D.h>
#include <TH2D.h>
#include <exception>
#include <iostream>
#include <string>
#include <memory>
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
#include "constants.hh"
#include <TF1.h>
#include "TNinWater.hh"
#include "Reconstructdata.hh"
#include "hitinfo.hh"
#include "distance_function.hh"

double ninwatertrue(double *en,double* par)
{
  double energy = en[0];
  energy *= 1.0e9;
  double lambda = 2*PI*197/energy;
  TNinWater ninwater;
  double n = ninwater.returnvalue(lambda);
  return n;
}

std::vector<double> Getmeanandwidth(double n,TTree* wcsimT,WCSimRootEvent* wcsimrootevent,WCSimRootGeom* wcsimrootgeom,double toffset)
{
  double velocityfixed = v_light/n;
  TH1D* h1 = new TH1D("hmeanandwidth","",1000,-40.,40.);
  int n_event = wcsimT->GetEntries();
  for(int i = 0;i < n_event;i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      CLHEP::Hep3Vector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2));
      int Ntrack = wcsimroottrigger->GetNtrack();
      for(int k = 0;k < Ntrack;k++)
	{
	  WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(k);
	  if(k == 0 && i == 0)
	    {
	      std::cout << "Id = " << wcsimroottrack->GetId() << std::endl;
	      std::cout << "E = " << wcsimroottrack->GetE() << std::endl;
	      std::cout << "P = " << wcsimroottrack->GetP() << std::endl;
	      std::cout << "Px = " << wcsimroottrack->GetPdir(0) << std::endl;
	      std::cout << "Py = " << wcsimroottrack->GetPdir(1) << std::endl;
	      std::cout << "Pz = " << wcsimroottrack->GetPdir(2) << std::endl;
	    }
	  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
	  for(int l = 0;l < ncherenkovdigihits;l++)
	    {
	      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(l));
	      if((wcsimroottrack->GetId() == hit->GetTrackId()))
		{
		  double trec = wcsimroottrigger->GetTriggerTime() + hit->GetT() - offset;
		  int tubeId = hit->GetTubeId();
		  WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
		  CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
		  double distancerec = (pmtposition - vectrue).mag();
		  double trecminusttruebydistance = trec - distancerec/velocityfixed;
		  h1->Fill(trecminusttruebydistance + toffset);
		}
	    }
	}
    }
  std::cout << h1->GetMean() << std::endl;
  TF1* f1 = new TF1("f1","gaus",-40.,40.);
  h1->Fit(f1,"n");
  std::vector<double> mandw;
  mandw.push_back(f1->GetParameter(1));
  mandw.push_back(f1->GetParameter(2));
  delete f1;
  delete h1;
  return mandw;
}

double Getmean(double n,TTree* wcsimT,WCSimRootEvent* wcsimrootevent,WCSimRootGeom* wcsimrootgeom,double toffset,double distanceoffset)
{
  double velocityfixed = v_light/n;
  TH1D* h1 = new TH1D("hmeanandwidth","",1000,-40.,40.);
  int n_event = wcsimT->GetEntries();
  for(int i = 0;i < n_event;i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      CLHEP::Hep3Vector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2));
      int Ntrack = wcsimroottrigger->GetNtrack();
      for(int k = 0;k < Ntrack;k++)
	{
	  WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(k);
	  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
	  for(int l = 0;l < ncherenkovdigihits;l++)
	    {
	      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(l));
	      if((wcsimroottrack->GetId() == hit->GetTrackId()))
		{
		  double trec = wcsimroottrigger->GetTriggerTime() + hit->GetT() - offset;
		  int tubeId = hit->GetTubeId();
		  WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
		  CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
		  double distancerec = (pmtposition - vectrue).mag() - distanceoffset;
		  double trecminusttruebydistance = trec - distancerec/velocityfixed;
		  h1->Fill(trecminusttruebydistance + toffset);
		}
	    }
	}
    }
  double max = h1->GetXaxis()->GetBinCenter(h1->GetMaximumBin());
  std::cout << "max = " << max << std::endl;
  delete h1;
  return max;
}

int main(int argc,char** argv)
{
  try
    {
      const char* infile = "/rhome/fujigami/retro/lowe/analizefile/wcsim_20210817_003020.root";
      //      const char* infile = "/home/fujigami/retro/WCSim_build/wcsim.root";
      TRint app("app",&argc,argv);
      TFile* file = new TFile(infile);
      TTree* wcsimT =(TTree*)file->Get("wcsimT");
      WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
      wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
      wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
      TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
      WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
      wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
      wcsimGeoT->GetEntry(0);
      int n_event = wcsimT->GetEntries();
      TH1D* htrecminusttrue = new TH1D("htrecminusttrue","",1400,-30.,700.);
      TH1D* htrecminusttruelog = new TH1D("htrecminusttruelog","",1400,-30.,700.);
      TH1D* hdistancerecminusdistance = new TH1D("hdistancerecminusdistance","",1000,-50.,50.);
      TH1D* hdistancerecminusdistanceRetro = new TH1D("hdistancerecminusdistanceRetro","",1000,-50.,50.);
      TH2D* htrecvsttrue = new TH2D("htrecvsttrue","",1000,0.,700.,1000,0.,700.);
      TH1D* htrecminusttruebytracklength = new TH1D("htrecminusttruebytracklength","",1000,-30.,30.);
      TH1D* htrecminusttruebydistancestop = new TH1D("htrecminusttruebydistancestop","",1000,-30.,30.);
      TH1D* htrecminusttruebyPMTPosition = new TH1D("htrecminusttruebyPMTPosition","",1000,-30.,30.);
      TH1D* htrecminusttruebydistancestopRetro = new TH1D("htrecminusttruebydistancestopRetro","",1000,-30.,30.);
      TH1D* htrecminusttruebyPMTPositionRetro = new TH1D("htrecminusttruebyPMTPositionRetro","",1000,-30.,30.);
      TH1D* htrecminusttruebyPMTPositionRetroRetroonlylog = new TH1D("htrecminusttruebyPMTPositionRetroRetroonlylog","",1000,-300.,600.);
      TH1D* htrecminusttruebyPMTPositionRetroRetroonly = new TH1D("htrecminusttruebyPMTPositionRetroRetroonly","",1000,-300.,600.);
      TH1D* hnbytracklength = new TH1D("hnbytracklength","",1000,1.3,1.5);
      TH1D* hnbytracklengthnotPMT = new TH1D("hnbytracklengthnotPMT","",1000,1.3,1.5);
      TH1D* henergy = new TH1D("henergy","",1000,1e-6,5e-6);
      TH2D* henergyvsnbytracklength = new TH2D("henergyvsnbytracklength","",100,1e-6,5e-6,100,1.3,1.5);
      TH2D* henergyvsvelocitybytracklength = new TH2D("henergyvsvelocitybytracklength","",200,1e-6,5e-6,200,20.,23.);
      TH1D* hflytime = new TH1D("hflytime","",1000,0.,700.);
      TH1D* hdistance = new TH1D("hdistance","",1000,0.,3000.);
      TH1D* hdistanceRetro = new TH1D("hdistanceRetro","",1000,0.,6000.);
      TH2D* htracklengthvsdistancerec = new TH2D("htracklengthvsdistancerec","",1000,0.,10000.,1000,0.,4000);
      TH2D* htracklengthvsdistanceRetro = new TH2D("htracklengthvsdistanceRetro","",1000,0.,10000.,1000,0.,4000.);
      TH1D* hstopR = new TH1D("hstopR","",1000,0.,4000.);
      TH1D* hstartR = new TH1D("hstartR","",1000,1680.,1700.);
      TH2D* hstartRandL = new TH2D("hstartRandL","",1000,0.,1800.,1000,-2000.,2000.);
      TH1D* hstartLrestrict = new TH1D("hstartLrestrict","",1000,-1812.,-1808.);
      double nwaterfixed = 1.38072381233779451;
      double velocityfixed = v_light/nwaterfixed;
      double nwaterlower = 1.35;
      double nwaterupper = 1.46;
      double nwaternum = 1;
      double nwaterwidth = (nwaterupper - nwaterlower)/nwaternum;
      double toffset = 0.;
      double doffsetfixed = 1.95775611238980325e+01;
      TH1D* hmean = new TH1D("hmean","",nwaternum + 1,nwaterlower - nwaterwidth/2.,nwaterupper + nwaterwidth/2.);
      TH1D* hwidth = new TH1D("hwidth","",nwaternum + 1,nwaterlower - nwaterwidth/2.,nwaterupper + nwaterwidth/2.);
      for(double nwater = nwaterlower;nwater < nwaterupper + nwaterwidth/2.;nwater+=nwaterwidth)
	{
	  std::vector<double> meanandwidth = Getmeanandwidth(nwater,wcsimT,wcsimrootevent,wcsimrootgeom,toffset);
	  hmean->Fill(nwater,meanandwidth[0]);
	  hwidth->Fill(nwater,meanandwidth[1]);
	}
      double doffsetlower = 0.;
      double doffsetupper = 30.;
      double doffsetnum = 1;
      double doffsetwidth = (doffsetupper - doffsetlower)/doffsetnum;
      TH1D* hmax = new TH1D("hmax","",doffsetnum + 1,doffsetlower - doffsetwidth/2.,doffsetupper + doffsetwidth/2.);
      for(double doffset = doffsetlower;doffset < doffsetupper + doffsetwidth/2.;doffset+=doffsetwidth)
	{
	  double max = Getmean(nwaterfixed,wcsimT,wcsimrootevent,wcsimrootgeom,toffset,doffset);
	  hmax->Fill(doffset,max);
	}
      for(int i = 0;i < n_event;i++)
	{
	  wcsimT->GetEntry(i);
	  WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
	  CLHEP::Hep3Vector vectrue(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2));
	  CLHEP::HepLorentzVector vec4true(wcsimroottrigger->GetVtx(0),wcsimroottrigger->GetVtx(1),wcsimroottrigger->GetVtx(2),-wcsimroottrigger->GetTriggerTime());
	  int Ntrack = wcsimroottrigger->GetNtrack();
	  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
	  for(int l = 0;l < ncherenkovdigihits;l++)
	    {
	      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(l));
	      int tubeId = hit->GetTubeId();
	      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
	      CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
	      double distancerec = (pmtposition - vectrue).mag();
	      hitinfo info;
	      info.Sethit(hit,wcsimrootgeom);
	      Reconstructdata data;
	      data.Set4Vector(vec4true);
	      std::shared_ptr<distance_function> d_f_r = std::make_shared<distance_fly_retro>();
	      d_f_r->SetHitInfo(info);
	      d_f_r->SetReconstructdata(data);
	      double distanceRetro = d_f_r->returnvalue();
	      double trec = wcsimroottrigger->GetTriggerTime() + hit->GetT() - offset;
	      double trecminusttruebyPMTPosition = trec - (distancerec - doffsetfixed)/velocityfixed;
	      double trecminusttruebyPMTPositionRetro = trec - (distanceRetro - doffsetfixed)/velocityfixed;
	      htrecminusttruebyPMTPosition->Fill(trecminusttruebyPMTPosition + toffset);
	      htrecminusttruebyPMTPositionRetro->Fill(trecminusttruebyPMTPositionRetro + toffset);
	    }
	  for(int k = 0;k < Ntrack;k++)
	    {
	      WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(k);
	      if((wcsimroottrack->GetStopvol() != 20))
		{
		  double velocitybytracklength = (wcsimroottrack->GetTrackLength()/10.)/wcsimroottrack->GetFlyTime();
		  double nbytracklength = v_light/velocitybytracklength;
		  hnbytracklengthnotPMT->Fill(nbytracklength);
		}
	      for(int l = 0;l < ncherenkovdigihits;l++)
		{
		  WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(l));
		  if((wcsimroottrack->GetId() == hit->GetTrackId()))
		    {
		      hitinfo info;
		      info.Sethit(hit,wcsimrootgeom);
		      Reconstructdata data;
		      data.Set4Vector(vec4true);
		      CLHEP::Hep3Vector startvec(wcsimroottrack->GetStart(0),wcsimroottrack->GetStart(1),wcsimroottrack->GetStart(2));
		      CLHEP::Hep3Vector stopvec(wcsimroottrack->GetStop(0),wcsimroottrack->GetStop(1),wcsimroottrack->GetStop(2));
		      hstopR->Fill(std::sqrt(stopvec.x()*stopvec.x() + stopvec.y()*stopvec.y()));
		      if(wcsimroottrack->IsRetroReflectPhoton())
			{
			  std::cout << "startvol = " << wcsimroottrack->GetStartvol() << std::endl;
			  double R = std::sqrt(startvec.x()*startvec.x() + startvec.y()*startvec.y());
			  double L = startvec.z();
			  if(L < 1800 && L > -1800)
			    hstartR->Fill(R);
			  hstartRandL->Fill(R,L);
			  if(R < 1600.)
			    hstartLrestrict->Fill(L);
			}
		      double distance = (stopvec - startvec).mag();
		      hitinfo infostop;
		      infostop.Sethit(hit,wcsimrootgeom);
		      infostop.Set3Position(stopvec);
		      std::shared_ptr<distance_function> d_f_r = std::make_shared<distance_fly_retro>();
		      std::shared_ptr<distance_function> d_f_r_usetruestop = std::make_shared<distance_fly_retro>();
		      d_f_r->SetHitInfo(info);
		      d_f_r->SetReconstructdata(data);
		      d_f_r_usetruestop->SetHitInfo(infostop);
		      d_f_r_usetruestop->SetReconstructdata(data);
		      double distanceRetro = d_f_r->returnvalue();
		      double distanceRetrostop = d_f_r_usetruestop->returnvalue();
		      hdistance->Fill(distance);
		      hdistanceRetro->Fill(distanceRetro);
		      hdistancerecminusdistanceRetro->Fill(distanceRetro - distanceRetrostop);
		      double velocitybytracklength = (wcsimroottrack->GetTrackLength()/10.)/wcsimroottrack->GetFlyTime();
		      henergyvsvelocitybytracklength->Fill(wcsimroottrack->GetE(),velocitybytracklength);
		      double nbytracklength = v_light/velocitybytracklength;
		      double ttrue = wcsimroottrack->GetFlyTime();
		      hflytime->Fill(wcsimroottrack->GetFlyTime());
		      hnbytracklength->Fill(nbytracklength);
		      double trecminusttrue = -distance/velocityfixed + ttrue;
		      htrecminusttrue->Fill(trecminusttrue);
		      int tubeId = hit->GetTubeId();
		      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
		      CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
		      double distancerec = (pmtposition - vectrue).mag();
		      double distancestop = (stopvec - vectrue).mag();
		      double trec = wcsimroottrigger->GetTriggerTime() + hit->GetT() - offset;
		      double trecminusttruebytracklength = trec - (wcsimroottrack->GetTrackLength()/10.)/velocityfixed;
		      double trecminusttruebydistancestop = trec - distancestop/velocityfixed;
		      double trecminusttruebydistancestopRetro = trec - distanceRetrostop/velocityfixed;
		      double trecminusttruebyPMTPositionRetro = trec - (distanceRetro - doffsetfixed)/velocityfixed;
		      if(wcsimroottrack->IsRetroReflectPhoton())
			htrecminusttruebyPMTPositionRetroRetroonly->Fill(trecminusttruebyPMTPositionRetro);
		      
		      hdistancerecminusdistance->Fill(distancerec - distance);
		      htrecvsttrue->Fill(trec,ttrue);
		      henergy->Fill(wcsimroottrack->GetE());
		      henergyvsnbytracklength->Fill(wcsimroottrack->GetE(),nbytracklength);
		      htracklengthvsdistancerec->Fill(wcsimroottrack->GetTrackLength()/10.,distancerec);
		      htracklengthvsdistanceRetro->Fill(wcsimroottrack->GetTrackLength()/10.,distanceRetro);
		      htrecminusttruebytracklength->Fill(trecminusttruebytracklength + toffset);
		      htrecminusttruebydistancestop->Fill(trecminusttruebydistancestop + toffset);
		      htrecminusttruebydistancestopRetro->Fill(trecminusttruebydistancestopRetro + toffset);
		      
		    }
		}
	    }
	}
      for(int i = 1; i < htrecminusttrue->GetXaxis()->GetNbins();i++)
	{
	  if(htrecminusttrue->GetBinContent(i) != 0)
	    htrecminusttruelog->Fill(htrecminusttrue->GetXaxis()->GetBinCenter(i),std::log(htrecminusttrue->GetBinContent(i)));
	}
      for(int i = 1; i < htrecminusttruebyPMTPositionRetroRetroonly->GetXaxis()->GetNbins();i++)
	{
	  if(htrecminusttruebyPMTPositionRetroRetroonly->GetBinContent(i) != 0)
	    htrecminusttruebyPMTPositionRetroRetroonlylog->Fill(htrecminusttruebyPMTPositionRetroRetroonly->GetXaxis()->GetBinCenter(i),std::log(htrecminusttruebyPMTPositionRetroRetroonly->GetBinContent(i)));
	}
      htrecminusttruebyPMTPositionRetroRetroonlylog->SetStats(0);
      htrecminusttruebyPMTPositionRetroRetroonlylog->Draw();
      //      TF1* f1 = new TF1("f1",ninwatertrue,1e-6,5e-6,2);
      app.Run();
      //      delete f1;
    }
  catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  
  catch(std::string str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  
  return 0;
}
