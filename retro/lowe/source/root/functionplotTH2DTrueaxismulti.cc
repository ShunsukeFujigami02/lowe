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
#include <TMarker.h>
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
      AnalizeFile file("/rhome/fujigami/retro/lowe/analizefile/Minimize_20210617_150927.csv");
      filemanager->selectedfile.push_back(file);
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      manager->SetData();
      TH2D* h1 = new TH2D("h1","",100,-1000.,1000.,100,-50.,50.);
      int ievent = 0;
      std::vector<double> value = manager->SetTH2DFunctionDisTrueaxis(h1,"GetDirectPart",2,3,"minimized",ievent,"test");
      TMarker* m1 = new TMarker(value[0],value[1],20);
      TMarker* m2 = new TMarker(value[2],value[3],5);
      TCanvas* c1 = new TCanvas("c1","");
      h1->SetStats(0);
      h1->Draw("colz");
      m1->Draw("same");
      m2->Draw("same");
      app.Run();
      delete h1;
      delete m1;
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
