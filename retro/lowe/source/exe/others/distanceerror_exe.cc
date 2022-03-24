#include "distanceerror.hh"
#include <TRint.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <memory>
#include <exception>
#include <iostream>

int main(int argc,char** argv)
{
    try
    {
      TRint app("app",&argc,argv);
      TH1D* h1 = new TH1D("h1","",1000,-50.,50.);
      std::shared_ptr<distanceerror> de = std::make_shared<distanceerror>();
      de->Setd(1000.);
      de->SetCosTheta(0.9);
      de->DrawTH1D(h1,1000000);
      std::cout << "mean = " << de->GetMean(1000000) << std::endl;
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
