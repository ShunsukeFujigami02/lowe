#include "distanceerror.hh"
#include <TRint.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <memory>
#include <exception>
#include <iostream>

void distanceerror_drawfittingparameter_in(double distance,TH1D* hp0,TH1D* hp1,TH1D* hp2);

int main(int argc,char** argv)
{
    try
    {
      TRint app("app",&argc,argv);
      int distancenumber = 100;
      double distancemin = 30.;
      double distancemax = 3000.;
      double logdistancemin = std::log(distancemin);
      double logdistancemax = std::log(distancemax);
      double logdistancewidth = (logdistancemax - logdistancemin)/distancenumber;
      TH1D* hp0 = new TH1D("hp0","",distancenumber+1,logdistancemin - logdistancewidth/2.,logdistancemax + logdistancewidth/2.);
      TH1D* hp1 = new TH1D("hp1","",distancenumber+1,logdistancemin - logdistancewidth/2.,logdistancemax + logdistancewidth/2.);
      TH1D* hp2 = new TH1D("hp2","",distancenumber+1,logdistancemin - logdistancewidth/2.,logdistancemax + logdistancewidth/2.);
      for(double logdistance = logdistancemin;logdistance < logdistancemax + logdistancewidth/2.;logdistance+=logdistancewidth)
	{
	  distanceerror_drawfittingparameter_in(std::exp(logdistance),hp0,hp1,hp2);
	}
      app.Run();
      delete hp0;
      delete hp1;
      delete hp2;
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

void distanceerror_drawfittingparameter_in(double distance,TH1D* hp0,TH1D* hp1,TH1D* hp2)
{
  int costhetanumber = 100;
  double costhetamin = 0.01;
  double costhetamax = 0.999;
  double costhetawidth = (costhetamax - costhetamin)/costhetanumber;
  TH1D* h1 = new TH1D("hcostheta","",costhetanumber + 1,costhetamin - costhetawidth/2.,costhetamax + costhetawidth/2.);
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
  TF1* f1 = new TF1("f1","pol2",costhetamin,costhetamax);
  h1->Fit(f1,"Rn");
  hp0->Fill(std::log(distance),f1->GetParameter(0));
  hp1->Fill(std::log(distance),f1->GetParameter(1));
  hp2->Fill(std::log(distance),f1->GetParameter(2));
  delete f1;
  delete h1;
}

