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
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      std::string retrotype = Getchar("RETROTYPE");
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string",retrotype));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY")));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",Getdouble("POSITIONCENTERX")));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      if(retrotype != "NoRetro"){
	filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY")));
      }
      filemanager->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH1D* h1 = new TH1D("h1",Getchar("HISTTITLE"),Getint("HISTBINNUM"),Getdouble("HISTMIN"),Getdouble("HISTMAX"));
      manager->SetTH1DEvent(h1,Getchar("XVALUE"),"number","test");
      TCanvas* c1 = new TCanvas("c1","");
      h1->SetStats(0);
      h1->Draw("samehist");
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
