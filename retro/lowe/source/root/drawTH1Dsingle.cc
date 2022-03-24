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
#include <TStyle.h>
#include <TH2D.h>
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      //      std::cout << Getdouble("TESTVALUE") << std::endl;
      TRint app("app",&argc,argv);
      gStyle->SetPalette(1);
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",15.));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      //      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionFixedX","double",0.));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      //      filemanager->narrowdowntag.push_back(AnalizeTag("Lambda","double",14000.));
      filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",0.3));
      filemanager->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroFinal"));
      filemanager->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH1D* h1 = new TH1D("h1",";N eff direct;# of event",100,0.,200.);
      manager->SetTH1DEvent(h1,"efficienthitsreflect","number","test");
      TCanvas* c1 = new TCanvas("c1","");
      //      h1->SetStats(0);
      h1->Draw("samehist");
      //      TH2D* h2 = new TH2D("h2",";efficient hits direct;distance to Detector(cm)",100,0.,200.,100,0.,500.);
      //      manager->SetTH2DEvent(h2,"efficienthitsdirect","distancetoDetector","number","test");
      //      h2->Draw("histcolz");
      app.Run();
      delete h1;
      delete c1;
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
