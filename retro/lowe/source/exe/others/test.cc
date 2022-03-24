#include <TH2D.h>
#include <TRint.h>
#include <TCanvas.h>
#include <exception>
#include <iostream>
#include "distanceerror.hh"
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      int distancenumber = 1000;
      double distancemin = 30.;
      double distancemax = 4000.;
      double distancewidth = (distancemax - distancemin)/distancenumber;
      int costhetanumber = 1000;
      double costhetamin = 0.01;
      double costhetamax = 0.999;
      double costhetawidth = (costhetamax - costhetamin)/costhetanumber;
      
      TH2D* h1 = new TH2D("h1","",distancenumber + 1,distancemin - distancewidth/2.,distancemax + distancewidth/2.,costhetanumber + 1,costhetamin - costhetawidth/2.,costhetamax + costhetawidth/2.);
      for(double distance = distancemin;distance < distancemax + distancewidth/2.;distance+=distancewidth)
	{
	  std::cout << "distance = " << distance << std::endl;
	  for(double costheta = costhetamin;costheta < costhetamax + costhetawidth/2.;costheta+=costhetawidth)
	    {
	      std::cout << "costheta = " << costheta << std::endl;
	      double mean = direcminusdtrue_direct(distance,costheta);
	      h1->Fill(distance,costheta,mean);
	    }
	}
      TCanvas* c1 = new TCanvas("c1","");
      h1->Draw("colz");
      app.Run();
      delete h1;
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

  
