#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
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
      filemanager->narrowdowntag.push_back(AnalizeTag("RetroType","string","NoRetro"));
      //      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionFixedX","double",20.));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionSphereCenterX","double",0.));
      filemanager->narrowdowntag.push_back(AnalizeTag("ParticleEnergyFixedValue","double",5.));
      //      filemanager->narrowdowntag.push_back(AnalizeTag("EmitDirectionFixedCostheta","double",0.78539));
      filemanager->narrowdowntag.push_back(AnalizeTag("Detectortype","string","SK"));
      filemanager->narrowdowntag.push_back(AnalizeTag("EmitPositionType","string","Sphere"));
      //      filemanager->narrowdowntag.push_back(AnalizeTag("ReflectivityFactorTrapezoidReflectivity","double",0.3));
      filemanager->reflectNarrowDownTag("wcsim");
      std::cout << "file number is " << filemanager->selectedfilemap.size() << std::endl;
      //      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/wcsim_20211101_165524.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      //      TH1D* hdistance = new TH1D("hdistance",";TOF error (ns);# of hit",400,-300.,300.);
      //      manager->SetTH1DAllHit(hdistance,"emittimeerrorretrotrue","number","test");
      //      hdistance->SetStats(0);
      //      hdistance->SetLineColor(2);
      TH1D* hdistance2 = new TH1D("hdistance2",";TOF error (ns);# of hit",400,-300.,300.);
      manager->SetTH1DAllHit(hdistance2,"emittimeerrortrue","number","test");
      hdistance2->SetStats(0);
      hdistance2->SetLineColor(4);
      gStyle->SetOptLogy(1);
      TCanvas* c1 = new TCanvas("c1","");
      //      TLegend* l = new TLegend(0.6,0.7,0.9,0.9);
      //      l->AddEntry(hdistance2,"Direct","l");
      //      l->AddEntry(hdistance,"Reflect","l");
      hdistance2->Draw("samehist");
      //      hdistance->Draw("samehist");
      //      l->Draw("same");
      app.Run();
      /*      TH1D* honretro = new TH1D("honretro","",8,0.25,1.05);
      TH1D* hnoretro = new TH1D("hnoretro","",8,0.25,1.05);
      TH1D* honretrohitnum = new TH1D("honretrohitnum",";reflectivity;hit number(On Retro)",8,0.25,1.05);
      TH1D* hnoretrohitnum = new TH1D("hnoretrohitnum",";reflectivity;hit number(No Retro)",8,0.25,1.05);
      for(int j = 0;j < (int)manager->listoffilelist["test"].size();j++){
	TH1D* h1 = new TH1D("h1","",1000,-30.,700.);
	TH1D* h2 = new TH1D("h2","",1000,-30.,700.);
	TH1D* h3 = new TH1D("h3","",1000,-30.,700.);
	TH1D* h4 = new TH1D("h4","",1000,-30.,700.);
	AnalizeFile file = manager->SetTH1DAllHit(h1,"emittimeerrorretrotrue","number","test",j);
	AnalizeFile file2 = manager->SetTH1DAllHit(h3,"emittimeerrortrue","number","test",j);
	if(!(file == file2)){
	  std::cout << "error: file is not same" << std::endl;
	  throw "int main()";
	}
	//      manager->SetTH1DAllHit(h1,"openingangle","number","test","emittimeerrortrue > 50.");
	for(int i = 1; i < h1->GetXaxis()->GetNbins();i++)
	  {
	    if(h1->GetBinContent(i) != 0)
	      h2->Fill(h1->GetXaxis()->GetBinCenter(i),std::log(h1->GetBinContent(i)));
	  }
	int rangemin = h2->GetXaxis()->FindBin(-100.);
	int rangemax = h2->GetXaxis()->FindBin(100.);
	double maxval = 0.;
	for(int i = rangemin;i < rangemax;i++){
	  double val = h2->GetBinContent(i);
	  if(maxval < val)
	    maxval = val;
	}
	int rangemin2 = h2->GetXaxis()->FindBin(500.);
	int rangemax2 = h2->GetXaxis()->FindBin(700.);
	double minval = 0.;
	double minvalsum = 0.;
	int binnum = 0;
	for(int i = rangemin2;i < rangemax2;i++){
	  double val = h2->GetBinContent(i);
	  binnum++;
	  minvalsum += val;
	}
	minval = minvalsum/(double)binnum;
	for(int i = 1; i < h1->GetXaxis()->GetNbins();i++)
	  {
	    if(h3->GetBinContent(i) != 0)
	      h4->Fill(h3->GetXaxis()->GetBinCenter(i),std::log(h3->GetBinContent(i)));
	  }
	int rangeminnoretro = h4->GetXaxis()->FindBin(-100.);
	int rangemaxnoretro = h4->GetXaxis()->FindBin(100.);
	double maxval2 = 0.;
	for(int i = rangeminnoretro;i < rangemaxnoretro;i++){
	  double val = h4->GetBinContent(i);
	  if(maxval2 < val)
	    maxval2 = val;
	}
	int rangemin22 = h4->GetXaxis()->FindBin(-400.);
	int rangemax22 = h4->GetXaxis()->FindBin(600.);
	double minval2 = 0.;
	double minvalsum2 = 0.;
	int binnum2 = 0;
	for(int i = rangemin22;i < rangemax22;i++){
	  double val = h4->GetBinContent(i);
	  binnum2++;
	  minvalsum2 += val;
	}
	minval2 = minvalsum/(double)binnum;
	std::cout << "maxval(onretro) is " << maxval << std::endl;
	std::cout << "minval(onretro) is " << minval << std::endl;
	std::cout << "maxval(noretro) is " << maxval2 << std::endl;
	std::cout << "minval(noretro) is " << minval2 << std::endl;
	double reflectivity = 0.;
	file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
	std::cout << "reflectivity = " << reflectivity << std::endl;
	if(reflectivity > 0.25){
	  honretro->Fill(reflectivity,maxval - minval);
	  hnoretro->Fill(reflectivity,maxval2 - minval2);
	}
	double hitnumonretro = h1->Integral(h1->GetXaxis()->FindBin(-25.),h1->GetXaxis()->FindBin(25.));
	double hitnumnoretro = h3->Integral(h3->GetXaxis()->FindBin(-25.),h3->GetXaxis()->FindBin(25.));
	double darkrate = 0.;
	file.GetTagdouble("DarkRate",darkrate);
	double NPMT = 0.;
	manager->SetdoubleRun(NPMT,"NPMT","test",j);
	double darkhit50 = darkrate*1.0e3*NPMT*50*1.0e-9*10000.;
	std::cout << "darkhit50 is " << darkhit50 << std::endl;
	honretrohitnum->Fill(reflectivity,hitnumonretro-darkhit50);
	hnoretrohitnum->Fill(reflectivity,hitnumnoretro-darkhit50);
	
	delete h1;
	delete h2;
	delete h3;
	delete h4;
      }
      TCanvas* c1 = new TCanvas("c1","");
      //      h2->Draw("histsame");
      honretrohitnum->SetStats(0);
      hnoretrohitnum->SetStats(0);
      honretrohitnum->Draw("hist");
      app.Run();
      //      delete h1;
      */
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
