#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TCanvas.h>
#include <exception>
#include <iostream>
#include <string>
#include <TFile.h>
#include "config.hh"
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
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/tof_20210602_182611.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      //      TH1D* h1 = new TH1D("h1","",4000,-1000.,1000.);
      TH1D* h2 = new TH1D("h2","",400,-1.,1.);
      //      TH1D* h3 = new TH1D("h3","",4000,-1000.,1000.);
      //      manager->SetTH1DAllHit(h1,"emittimeerrortrue","number","test");
      manager->SetTH1DAllHit(h2,"openingangle","number","test");
      //      for(int i = 1;i < h1->GetXaxis()->GetNbins();i++)
      //	{
      //	  if(h1->GetBinContent(i) != 0)
      //	    h3->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
      //	}
      TCanvas* c1 = new TCanvas("c1","");
      h2->Draw("same");
      app.Run();
      delete h2;
      //      delete h1;
      //      delete h3;
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
