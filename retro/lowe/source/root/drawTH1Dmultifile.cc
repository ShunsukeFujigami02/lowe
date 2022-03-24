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
#include <TF1.h>
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);

      int filenumber = Getint("FILENUMBER");
      
      AnalizeManager* manager = new AnalizeManager();
      FileManager* filemanager1 = new FileManager();
      filemanager1->SetAllFile();
      std::string retrotype1 = Getchar("RETROTYPE1");
      filemanager1->narrowdowntag.push_back(AnalizeTag("RetroType","string",retrotype1));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",Getdouble("POSITIONCENTERX1")));
      filemanager1->narrowdowntag.push_back(AnalizeTag("GoodnessType","string",Getchar("GOODNESSTYPE1")));
      filemanager1->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY1")));
      filemanager1->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      if(retrotype1 == "OnRetro")
	filemanager1->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY1")));
      std::string narrowdowntag1 = Getchar("NARROWDOWNTAG1");
      if(narrowdowntag1 == "Energy"){
	std::string energyfuncname1 = Getchar("ENERGYFUNCTIONNAME1");
	filemanager1->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname1));
      }
      filemanager1->reflectNarrowDownTag(narrowdowntag1);
      std::cout << "file number is " << filemanager1->selectedfilemap.size() << std::endl;
      filemanager1->printselectedfile();
      manager->cpFileList(filemanager1,"file1");
      TH1D* h1 = new TH1D("h1",Getchar("HISTTITLE"),Getint("HISTNUM"),Getdouble("HISTMIN"),Getdouble("HISTMAX"));
      manager->SetTH1DEvent(h1,Getchar("XVALUE1"),"number","file1");
      
      FileManager* filemanager2 = new FileManager();
      filemanager2->SetAllFile();
      std::string retrotype2 = Getchar("RETROTYPE2");
      filemanager2->narrowdowntag.push_back(AnalizeTag("RetroType","string",retrotype2));
      filemanager2->narrowdowntag.push_back(AnalizeTag("GoodnessType","string",Getchar("GOODNESSTYPE2")));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",Getdouble("POSITIONCENTERX2")));
      filemanager2->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY2")));
      filemanager2->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      if(retrotype2 == "OnRetro")
	filemanager2->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY2")));
      std::string narrowdowntag2 = Getchar("NARROWDOWNTAG2");
      if(narrowdowntag2 == "Energy"){
	std::string energyfuncname2 = Getchar("ENERGYFUNCTIONNAME2");
	filemanager2->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname2));
      }
      filemanager2->reflectNarrowDownTag(narrowdowntag2);
      std::cout << "file number is " << filemanager2->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager2,"file2");
      TH1D* h2 = new TH1D("h2",Getchar("HISTTITLE"),Getint("HISTNUM"),Getdouble("HISTMIN"),Getdouble("HISTMAX"));
      manager->SetTH1DEvent(h2,Getchar("XVALUE2"),"number","file2");
	
      FileManager* filemanager3 = new FileManager();
      filemanager3->SetAllFile();
      std::string retrotype3 = Getchar("RETROTYPE3");
      filemanager3->narrowdowntag.push_back(AnalizeTag("RetroType","string",retrotype3));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",Getdouble("POSITIONCENTERX3")));
      filemanager3->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY3")));
      filemanager3->narrowdowntag.push_back(AnalizeTag("GoodnessType","string",Getchar("GOODNESSTYPE3")));
      filemanager3->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      if(retrotype3 == "OnRetro")
	filemanager3->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY3")));
      std::string narrowdowntag3 = Getchar("NARROWDOWNTAG3");
      if(narrowdowntag3 == "Energy"){
	std::string energyfuncname3 = Getchar("ENERGYFUNCTIONNAME3");
	filemanager3->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname3));
      }
      filemanager3->reflectNarrowDownTag(narrowdowntag3);
      std::cout << "file number is " << filemanager3->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager3,"file3");
      TH1D* h3 = new TH1D("h3",Getchar("HISTTITLE"),Getint("HISTNUM"),Getdouble("HISTMIN"),Getdouble("HISTMAX"));
      manager->SetTH1DEvent(h3,Getchar("XVALUE3"),"number","file3");

      FileManager* filemanager4 = new FileManager();
      filemanager4->SetAllFile();
      std::string retrotype4 = Getchar("RETROTYPE4");
      filemanager4->narrowdowntag.push_back(AnalizeTag("RetroType","string",retrotype4));
      filemanager4->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",Getdouble("POSITIONCENTERX4")));
      filemanager4->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY4")));
      filemanager4->narrowdowntag.push_back(AnalizeTag("GoodnessType","string",Getchar("GOODNESSTYPE4")));
      filemanager4->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager4->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager4->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      if(retrotype4 == "OnRetro")
	filemanager4->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY4")));
      std::string narrowdowntag4 = Getchar("NARROWDOWNTAG4");
      if(narrowdowntag4 == "Energy"){
	std::string energyfuncname4 = Getchar("ENERGYFUNCTIONNAME4");
	filemanager4->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname4));
      }
      filemanager4->reflectNarrowDownTag(narrowdowntag4);
      std::cout << "file number is " << filemanager4->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager4,"file4");
      TH1D* h4 = new TH1D("h4",Getchar("HISTTITLE"),Getint("HISTNUM"),Getdouble("HISTMIN"),Getdouble("HISTMAX"));
      manager->SetTH1DEvent(h4,Getchar("XVALUE4"),"number","file4");
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(Getdouble("LEGENDXMIN"),Getdouble("LEGENDYMIN"),Getdouble("LEGENDXMAX"),Getdouble("LEGENDYMAX"));
      l1->AddEntry(h1,Getchar("LEGENDTITLE1"),"l");
      if(filenumber > 1)
	l1->AddEntry(h2,Getchar("LEGENDTITLE2"),"l");
      if(filenumber > 2)
	l1->AddEntry(h3,Getchar("LEGENDTITLE3"),"l");
      if(filenumber > 3)
	l1->AddEntry(h4,Getchar("LEGENDTITLE4"),"l");
      h1->SetStats(0);
      h1->SetLineColor(1);
      h1->GetYaxis()->SetRangeUser(Getdouble("HISTRANGEMIN"),Getdouble("HISTRANGEMAX"));
      h1->Draw("hist");
      if(filenumber > 1){
	h2->SetStats(0);
	h2->SetLineColor(2);
	h2->Draw("histsame");
      }
      if(filenumber > 2){
	h3->SetStats(0);
	h3->SetLineColor(6);
	h3->Draw("histsame");
      }
      if(filenumber > 3){
	h4->SetStats(0);
	h4->SetLineColor(4);
	h4->Draw("histsame");
      }
      l1->Draw("same");
      app.Run();
      delete h1;
      delete l1;
      delete c1;
      delete manager;
      delete filemanager1;
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
