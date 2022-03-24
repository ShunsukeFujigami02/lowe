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
#include <TLegend.h>
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
      filemanager->reflectNarrowDownTag("Minimize");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      TH2D* h1 = new TH2D("h1",Getchar("HISTTITLE"),Getint("HISTXBINNUM"),Getdouble("HISTXMIN"),Getdouble("HISTXMAX"),Getint("HISTYBINNUM"),Getdouble("HISTYMIN"),Getdouble("HISTYMAX"));
      int ievent = 1;
      //      std::vector<double> value = manager->SetTH2DFunctionDisTrueaxis(h1,"returnvalue",7,4,5,"true",ievent,"test","likelihooddirectionsum");
      gStyle->SetPalette(1);
      //      TMarker* m1 = new TMarker(value[0],value[1],20); // minimized
      //      TMarker* m2 = new TMarker(value[2],value[3],5); // before minimize
      //      TMarker* m3 = new TMarker(value[4],value[5],3); // true
      manager->SetTH2DFunctionDisTrueaxismultievent(h1,"returnvalue",Getint("PARANUM"),Getint("XPARANUM"),Getint("YPARANUM"),"true",Getint("NEVENT"),"test",Getchar("FUNCTIONNAME"));
      TCanvas* c1 = new TCanvas("c1","");
      h1->SetStats(0);
      h1->Draw("colz");
      //      m1->Draw("same");
      //      m2->Draw("same");
      //      m3->Draw("same");
      //      TLegend* l1 = new TLegend(0.5,0.68,0.89,0.88);
      //      l1->AddEntry(m1,"minimized","p");
      //      l1->AddEntry(m2,"before minimize","p");
      //      l1->AddEntry(m3,"true","p");
      //      l1->Draw("same");
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
