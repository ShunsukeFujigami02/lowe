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
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",5.));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",0.3));
      filemanager->reflectNarrowDownTag("wcsim");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      for(auto map : filemanager->selectedfilemap){
	map.second.print();
      }
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH1D* h1 = new TH1D("h1","",1000,-30.,700.);
      TH1D* h2 = new TH1D("h2","",1000,-30.,700.);
      manager->SetTH1DAllHit(h1,"emittimeerrorretrotrue","number","test");
      for(int i = 1; i < h1->GetXaxis()->GetNbins();i++)
	{
	  if(h1->GetBinContent(i) != 0)
	    h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
	}
      TCanvas* c1 = new TCanvas("c1","");
      h2->Draw("histsame");
      app.Run();
      delete h1;
      delete h2;
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
