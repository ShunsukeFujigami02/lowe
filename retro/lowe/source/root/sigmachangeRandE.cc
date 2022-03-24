#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <exception>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TStyle.h>
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      //      double r = 1.0;
      TRint app("app",&argc,argv);
      //      TH1D* hsigmadirect = new TH1D("hsigmadirect",";energy(MeV);sigma E reflect(r=1.0)",11,4.5,15.5);
      gStyle->SetPalette(1);
      AnalizeManager* manager = new AnalizeManager();
      FileManager* filemanager0 = new FileManager();
      filemanager0->SetAllFile();
      filemanager0->narrowdowntag.push_back(AnalizeTag("RetroType","string","NoRetro"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      //      filemanager1->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY1")));
      filemanager0->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      //      filemanager1->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",r));
      filemanager0->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","NoRetro"));
      filemanager0->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager0->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager0,"file0");
      std::vector<double> meanvec;
      for(int j = 0;j < (int)manager->listoffilelist["file0"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,30.);
	double mean = 0;
	AnalizeFile file = manager->SetTH1DEvent(h1,"EnergyNoRetro","number","file0",j);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,30.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(2);
	meanvec.push_back(mean/energy);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "sigma = " << mean << std::endl;
	delete h1;
	delete f1;
      }
      FileManager* filemanager1 = new FileManager();
      filemanager1->SetAllFile();
      filemanager1->narrowdowntag.push_back(AnalizeTag("RetroType","string","OnRetro"));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      //      filemanager1->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",Getdouble("ENERGY1")));
      filemanager1->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereRadius","double",200.));
      //      filemanager1->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",r));
      filemanager1->narrowdowntag.push_back(AnalizeTag("EnergyFunctionName","string","OnRetroFinalver3"));
      filemanager1->reflectNarrowDownTag("Energy");
      std::cout << "file number is " << filemanager1->selectedfilemap.size() << std::endl;
      manager->cpFileList(filemanager1,"file1");
      TH2D* hsigma = new TH2D("hsigma",";reflectivity max;energy(MeV)",8,0.25,1.05,11,4.5,15.5);
      //      TH1D* hsigma = new TH1D("hsigma",";energy(MeV);deltaE/E",11,4.5,15.5);
      for(int j = 0;j < (int)manager->listoffilelist["file1"].size();j++){
	TH1D* h1 = new TH1D("h1","",100,0.,30.);
	double mean = 0;
	AnalizeFile file = manager->SetTH1DEvent(h1,"ReconstructEnergyOnRetro","number","file1",j);
	double reflectivity = 0.;
	file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
	double energy = 0.;
	file.GetTagdouble("ParticleEnergyFixedValue",energy);
	TF1* f1 = new TF1("f1","gaus",0.,30.);
	h1->Fit(f1,"Rn");
	mean = f1->GetParameter(2);
	std::cout << "energy = " << energy << std::endl;
	std::cout << "reflectivity = " << reflectivity << std::endl;
	std::cout << "sigma = " << mean << std::endl;
	//	hsigma->Fill(reflectivity,energy,mean);
	if(reflectivity > 0.25){
	  int number = 0;
	  if(energy == 5.)
	    number = 0;
	  if(energy == 6.)
	    number = 1;
	  if(energy == 7.)
	    number = 2;
	  if(energy == 8.)
	    number = 3;
	  if(energy == 9.)
	    number = 4;
	  if(energy == 10.)
	    number = 5;
	  if(energy == 11.)
	    number = 6;
	  if(energy == 12.)
	    number = 7;
	  if(energy == 13.)
	    number = 8;
	  if(energy == 14.)
	    number = 9;
	  if(energy == 15.)
	    number = 10;
	  hsigma->Fill(reflectivity,energy,(mean/energy)/meanvec[number]);
	}
	//	TH1D* h2 = new TH1D("h2","",100,0.,30.);
	//	double mean2 = 0;
	//	manager->SetTH1DEvent(h2,"ReconstructEnergyOnRetro","number","file1",j);
	//	TF1* f2 = new TF1("f2","gaus",0.,300.);
	//	h2->Fit(f2,"Rn");
	//	mean2 = f2->GetParameter(2);
	//	std::cout << "sigma2 = " << mean2 << std::endl;
	//	hsigma->Fill(reflectivity,energy,mean2/mean);
	delete h1;
	delete f1;
	//	delete h2;
	//	delete f2;
      }
      /*      for(int i = 0;i < 15;i++){
	double E = (double)i + 5.;
	hsigma->Fill(0.2,E,meanvec[i]);
      }
      hsigma->GetXaxis()->SetBinLabel(1,"Not Use Retro");
      hsigma->GetXaxis()->SetBinLabel(2,"0.3");
      hsigma->GetXaxis()->SetBinLabel(3,"0.4");
      hsigma->GetXaxis()->SetBinLabel(4,"0.5");
      hsigma->GetXaxis()->SetBinLabel(5,"0.6");
      hsigma->GetXaxis()->SetBinLabel(6,"0.7");
      hsigma->GetXaxis()->SetBinLabel(7,"0.8");
      hsigma->GetXaxis()->SetBinLabel(8,"0.9");
      hsigma->GetXaxis()->SetBinLabel(9,"1.0");*/
      TCanvas* c1 = new TCanvas("c1","");

      //      for(double E = 5.;E < 15.5;E+=1.){
	//	double average = 0.;
	//	for(double r = 0.3;r < 1.05;r+=0.1){
      //	  int binr = hsigma->GetXaxis()->FindBin(r);
      //	  int binE = hsigma->GetYaxis()->FindBin(E);
      //	  double mean0 = hsigma->GetBinContent(binr,binE);
	  //	  average+=mean0;
	  //	}
	  //	average = average/8.;
      //	  hsigmadirect->Fill(E,mean0);
	  //	hsigmadirect->Fill(E,average);
      //	}
      hsigma->SetStats(0);
      //      hsigma->GetYaxis()->SetRangeUser(0.,0.5);
      hsigma->Draw("colz");
      //      TF1* f = new TF1("f","pol2",4.5,15.5);
      //      hsigmadirect->Fit(f,"R");
      //      hsigmadirect->SetStats(0);
      //      hsigmadirect->Draw("hist");
      //      f->Draw("same");
      app.Run();
      delete c1;
      delete hsigma;
      //      delete hsigmadirect;
      //      delete f;
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
  return 0.;
}
