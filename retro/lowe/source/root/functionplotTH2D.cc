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
#include <TStyle.h>
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/wcsim_20211101_165524.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH2D* h1 = new TH2D("h1","",1000,-400.,0.,1000,-500.,500.);
      int ievent = 70;
      std::vector<double> value = manager->SetTH2DFunctionDis(h1,"returnvalue",7,3,2,"true",0,"test","minimizedfunconretroadddarkratenumaddacceptance");
      gStyle->SetPalette(1);
      //      TMarker* m1 = new TMarker(value[0],value[1],20); // minimized
      //      TMarker* m2 = new TMarker(value[2],value[3],5); // before minimize
      TMarker* m3 = new TMarker(value[4],value[5],3); // true
      TCanvas* c1 = new TCanvas("c1","");
      h1->SetStats(0);
      h1->Draw("colz");
      //      m1->Draw("same");
      //      m2->Draw("same");
      m3->Draw("same");
      app.Run();
      delete h1;
      //      delete m1;
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
