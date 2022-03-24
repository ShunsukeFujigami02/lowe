#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TLine.h>
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
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/wcsim_20211101_102748.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH1D* h1 = new TH1D("h1","",1000,-300.,0.);
      std::vector<double> minimizedvalue = manager->SetTH1DFunctionDis(h1,"returnvalue",4,3,"true",0,"test","goodnessnoretro");
      TLine* l1 = new TLine(minimizedvalue[0],0.,minimizedvalue[0],3000.);
      TCanvas* c1 = new TCanvas("c1","");
      h1->Draw("hist");
      l1->Draw("same");
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
