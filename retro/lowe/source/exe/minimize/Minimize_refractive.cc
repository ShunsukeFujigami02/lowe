#include "config.hh"
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TRint.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>
#include "MinimizeRefractiveFunction.hh"
int main(int argc,char**argv)
{
  const char* infile = "/rhome/fujigami/retro/lowe/analizefile/wcsim_20210718_135607.root";
  //  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer();
  //  min->SetMaxFunctionCalls(1000);
  //  min->SetMaxIterations(1000);
  //  min->SetTolerance(0.000000001);
  MinimizeRefractiveFunction* function = new MinimizeRefractiveFunction(infile);
  //  ROOT::Math::Functor f(function,&MinimizeRefractiveFunction::returnvalue,1);
  //  min->SetFunction(f);
  //  min->SetVariable(0,"n",1.333,0.00001);
  //  min->Minimize();
  TRint app("app",&argc,argv);
  int searchnumber = 100;
  double searchmin = 1.37;
  double searchmax = 1.4;
  double searchwidth = (searchmax - searchmin)/searchnumber;
  TH1D* hmean = new TH1D("hmean","",searchnumber + 1,searchmin - searchwidth/2.,searchmax + searchwidth/2.);
  TH1D* hpeak = new TH1D("hpeak","",searchnumber + 1,searchmin - searchwidth/2.,searchmax + searchwidth/2.);
  for(double n = searchmin;n < searchmax + searchwidth/2.;n+=searchwidth)
    {
      double a[1];
      a[0] = n;
      std::cout << "n = " << n << std::endl;
      std::vector<double> meanandpeak = function->returnmeanandpeak(a);
      hmean->Fill(n,meanandpeak[0]);
      hpeak->Fill(n,meanandpeak[1]);
    }
  TH1D* h1 = new TH1D("h1","",400,-40.,40.);
  TH1D* hlog = new TH1D("hlog","",400,-40.,40.);
  double b[1];
  b[0] = 1.37942;
  function->Filltofhist(h1,hlog,b);
  h1->Draw();
  app.Run();
  //  min->PrintResults();
  
}

