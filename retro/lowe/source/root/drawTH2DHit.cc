#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TCanvas.h>
#include <exception>
#include <iostream>
#include <string>
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      TPython::Exec("import macro");
      TPython::Exec("import func");
      TPython::Exec("import ROOT");
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/tof_20210713_212605.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH2D* h1 = new TH2D("h1","",400,0.6,1.,400,-20.,20.);
      manager->SetTH2DAllHit(h1,"PMTacceptancecosangle","emittimeerrortrue","number","test","CylLoc == 1");
      TH2D* h2 = new TH2D("h2","",400,0.6,1.,400,-20.,20.);
      for(int i = 1;i < h1->GetXaxis()->GetNbins()+1;i++)
	{
	  double max = 0.;
	  int maxj = 1;
	  for(int j = 1;j < h1->GetYaxis()->GetNbins()+1;j++)
	    {
	      double binvalue = h1->GetBinContent(i,j);
	      if(max < binvalue)
		{
		  max = binvalue;
		  maxj = j;
		}
	    }
	  if(max > 10.)
	    {
	      h2->Fill(h1->GetXaxis()->GetBinCenter(i),h1->GetYaxis()->GetBinCenter(maxj));
	    }
	}
      TCanvas* c1 = new TCanvas("c1","");
      //      c1->DrawFrame(-20.,0.,20.,1.);
      h1->Draw("samecolz");
      app.Run();
      delete h1;
      delete manager;
      delete filemanager;
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
