#include "config.hh"
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TRint.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>
#include "MinimizeRefractiveandDistanceFunction.hh"
int main(int argc,char**argv)
{
  const char* infile = "/rhome/fujigami/retro/lowe/analizefile/wcsim_20210718_135607.root";
  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin");
  min->SetMaxFunctionCalls(1000);
  min->SetMaxIterations(1000);
  min->SetTolerance(0.1);
  MinimizeRefractiveandDistanceFunction* function = new MinimizeRefractiveandDistanceFunction(infile);
  ROOT::Math::Functor f(function,&MinimizeRefractiveandDistanceFunction::returnminimizedfunctioncutanglepeakaddflyparticle,4);
  min->SetFunction(f);
  min->SetLimitedVariable(0,"n",1.386,0.0001,1.3,1.4);
  min->SetLimitedVariable(1,"doffsetwall",-40.,0.1,-100.,100.);
  min->SetLimitedVariable(2,"doffsetcap",-20.,0.1,-100.,100.);
  min->SetLimitedVariable(3,"dflyparticle",70.,0.1,0.,100.);
  min->SetPrintLevel(1);
  if(!min->Minimize())
    {
      std::cout << "failed to minimize" << std::endl;
    }
  min->PrintResults();
  TRint app("app",&argc,argv);
  //  double n = 1.3907;
  /*
  int searchnumberX = 10;
  double searchminX = 1.38;
  double searchmaxX = 1.4;
  double searchwidthX = (searchmaxX - searchminX)/searchnumberX;
  int searchnumberY = 10;
  double searchminY = -100.;
  double searchmaxY = 100.;
  double searchwidthY = (searchmaxY - searchminY)/searchnumberY;
  int searchnumberZ = 10;
  double searchminZ = -100.;
  double searchmaxZ = 100.;
  double searchwidthZ = (searchmaxZ - searchminZ)/searchnumberZ;
  int searchnumberA = 10;
  double searchminA = 0.;
  double searchmaxA = 100.;
  double searchwidthA = (searchmaxA - searchminA)/searchnumberA;
  //  double doffset = 0.;
  //  TH2D* h1 = new TH2D("h1","",searchnumberX + 1,searchminX - searchwidthX/2.,searchmaxX + searchwidthX/2.,searchnumberY + 1,searchminY - searchwidthY/2.,searchmaxY + searchwidthY/2.);
  //  TH2D* h2 = new TH2D("h2","",searchnumberX + 1,searchminX - searchwidthX/2.,searchmaxX + searchwidthX/2.,searchnumberY + 1,searchminY - searchwidthY/2.,searchmaxY + searchwidthY/2.);
  std::vector<double> maxX(4);
  double maxvalue = 1000.;
  for(double n = searchminX;n < searchmaxX + searchwidthX/2.;n+=searchwidthX)
    {
      for(double doffsetwall = searchminY;doffsetwall < searchmaxY + searchwidthY/2.;doffsetwall+=searchwidthY)
	{
	  for(double doffsetcap = searchminZ;doffsetcap < searchmaxZ + searchwidthZ/2.;doffsetcap+=searchwidthZ)
	    {
	      for(double dfly = searchminA;dfly < searchmaxA + searchwidthA/2.;dfly+=searchwidthA)
		{
		  double a[4];
		  a[0] = n;
		  a[1] = doffsetwall;
		  a[2] = doffsetcap;
		  a[3] = dfly;
		  std::cout << "n = " << n << std::endl;
		  std::cout << "doffsetwall = " << doffsetwall << std::endl;
		  std::cout << "doffsetcap = " << doffsetcap << std::endl;
		  std::cout << "dfly = " << dfly << std::endl;
		  double returnvalue = function->returnminimizedfunctioncutanglepeakaddflyparticle(a);
		  if(maxvalue > returnvalue)
		    {
		      maxvalue = returnvalue;
		      maxX[0] = n;
		      maxX[1] = doffsetwall;
		      maxX[2] = doffsetcap;
		      maxX[3] = dfly;
		    }
		}
	    }
	} 
    }
  std::cout << "max n = " << maxX[0] << std::endl;
  std::cout << "max doffsetwall = " << maxX[1] << std::endl;
  std::cout << "max doffsetcap = " << maxX[2] << std::endl;
  std::cout << "max dfly = " << maxX[3] << std::endl;
  double amax[4] = {maxX[0],maxX[1],maxX[2],maxX[3]} ;
  function->returnminimizedfunctioncutanglepeakaddflyparticle(amax);
  //  h1->Draw("colz");
  */
  app.Run();
}
