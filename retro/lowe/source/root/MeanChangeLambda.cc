#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TF1.h>
#include <TRint.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <exception>
#include <iostream>
#include <string>
#include <TStyle.h>
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      double reflectivity = 1.0;
      TRint app("app",&argc,argv);
      AnalizeManager* manager = new AnalizeManager();
      /*      FileManager* filemanagernoretrofar = new FileManager();
      filemanagernoretrofar->SetAllFile();
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("EmitPositionFixedX","double",-1300.));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","fixed"));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",reflectivity));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroFinalver2True"));
      filemanagernoretrofar->narrowdowntag.push_back(AnalizeTag("LambdaRetro","double",5000.));
      filemanagernoretrofar->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanagernoretrofar->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanagernoretrofar,"testnoretrofar");
      TH1D* hist = new TH1D("hist",";rave;# of events",300,0.,300.);
      manager->SetTH1DEvent(hist,"efficienthitsdirect","number","testnoretrofar");
      TH1D* hmeannoretrofar = new TH1D("hmeannoretrofar",";Lambda(cm);mean of effective hits",11,4500.,15500.);
      for(int j = 0;j < (int)manager->listoffilelist["testnoretrofar"].size();j++){
	TH1D* h1 = new TH1D("h1","",300,0.,300.);
	double mean = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthitsreflect","number","testnoretrofar",j);
	double lambdaretro = 0.;
	file.GetTagdouble("LambdaRetro",lambdaretro);
	TF1* f1 = new TF1("f1","gaus",0.,300.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	std::cout << "labmdaRetro = " << lambdaretro << std::endl;
	std::cout << "mean = " << mean << std::endl;
	hmeannoretrofar->Fill(lambdaretro,mean);
	delete h1;
	delete f1;
      }
      */
      FileManager* filemanagernoretrocenter = new FileManager();
      filemanagernoretrocenter->SetAllFile();
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("EmitPositionFixedX","double",200.));
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","fixed"));
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",reflectivity));
      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroFinalver3True"));
      //      filemanagernoretrocenter->narrowdowntag.push_back(AnalizeTag("LambdaRetro","double",5000.));
      filemanagernoretrocenter->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanagernoretrocenter->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanagernoretrocenter,"testnoretrocenter");
      TH1D* hist2 = new TH1D("hist2",";rave;# of events",300,0.,300.);
      manager->SetTH1DEvent(hist2,"efficienthitsdirect","number","testnoretrocenter");
      TH1D* hmeannoretrocenter = new TH1D("hmeannoretrocenter",";Lambda Reflect(cm);mean of effective hits",11,4500,15500);
      TH1D* hmeandirect = new TH1D("hmeandirect",";Lambda Reflect(cm);mean of effective hits",11,4500,15500);
      TH1D* h = new TH1D("h","",300,0.,300.);
      manager->SetTH1DEvent(h,"efficienthitsdirect","number","testnoretrocenter");
      TF1* f = new TF1("f","gaus",0.,300.);
      h->Fit(f,"Rn");
      double m = f->GetParameter(1);
      for(int j = 0;j < (int)manager->listoffilelist["testnoretrocenter"].size();j++){
	TH1D* h1 = new TH1D("h1","",300,0.,300.);
	double mean = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthitsreflect","number","testnoretrocenter",j);
	double lambdaretro = 0.;
	file.GetTagdouble("LambdaRetro",lambdaretro);
	TF1* f1 = new TF1("f1","gaus",0.,300.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	std::cout << "labmdaRetro = " << lambdaretro << std::endl;
	std::cout << "mean = " << mean << std::endl;
	hmeannoretrocenter->Fill(lambdaretro,mean);
	hmeandirect->Fill(lambdaretro,m);
	delete h1;
	delete f1;
      }
      /*      FileManager* filemanagernoretronear = new FileManager();
      filemanagernoretronear->SetAllFile();
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("EmitPositionFixedX","double",1300.));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","fixed"));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",reflectivity));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroFinalver2True"));
      filemanagernoretronear->narrowdowntag.push_back(AnalizeTag("LambdaRetro","double",5000.));
      filemanagernoretronear->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanagernoretronear->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanagernoretronear,"testnoretronear");
      TH1D* hist3 = new TH1D("hist3",";rave;# of events",300,0.,300.);
      manager->SetTH1DEvent(hist3,"N50refTrue","number","testnoretronear");
      TH1D* hmeannoretronear = new TH1D("hmeannoretronear",";Lambda(cm);mean of effective hits",11,4500.,15500.);
      for(int j = 0;j < (int)manager->listoffilelist["testnoretronear"].size();j++){
	TH1D* h1 = new TH1D("h1","",300,0.,300.);
	double mean = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthitsreflect","number","testnoretronear",j);
	double lambdaretro = 0.;
	file.GetTagdouble("LambdaRetro",lambdaretro);
	TF1* f1 = new TF1("f1","gaus",0.,300.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	std::cout << "labmdaRetro = " << lambdaretro << std::endl;
	std::cout << "mean = " << mean << std::endl;
	hmeannoretronear->Fill(lambdaretro,mean);
	delete h1;
	delete f1;
      }
      */
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.5,0.7,0.98,0.9);
      //      l1->AddEntry(hmeannoretrofar,"far,15MeV,Use Retro,Reflect Part","l");
      l1->AddEntry(hmeannoretrocenter,"r=1.0,Reflect Part","l");
      //      l1->AddEntry(hmeannoretronear,"near,15MeV,Use Retro,Reflect Part","l");
      l1->AddEntry(hmeandirect,"r=1.0,Direct Part","l");
      //      hmeannoretrofar->SetStats(0);
      //      hmeannoretrofar->GetYaxis()->SetRangeUser(0.,150.);
      //      hmeannoretrofar->SetLineColor(1);
      //      hmeannoretrofar->Draw("hist");
      hmeannoretrocenter->GetYaxis()->SetRangeUser(0.,200.);
      hmeannoretrocenter->SetStats(0);
      hmeannoretrocenter->SetLineColor(2);
      hmeannoretrocenter->Draw("hist");
      //      hmeannoretronear->SetStats(0);
      //      hmeannoretronear->SetLineColor(2);
      //      hmeannoretronear->Draw("histsame");
      hmeandirect->SetStats(0);
      hmeandirect->SetLineColor(4);
      hmeandirect->Draw("histsame");
      TF1* f1 = new TF1("f1","pol4",4500.,15500.);
      hmeannoretrocenter->Fit(f1,"R");
      l1->AddEntry(f1,"fit of Reflect Part");
      f1->Draw("same");
      l1->Draw("same");
      std::cout << "direct hits = " << hmeandirect->GetBinContent(1) << std::endl;
      app.Run();
      delete c1;
      //      delete hmeannoretrofar;
      delete hmeannoretrocenter;
      //      delete hmeannoretronear;
      delete hmeandirect;
      delete manager;
      //      delete filemanagernoretrofar;
      delete filemanagernoretrocenter;
      //      delete filemanagernoretronear;
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
