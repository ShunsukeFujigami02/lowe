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
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      AnalizeManager* manager = new AnalizeManager();
      FileManager* filemanagernoretro = new FileManager();
      filemanagernoretro->SetAllFile();
      filemanagernoretro->narrowdowntag.push_back(AnalizeTag("RetroType","string","NoRetro"));
      filemanagernoretro->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",1300.));
      filemanagernoretro->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanagernoretro->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanagernoretro->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanagernoretro->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanagernoretro->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanagernoretro,"testnoretro");
      TH1D* hmeannoretro = new TH1D("hmeannoretro",";energy(MeV);mean of efficient hits",11,4.5,15.5);
      TH1D* hEerrornoretro = new TH1D("hEerrornoretro",";energy(MeV);(error of reconstructed energy)/energy",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["testnoretro"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,100+j*10);
	TH1D* h2 = new TH1D("h2","",100,0.,(double)j+10.);
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthits","number","testnoretro",j);
	manager->SetTH1DEvent(h2,"ReconstructedEnergyNoRetro","number","testnoretro",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,100+j*10.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	TF1* f2 = new TF1("f2","gaus",0.,(double)j+10.);
	h2->Fit(f2,"Rn");
	double Eerror = f2->GetParameter(2);
	double Eerrorerror = f2->GetParError(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	std::cout << "Eerror = " << Eerror << std::endl;
	std::cout << "Eerrorerror = " << Eerrorerror << std::endl;
	hmeannoretro->Fill(energy,mean);
	hmeannoretro->SetBinError(hmeannoretro->GetXaxis()->FindBin(energy),meanerror);
	hEerrornoretro->Fill(energy,Eerror/energy);
	hEerrornoretro->SetBinError(hEerrornoretro->GetXaxis()->FindBin(energy),Eerrorerror/energy);
	delete h1;
	delete h2;
	delete f1;
      }
      FileManager* filemanagernoretro2 = new FileManager();
      filemanagernoretro2->SetAllFile();
      filemanagernoretro2->narrowdowntag.push_back(AnalizeTag("RetroType","string","NoRetro"));
      filemanagernoretro2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanagernoretro2->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanagernoretro2->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanagernoretro2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanagernoretro2->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanagernoretro2->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanagernoretro2,"testnoretro2");
      TH1D* hmeannoretro2 = new TH1D("hmeannoretro2",";energy(MeV);mean of efficient hits",11,4.5,15.5);
      TH1D* hEerrornoretro2 = new TH1D("hEerrornoretro2",";energy(MeV);(error of reconstructed energy)/energy",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["testnoretro2"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,100+j*10);
	TH1D* h2 = new TH1D("h2","",100,0.,(double)j+10.);
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthits","number","testnoretro2",j);
	manager->SetTH1DEvent(h2,"ReconstructedEnergyNoRetro","number","testnoretro2",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,100+j*10.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	TF1* f2 = new TF1("f2","gaus",0.,(double)j+10.);
	h2->Fit(f2,"Rn");
	double Eerror = f2->GetParameter(2);
	double Eerrorerror = f2->GetParError(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	std::cout << "Eerror = " << Eerror << std::endl;
	std::cout << "Eerrorerror = " << Eerrorerror << std::endl;
	hmeannoretro2->Fill(energy,mean);
	hmeannoretro2->SetBinError(hmeannoretro2->GetXaxis()->FindBin(energy),meanerror);
	hEerrornoretro2->Fill(energy,Eerror/energy);
	hEerrornoretro2->SetBinError(hEerrornoretro2->GetXaxis()->FindBin(energy),Eerrorerror/energy);
	delete h1;
	delete h2;
	delete f1;
      }
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",1300.));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",1.0));
      filemanager->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroaddretrotail"));
      filemanager->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager,"test");
      TH1D* hmean = new TH1D("hmean",";energy(MeV);mean of efficient hits",11,4.5,15.5);
      TH1D* hEerror = new TH1D("hEerror",";energy(MeV);(error of reconstructed energy)/energy",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["test"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,100+j*10);
	TH1D* h2 = new TH1D("h2","",100,0.,(double)j+10.);
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthits","number","test",j);
	manager->SetTH1DEvent(h2,"ReconstructedEnergyOnRetroaddretrotail","number","test",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,100+j*10.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	TF1* f2 = new TF1("f2","gaus",0.,(double)j+10.);
	h2->Fit(f2,"Rn");
	double Eerror = f2->GetParameter(2);
	double Eerrorerror = f2->GetParError(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	std::cout << "Eerror = " << Eerror << std::endl;
	std::cout << "Eerrorerror = " << Eerrorerror << std::endl;
	hmean->Fill(energy,mean);
	hmean->SetBinError(hmean->GetXaxis()->FindBin(energy),meanerror);
	hEerror->Fill(energy,Eerror/energy);
	hEerror->SetBinError(hEerror->GetXaxis()->FindBin(energy),Eerrorerror/energy);
	delete h1;
	delete h2;
	delete f1;
      }
      FileManager* filemanager2 = new FileManager();
      filemanager2->SetAllFile();
      filemanager2->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",1300.));
      filemanager2->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager2->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",1.0));
      filemanager2->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetro"));
      filemanager2->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager2->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager2,"test2");
      TH1D* hmean2 = new TH1D("hmean2",";energy(MeV);mean of efficient hits",11,4.5,15.5);
      TH1D* hEerror2 = new TH1D("hEerror2",";energy(MeV);(error of reconstructed energy)/energy",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["test2"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,100+j*10);
	TH1D* h2 = new TH1D("h2","",100,0.,(double)j+10.);
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthits","number","test2",j);
	manager->SetTH1DEvent(h2,"ReconstructedEnergyOnRetro","number","test2",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,100+j*10.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	TF1* f2 = new TF1("f2","gaus",0.,(double)j+10.);
	h2->Fit(f2,"Rn");
	double Eerror = f2->GetParameter(2);
	double Eerrorerror = f2->GetParError(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	std::cout << "Eerror = " << Eerror << std::endl;
	std::cout << "Eerrorerror = " << Eerrorerror << std::endl;
	hmean2->Fill(energy,mean);
	hmean2->SetBinError(hmean2->GetXaxis()->FindBin(energy),meanerror);
	hEerror2->Fill(energy,Eerror/energy);
	hEerror2->SetBinError(hEerror2->GetXaxis()->FindBin(energy),Eerrorerror/energy);
	delete h1;
	delete h2;
	delete f1;
      }
      FileManager* filemanager3 = new FileManager();
      filemanager3->SetAllFile();
      filemanager3->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager3->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      filemanager3->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",1.0));
      filemanager3->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetro"));
      filemanager3->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager3->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager3,"test3");
      TH1D* hmean3 = new TH1D("hmean3",";energy(MeV);mean of efficient hits",11,4.5,15.5);
      TH1D* hEerror3 = new TH1D("hEerror3",";energy(MeV);(error of reconstructed energy)/energy",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["test3"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,100+j*10);
	TH1D* h2 = new TH1D("h2","",100,0.,(double)j+10.);
	double mean = 0.;
	double meanerror = 0.;
	AnalizeFile file = manager->SetTH1DEvent(h1,"efficienthits","number","test3",j);
	manager->SetTH1DEvent(h2,"ReconstructedEnergyOnRetro","number","test3",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,100+j*10.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(1);
	meanerror = f1->GetParError(1);
	TF1* f2 = new TF1("f2","gaus",0.,(double)j+10.);
	h2->Fit(f2,"Rn");
	double Eerror = f2->GetParameter(2);
	double Eerrorerror = f2->GetParError(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "mean = " << mean << std::endl;
	std::cout << "meanerror = " << meanerror << std::endl;
	std::cout << "Eerror = " << Eerror << std::endl;
	std::cout << "Eerrorerror = " << Eerrorerror << std::endl;
	hmean3->Fill(energy,mean);
	hmean3->SetBinError(hmean3->GetXaxis()->FindBin(energy),meanerror);
	hEerror3->Fill(energy,Eerror/energy);
	hEerror3->SetBinError(hEerror3->GetXaxis()->FindBin(energy),Eerrorerror/energy);
	delete h1;
	delete h2;
	delete f1;
      }
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.6,0.68,0.99,0.88);
      l1->AddEntry(hEerrornoretro,"No Retro","l");
      l1->AddEntry(hEerror,"On Retro add retro tail(r=1.0)","l");
      l1->AddEntry(hEerror2,"On Retro(r=1.0)","l");
      hEerrornoretro->SetStats(0);
      hEerrornoretro->GetYaxis()->SetRangeUser(0.,0.3);
      hEerrornoretro->Draw("histE");
      hEerrornoretro->SetLineColor(2);
      hEerror->SetStats(0);
      hEerror->GetYaxis()->SetRangeUser(0.,0.3);
      hEerror->Draw("histEsame");
      hEerror->SetLineColor(4);
      hEerror2->SetStats(0);
      hEerror2->GetYaxis()->SetRangeUser(0.,0.3);
      hEerror2->SetLineColor(6);
      hEerror2->Draw("histEsame");
      l1->Draw("same");
      TLegend* l2 = new TLegend(0.3,0.78,0.6,0.88);
      l2->AddEntry(hmean2,"side(On Retro)","l");
      l2->AddEntry(hmean3,"center(On Retro)","l");
      l2->AddEntry(hmeannoretro,"side(No Retro)","l");
      l2->AddEntry(hmeannoretro2,"center(No Retro)","l");
      hmeannoretro->SetStats(0);
      hmeannoretro->GetYaxis()->SetRangeUser(0.,160.);
      hmeannoretro->SetLineColor(1);
      hmeannoretro->Draw("histE");
      hmeannoretro2->SetStats(0);
      hmeannoretro2->GetYaxis()->SetRangeUser(0.,160.);
      hmeannoretro2->SetLineColor(3);
      hmeannoretro2->Draw("histEsame");
      hmean2->SetStats(0);
      hmean2->GetYaxis()->SetRangeUser(0.,160.);
      hmean2->SetLineColor(2);
      hmean2->Draw("histEsame");
      //      TF1* f1 = new TF1("f1","pol1",4.5,15.5);
      //      hmean2->Fit(f1,"R");
      //      f1->Draw("same");
      hmean3->SetStats(0);
      hmean3->SetLineColor(4);
      hmean3->Draw("histEsame");
      l2->Draw("same");
      app.Run();
      delete c1;
      delete hmean;
      delete hEerror;
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
