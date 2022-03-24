// C++ STL
#include <iostream>

// WCSim library
#include "WCSimRootEvent.hh"

// ROOT library
#include <TFile.h>
#include <TTree.h>

// self-introduced library
#include "efficiency.hh"

ClassImp(efficiency)

efficiency::efficiency():TH1D()
{
}

efficiency::efficiency(FileList* filelist_in,const char* name,const char* title,int num,double min,double max,double width)
  :TH1D(name,title,num,min-width/2.,max+width/2.)
{
  filelist.Copy(*filelist_in);
  double iter = min;
  for(int i = 0; i < num ; i++, iter += width)
    {
      fillloop(i,iter);
    }
  GetYaxis()->SetRangeUser(0.,1.1);
  SetStats(0);
}

void efficiency::fillloop(int i,double iter)
{
  TFile* file = (TFile*)filelist.At(i);
  TTree* wcsimT = (TTree*)file->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  int ntrigger = 0;
  Nevent = wcsimT->GetEntries();
  for(int i = 0;i < Nevent; i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      if(wcsimroottrigger->GetNcherenkovdigihits() != 0)
	{
	  ntrigger++;
	}
    }
  double eff = (double)ntrigger/(double)Nevent;
  Fill(iter,eff);
  delete wcsimrootevent;
}

void efficiency::SetEfError()
{
  for(int i = 0;i < filelist.GetEntries();i++)
    {
      double p = GetBinContent(i+1);
      double sigma = std::sqrt(p*(1-p)/Nevent);
      SetBinError(i+1,sigma);
    }
}

