#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <exception>
#include <iostream>
#include <string>
#include <TStyle.h>
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      FileManager* filemanager0 = new FileManager();
      gStyle->SetPalette(1);
      filemanager0->SetAllFile();
      filemanager0->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",15.));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager0->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("GoodnessType","string","compare_nodigital_ver2"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager0->reflectNarrowDownTag("Minimize");
      std::cout << "file number is " << filemanager0->selectedfilemap.size() << std::endl;
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager0,"test0");
      TH1D* hnoretrog = new TH1D("hnoretrog",";reflectivity;angle resolution",8,0.25,1.05);
      TH1D* hnoretrom = new TH1D("hnoretrom",";reflectivity;angle resolution",8,0.25,1.05);
      for(int j = 0;j < (int)manager->listoffilelist["test0"].size();j++){
	double valueg = 0.;
	double valuem = 0.;
	AnalizeFile file = manager->SetdoubleRun(valueg,"deltaanglebyonesigmalikelihood","test0",j);
	manager->SetdoubleRun(valuem,"deltaanglebyonesigmaminimize","test0",j);
	double reflectivity = 0.;
	file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
	std::cout << "reflectivity = " << reflectivity << std::endl;
	std::cout << "value goodness = " << valueg << std::endl;
	std::cout << "value minimize = " << valuem << std::endl;
	hnoretrog->Fill(reflectivity,valueg);
	hnoretrom->Fill(reflectivity,valuem);
      }
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",15.));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager->narrowdowntag.push_back(AnalizeTag("GoodnessType","string","compare_digital"));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager->reflectNarrowDownTag("Minimize");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager,"test");
      TH1D* honretrog = new TH1D("honretrog",";reflectivity;angle resolution",8,0.25,1.05);
      TH1D* honretrom = new TH1D("honretrom",";reflectivity;angle resolution",8,0.25,1.05);
      for(int j = 0;j < (int)manager->listoffilelist["test"].size();j++){
	double valueg = 0.;
	double valuem = 0.;
	AnalizeFile file = manager->SetdoubleRun(valueg,"deltaanglebyonesigmalikelihood","test",j);
	manager->SetdoubleRun(valuem,"deltaanglebyonesigmaminimize","test",j);
	double reflectivity = 0.;
	file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
	std::cout << "reflectivity = " << reflectivity << std::endl;
	std::cout << "value goodness = " << valueg << std::endl;
	std::cout << "value minimize = " << valuem << std::endl;
	honretrog->Fill(reflectivity,valueg);
	honretrom->Fill(reflectivity,valuem);
      }
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.6,0.68,0.99,0.98);
      l1->AddEntry(hnoretrog,"use gaussian by grid search","l");
      l1->AddEntry(hnoretrom,"use gaussian by minimize","l");
      l1->AddEntry(honretrog,"use N10 by grid search","l");
      l1->AddEntry(honretrom,"use N10 by minimize","l");
      honretrog->SetStats(0);
      hnoretrog->SetStats(0);
      honretrom->SetStats(0);
      hnoretrom->SetStats(0);
      hnoretrog->GetYaxis()->SetRangeUser(0.,0.5);
      hnoretrog->SetLineColor(2);
      honretrog->SetLineColor(3);
      hnoretrom->SetLineColor(1);
      honretrom->SetLineColor(4);
      hnoretrog->Draw("hist");
      honretrog->Draw("samehist");
      hnoretrom->Draw("samehist");
      honretrom->Draw("samehist");
      l1->Draw("same");
      app.Run();
      delete honretrog;
      delete hnoretrog;
      delete honretrom;
      delete hnoretrom;
      delete l1;
      delete c1;
      delete manager;
      delete filemanager;
      delete filemanager0;
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
