#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TLegend.h>
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
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",5.));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",1.0));
      filemanager->reflectNarrowDownTag("Minimize");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH1D* h1 = new TH1D("h1","",100,0.,3.141592);
      TH1D* h2 = new TH1D("h2","",100,0.,3.141592);
      manager->SetTH1DEvent(h1,"deltaanglebylikelihood","number","test");
      manager->SetTH1DEvent(h2,"deltaanglebyminimize","number","test");
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.6,0.68,0.99,0.88);
      h1->SetLineColor(2);
      h2->SetLineColor(4);
      l1->AddEntry(h1,"angle error by grid search","l");
      l1->AddEntry(h2,"angle error by minimize","l");
      h1->SetStats(0);
      h2->SetStats(0);
      h2->Draw("samehist");
      h1->Draw("samehist");
      l1->Draw("same");
      app.Run();
      delete h2;
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
