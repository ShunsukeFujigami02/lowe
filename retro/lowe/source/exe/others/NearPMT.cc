#include <TFile.h>
#include <TTree.h>
#include "WCSimRootGeom.hh"
#include <vector>
#include <cmath>
int main()
{
  TFile* fin = new TFile("/rhome/fujigami/retro/lowe/analizefile/wcsim_20210503_190725.root");
  TTree *wcsimGeoT = (TTree*)fin->Get("wcsimGeoT");
  WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile* fout = new TFile("/rhome/fujigami/retro/lowe/NearPMT.root","recreate");
  TTree* tree = new TTree("NearPMT","title");
  std::vector<int> iNearPMT;
  std::vector<double> distanceNearPMT;
  tree->Branch("iNearPMT",&iNearPMT);
  tree->Branch("distanceNearPMT",&distanceNearPMT);
  int wcnumpmt = wcsimrootgeom->GetWCNumPMT();
  for(int i = 0;i < wcnumpmt;++i)
    {
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(i);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      std::vector<int> iNearPMTtemp;
      std::vector<double> distanceNearPMTtemp;
      double distancemax = 0.;
      size_t posmax = 0;
      for(int j = 0;j < wcnumpmt;++j)
	{
	  if(i != j)
	    {
	      WCSimRootPMT pmtcompare = wcsimrootgeom->GetPMT(j);
	      double pmtcompareX = pmtcompare.GetPosition(0);
	      double pmtcompareY = pmtcompare.GetPosition(1);
	      double pmtcompareZ = pmtcompare.GetPosition(2);
	      double distance = std::sqrt((pmtX - pmtcompareX)*(pmtX - pmtcompareX) + (pmtY - pmtcompareY)*(pmtY - pmtcompareY) + (pmtZ - pmtcompareZ)*(pmtZ - pmtcompareZ));
	      if(iNearPMTtemp.size() < 9)
		{
		  iNearPMTtemp.push_back(j);
		  distanceNearPMTtemp.push_back(distance);
		  if(distance > distancemax)
		    {
		      distancemax = distance;
		      posmax = iNearPMTtemp.size() - 1;
		    }
		}
	      else
		{
		  if(distance < distancemax)
		    {
		      iNearPMTtemp[posmax] = j;
		      distanceNearPMTtemp[posmax] = distance;
		      double distancemaxtemp = 0.;
		      for(size_t k = 0;k < distanceNearPMTtemp.size();k++)
			{
			  if(distanceNearPMTtemp[k] > distancemaxtemp)
			    {
			      distancemaxtemp = distanceNearPMTtemp[k];
			      posmax = k;
			    }
			}
		      distancemax = distancemaxtemp;
		    } 
		}
	    }
	}
      iNearPMT = iNearPMTtemp;
      distanceNearPMT = distanceNearPMTtemp;
      tree->Fill();
    }
  fout->Write();
  fout->Close();
}

	  
	  
