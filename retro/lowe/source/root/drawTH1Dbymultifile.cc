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
#include "config.hh"
int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      TPython::Exec("import macro");
      TPython::Exec("import func");
      TPython::Exec("import ROOT");
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/Minimize_20210806_121430.csv");
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/Minimize_20210808_193944.csv");
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/Minimize_20210808_194116.csv");
      AnalizeManager* manager = new AnalizeManager();
      std::string filelistname = "changelikelioodgridsearch";
      manager->cpFileList(filemanager,filelistname);
      std::vector<TH1D*> hvec;
      TH1D* h1 = new TH1D("h1","",100,0.,1000.);
      hvec.push_back(h1);
      TH1D* h2 = new TH1D("h2","",100,0.,1000.);
      hvec.push_back(h2);
      TH1D* h3 = new TH1D("h3","",100,0.,1000.);
      hvec.push_back(h3);
      manager->SetTH1DEvent(hvec,"distance_true_reconstructedbygoodness","number",filelistname);
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.6, 0.68, 0.99, 0.88);
      c1->DrawFrame(0.,0.,1000.,800.);
      std::vector<int> colorhist = {2,3,4,6,8};
      hvec[0]->SetLineColor(2);
      l1->AddEntry(hvec[0],"No Retro (gaussian)","l");
      hvec[0]->SetStats(0);
      hvec[0]->Draw("same");
      hvec[1]->SetLineColor(3);
      l1->AddEntry(hvec[1],"On Retro (digital)","l");
      hvec[1]->SetStats(0);
      hvec[1]->Draw("same");
      hvec[2]->SetLineColor(4);
      l1->AddEntry(hvec[2],"On Retro (no digital)","l");
      hvec[2]->SetStats(0);
      hvec[2]->Draw("same");
      /*      auto iterc = colorhist.begin();
      auto iterf = filemanager->selectedfile.begin();
      for(auto iter = hvec.begin();iter != hvec.end();iter++,iterc++,iterf++)
	{
	  double gridsearchxnum = 0.;
	  AnalizeManager::GetValue((*iterf),"GoodnessSearchRangeXNumber",gridsearchxnum);
	  double gridsearchtnum = 0.;
	  AnalizeManager::GetValue((*iterf),"GoodnessSearchRangeTNumber",gridsearchtnum);
	  int gridsearchxnumi = gridsearchxnum;
	  int gridsearchtnumi = gridsearchtnum;
	  std::string interpretation = "grid search num x: " + std::to_string(gridsearchxnumi) + " t: " + std::to_string(gridsearchtnumi);
	  (*iter)->SetLineColor((*iterc));
	  l1->AddEntry((*iter),interpretation.c_str(),"l");
	  (*iter)->SetStats(0);
	  (*iter)->Draw("same");
	  }*/
      l1->Draw("same");
      app.Run();
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
