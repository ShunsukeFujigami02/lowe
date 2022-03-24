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
#include <CLHEP/Vector/ThreeVector.h>
#include "constants.hh"
#include <TF1.h>
#include "TNinWater.hh"

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
  TH1D* h1 = new TH1D("hmeanandwidth","",500,-40.,40.);
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
  TF1* f1 = new TF1("f1","gaus",max - 10.,max + 10.);
  h1->Fit(f1,"Rn");
  double fitmax = f1->GetParameter(1);
  std::cout << "fitmax = " << fitmax << std::endl;
  delete h1;
  delete f1;
  return fitmax;
}

int main(int argc,char** argv)
{
  try
    {
      const char* infile = "/rhome/fujigami/retro/lowe/analizefile/wcsim_20210726_162856.root";
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
      TH1D* h1 = new TH1D("h1","",1400,-30.,700.);
      TH1D* h2 = new TH1D("h2","",1400,-30.,700.);
      TH1D* h3 = new TH1D("h3","",1000,-50.,50.);
      TH2D* h4 = new TH2D("h4","",10000,0.,700.,10000,0.,700.);
      TH1D* h5 = new TH1D("h5","",1000,1.3,1.5);
      TH1D* htrecminusttruebytracklength = new TH1D("htrecminusttruebytracklength","",1000,-30.,30.);
      TH1D* htrecminusttruebydistancestop = new TH1D("htrecminusttruebydistancestop","",1000,-30.,30.);
      TH1D* htrecminusttruebyPMTPosition = new TH1D("htrecminusttruebyPMTPosition","",1000,-30.,700.);
      TH1D* htrecminusttruebyPMTPositionlog = new TH1D("htrecminusttruebyPMTPositionlog","",1000,-30.,700.);
      TH1D* hnbytracklength = new TH1D("hnbytracklength","",1000,1.3,1.5);
      TH1D* hnbytracklengthnotPMT = new TH1D("hnbytracklengthnotPMT","",1000,1.3,1.5);
      TH1D* henergy = new TH1D("henergy","",1000,1e-6,5e-6);
      TH2D* henergyvsn = new TH2D("henergyvsn","",1000,1e-6,5e-6,1000,1.3,1.6);
      TH2D* henergyvsnbytracklength = new TH2D("henergyvsnbytracklength","",100,1e-6,5e-6,100,1.3,1.5);
      TH2D* henergyvsvelocitybytracklength = new TH2D("henergyvsvelocitybytracklength","",200,1e-6,5e-6,200,20.,23.);
      TH1D* hflytime = new TH1D("hflytime","",1000,0.,700.);
      TH1D* hdistance = new TH1D("hdistance","",1000,0.,3000.);
      TH2D* hflytimevsdistance = new TH2D("hflytimevsdistance","",1000,0.,700.,1000,0.,4000.);
      TH2D* htracklengthvsdistance = new TH2D("htracklengthvsdistance","",1000,0.,10000.,1000,0.,4000);
      TH2D* hflytimevsn = new TH2D("hflytimevsn","",1000,0.,700.,1000,1.3,1.6);
      TH2D* hdistancevsn = new TH2D("hdistancevsn","",1000,0.,4000.,1000,1.3,1.6);
      TH1D* hstartdistance = new TH1D("hstartdistance","",1000,0.,20.);
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
	  int Ntrack = wcsimroottrigger->GetNtrack();
	  for(int k = 0;k < Ntrack;k++)
	    {
	      WCSimRootTrack* wcsimroottrack = (WCSimRootTrack*)wcsimroottrigger->GetTracks()->At(k);
	      if((wcsimroottrack->GetStopvol() != 20))
		{
		  double velocitybytracklength = (wcsimroottrack->GetTrackLength()/10.)/wcsimroottrack->GetFlyTime();
		  double nbytracklength = v_light/velocitybytracklength;
		  hnbytracklengthnotPMT->Fill(nbytracklength);
		}
		
	      int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
	      for(int l = 0;l < ncherenkovdigihits;l++)
		{
		  WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(l));
		  if((wcsimroottrack->GetId() == hit->GetTrackId()))
		    {
		      CLHEP::Hep3Vector startvec(wcsimroottrack->GetStart(0),wcsimroottrack->GetStart(1),wcsimroottrack->GetStart(2));
		      CLHEP::Hep3Vector stopvec(wcsimroottrack->GetStop(0),wcsimroottrack->GetStop(1),wcsimroottrack->GetStop(2));
		      hstartdistance->Fill((startvec - vectrue).mag());
		      double distance = (stopvec - startvec).mag();
		      hdistance->Fill(distance);
		      double velocity = distance/wcsimroottrack->GetFlyTime();
		      double velocitybytracklength = (wcsimroottrack->GetTrackLength()/10.)/wcsimroottrack->GetFlyTime();
		      henergyvsvelocitybytracklength->Fill(wcsimroottrack->GetE(),velocitybytracklength);
		      double nbytracklength = v_light/velocitybytracklength;
		      double ttrue = wcsimroottrack->GetFlyTime();
		      hflytime->Fill(wcsimroottrack->GetFlyTime());
		      hflytimevsdistance->Fill(wcsimroottrack->GetFlyTime(),distance);
		      double n = v_light/velocity;
		      h5->Fill(n);
		      hnbytracklength->Fill(nbytracklength);
		      hflytimevsn->Fill(wcsimroottrack->GetFlyTime(),n);
		      hdistancevsn->Fill(distance,n);
		      double trecminusttrue = -distance/velocityfixed + ttrue;
		      h1->Fill(trecminusttrue);
		      int tubeId = hit->GetTubeId();
		      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId - 1);
		      CLHEP::Hep3Vector pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
		      double distancerec = (pmtposition - vectrue).mag();
		      double distancestop = (stopvec - vectrue).mag();
		      double trec = wcsimroottrigger->GetTriggerTime() + hit->GetT() - offset;
		      double trecminusttruebytracklength = trec - (wcsimroottrack->GetTrackLength()/10.)/velocityfixed;
		      double trecminusttruebyPMTPosition = trec - (distancerec - doffsetfixed)/velocityfixed;
		      double trecminusttruebydistancestop = trec - distancestop/velocityfixed;
		      h3->Fill(distancerec - distance);
		      h4->Fill(trec,ttrue);
		      henergy->Fill(wcsimroottrack->GetE());
		      henergyvsn->Fill(wcsimroottrack->GetE(),n);
		      henergyvsnbytracklength->Fill(wcsimroottrack->GetE(),nbytracklength);
		      htracklengthvsdistance->Fill(wcsimroottrack->GetTrackLength()/10.,distance);
		      htrecminusttruebytracklength->Fill(trecminusttruebytracklength + toffset);
		      htrecminusttruebyPMTPosition->Fill(trecminusttruebyPMTPosition + toffset);
		      htrecminusttruebydistancestop->Fill(trecminusttruebydistancestop + toffset);
		    }
		}
	    }
	}
      for(int i = 1; i < h1->GetXaxis()->GetNbins();i++)
	{
	  if(h1->GetBinContent(i) != 0)
	    h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
	}
      for(int i = 1; i < htrecminusttruebyPMTPosition->GetXaxis()->GetNbins();i++)
	{
	  if(htrecminusttruebyPMTPosition->GetBinContent(i) != 0)
	    htrecminusttruebyPMTPositionlog->Fill(htrecminusttruebyPMTPosition->GetXaxis()->GetBinCenter(i),std::log(htrecminusttruebyPMTPosition->GetBinContent(i)));
	}
      htrecminusttruebyPMTPositionlog->SetStats(0);
      htrecminusttruebyPMTPositionlog->Draw();
      //      TF1* f1 = new TF1("f1",ninwatertrue,1e-6,5e-6,2);
      app.Run();
      delete h1;
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
		  
