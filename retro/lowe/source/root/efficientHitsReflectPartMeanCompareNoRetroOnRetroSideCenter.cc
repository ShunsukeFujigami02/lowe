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
      TRint app("app",&argc,argv);
      AnalizeManager* manager = new AnalizeManager();
      FileManager* filemanageronretroside = new FileManager();
      filemanageronretroside->SetAllFile();
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",1300.));
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY")));
      std::string energyfuncname = Getchar("ENERGYFUNCTIONNAME");
      filemanageronretroside->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname));
      filemanageronretroside->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanageronretroside->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanageronretroside,"testonretroside");
      TH1D* hmeanonretroside = new TH1D("hmeanonretroside",";energy(MeV);mean of efficient hits averaged part",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["testonretroside"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,Getdouble("ONRETROHISTMAXMIN")+j*Getdouble("ONRETROHISTMAXGRAD"));
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthitsOnretroaveraged","number","testonretroside",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,Getdouble("ONRETROHISTMAXMIN")+j*Getdouble("ONRETROHISTMAXGRAD"));
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	hmeanonretroside->Fill(energy,mean);
	hmeanonretroside->SetBinError(hmeanonretroside->GetXaxis()->FindBin(energy),meanerror);
	delete h1;
	delete f1;
      }
      FileManager* filemanageronretrocenter = new FileManager();
      filemanageronretrocenter->SetAllFile();
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",Getdouble("REFLECTIVITY")));
      filemanageronretrocenter->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string",energyfuncname));
      filemanageronretrocenter->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanageronretrocenter->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanageronretrocenter,"testonretrocenter");
      TH1D* hmeanonretrocenter = new TH1D("hmeanonretrocenter",";energy(MeV);mean of efficient hits averaged part",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["testonretrocenter"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,Getdouble("ONRETROHISTMAXMIN")+j*Getdouble("ONRETROHISTMAXGRAD"));
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthitsOnretroaveraged","number","testonretrocenter",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,Getdouble("ONRETROHISTMAXMIN")+j*Getdouble("ONRETROHISTMAXGRAD"));
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	hmeanonretrocenter->Fill(energy,mean);
	hmeanonretrocenter->SetBinError(hmeanonretrocenter->GetXaxis()->FindBin(energy),meanerror);
	delete h1;
	delete f1;
      }
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(Getdouble("LEGENDXMIN"),Getdouble("LEGENDYMIN"),Getdouble("LEGENDXMAX"),Getdouble("LEGENDYMAX"));
      l1->AddEntry(hmeanonretroside,"side(On Retro)","l");
      l1->AddEntry(hmeanonretrocenter,"center(On Retro)","l");
      hmeanonretroside->GetYaxis()->SetRangeUser(Getdouble("HISTRANGEYMIN"),Getdouble("HISTRANGEYMAX"));
      hmeanonretroside->SetStats(0);
      hmeanonretroside->SetLineColor(2);
      hmeanonretroside->Draw("histEsame");
      hmeanonretrocenter->SetStats(0);
      hmeanonretrocenter->SetLineColor(4);
      hmeanonretrocenter->Draw("histEsame");
      l1->Draw("same");
      app.Run();
      delete c1;
      delete hmeanonretroside;
      delete hmeanonretrocenter;
      delete manager;
      delete filemanageronretroside;
      delete filemanageronretrocenter;
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
