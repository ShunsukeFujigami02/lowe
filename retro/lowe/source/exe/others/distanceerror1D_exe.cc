#include "distanceerror.hh"
#include <TRint.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <memory>
#include <exception>
#include <iostream>

int main(int argc,char** argv)
{
    try
    {
      TRint app("app",&argc,argv);
      double distance = 400.;
      int costhetanumber = 100;
      double costhetamin = 0.01;
      double costhetamax = 0.999;
      double costhetawidth = (costhetamax - costhetamin)/costhetanumber;
      
      TH1D* h1 = new TH1D("h1","",costhetanumber + 1,costhetamin - costhetawidth/2.,costhetamax + costhetawidth/2.);
      for(double costheta = costhetamin;costheta < costhetamax + costhetawidth/2.;costheta+=costhetawidth)
	{
	  std::cout << "costheta = " << costheta << std::endl;
	  std::shared_ptr<distanceerror> de = std::make_shared<distanceerror>();
	  de->Setd(distance);
	  de->SetCosTheta(costheta);
	  double mean = de->GetMean(100000);
	  std::cout << "mean = " << mean << std::endl;
	  h1->Fill(costheta,mean);
	}
      TCanvas* c1 = new TCanvas("c1","");
      h1->Draw();
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
