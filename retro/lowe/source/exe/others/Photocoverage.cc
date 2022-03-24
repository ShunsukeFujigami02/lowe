#include <TFile.h>
#include <TH2D.h>
#include <cmath>
#include <iostream>

int main()
{
  TFile* file = new TFile("/rhome/fujigami/retro/lowe/Photocoverage.root","recreate");
  TH2D* h1 = new TH2D("hcoverage","",101,-0.445,89.445,101,-0.45,90.45);
  double thetamin = 0.;
  double thetamax = 89.;
  int thetanum = 100;
  double thetawidth = (thetamax - thetamin)/thetanum;
  double phimin = 0.;
  double phimax = 90.;
  int phinum = 100;
  double phiwidth = (phimax - phimin)/phinum;
  double startxmin = 0.; // (m)
  double startxmax = 100.; // (m)
  int startxnum = 100;
  double startxwidth = (startxmax - startxmin)/startxnum;
  double startymin = 0.; // (m)
  double startymax = 100.; // (m)
  int startynum = 100;
  double startywidth = (startymax - startymin)/startynum;
  double startz = 0.4; // (m)
  double PMTdistance = 0.707; // (m)
  double distancebase = PMTdistance/std::sqrt(2.);
  double PMTRadius = 0.26921; // (m)
  double PMTRadius2 = PMTRadius*PMTRadius;
  double PMTOffset = 0.08921; // (m)
  double pi = std::acos(-1.);
  for(double theta = thetamin;theta < thetamax + thetawidth/2.;theta+=thetawidth)
    {
      for(double phi = phimin;phi < phimax + phiwidth/2.;phi+=phiwidth)
	{
	  std::cout << "theta = " << theta << ", phi = " << phi << std::endl;
	  double xgrad = std::cos(pi*phi/180.)*std::sin(pi*theta/180.);
	  double ygrad = std::sin(pi*phi/180.)*std::sin(pi*theta/180.);
	  double zgrad = -std::cos(pi*theta/180.);
	  std::cout << "xgrad,ygrad,zgrad = " << xgrad << "," << ygrad << "," << zgrad << std::endl;
	  double tneardeno = xgrad*xgrad + ygrad* ygrad;
	  double distancedeno = std::sqrt(tneardeno);
	  int counter = 0;
	  int counterall = 0;
	  int numiter = 0;
	  for(double startx = startxmin;startx < startxmax + startxwidth/2.;startx+=startxwidth)
	    {
	      for(double starty = startymin;starty < startymax + startywidth/2.;starty+=startywidth)
		{
		  int startm = (int)(startx/PMTdistance);
		  int startn = (int)(starty/PMTdistance);
		  int m = startm;
		  int n = startn;
		  double xcenter = m*PMTdistance + PMTdistance/2.;
		  double ycenter = n*PMTdistance + PMTdistance/2.;
		  while(true)
		    {
		      double startxminusxcenter = startx - xcenter;
		      double startyminusycenter = starty - ycenter;
		      double a = xgrad*xgrad + ygrad*ygrad + zgrad*zgrad;
		      double bprime = xgrad*startxminusxcenter + ygrad*startyminusycenter + zgrad*startz;
		      double c = startxminusxcenter*startxminusxcenter + startyminusycenter*startyminusycenter + startz*startz - PMTRadius2;
		      double discri = bprime*bprime - a*c;
		      if(discri > 0.)
			{
			  counterall++;
			  double tminus = (-bprime - std::sqrt(discri))/a;
			  double zcross = zgrad*tminus + startz;
			  if(zcross > PMTOffset)
			    {
			      counter++;
			      break;
			    }
			  break;
			}
		      double tnear = (xgrad*(xcenter - startx) + ygrad*(ycenter - starty))/tneardeno;
		      double znear = zgrad*tnear + startz;
		      if(znear < PMTOffset)
			{
			  counterall++;
			  break;
			}
		      double xcentertemp = xcenter + PMTdistance;
		      double pointlinedistancemplus = std::abs(ygrad * xcentertemp - xgrad * ycenter + (xgrad*starty - ygrad*startx))/distancedeno;
		      if(pointlinedistancemplus < distancebase)
			{
			  xcenter = xcentertemp;
			  numiter++;
			  continue;
			}
		      double ycentertemp = ycenter + PMTdistance;
		      double pointlinedistancenplus = std::abs(ygrad * xcenter - xgrad * ycentertemp + (xgrad*starty - ygrad*startx))/distancedeno;
		      if(pointlinedistancenplus < distancebase)
			{
			  ycenter = ycentertemp;
			  numiter++;
			  continue;
			}
		      counterall++;
		      break;
		    }
		}
	    }
	  std::cout << "numiter = " << numiter << std::endl;
	  double coverage = (double)counter/(double)counterall;
	  std::cout << "coverage = " << coverage << std::endl;
	  h1->Fill(theta,phi,coverage);
	}
    }
  file->Write();
  file->Close();
}
      
		      
