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
      filemanager->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/Goodness_20210523_140612.csv");
      FileManager* filemanager2 = new FileManager();
      filemanager2->SetAllFile();
      filemanager2->setselectedfile("/rhome/fujigami/retro/lowe/analizefile/Goodness_20210628_015204.csv");
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"file1");
      manager->cpFileList(filemanager2,"file2");
      //      TH1D* h1 = new TH1D("h1","",100,0.,1000.);
      TH1D* h2 = new TH1D("h2","",100,0.,1000.);
      //      manager->SetTH1DEvent(h1,"distance_true_reconstructedbygoodness","number","file1");
      manager->SetTH1DEvent(h2,"distance_true_reconstructedbygoodness","number","file1");
      TH1D* h3 = new TH1D("h3","",100,0.,1000.);
      manager->SetTH1DEvent(h3,"distance_true_reconstructedbygoodness","number","file2");
      TCanvas* c1 = new TCanvas("c1","");
      TLegend* l1 = new TLegend(0.5,0.6,0.99,0.88);
      //      h1->SetLineColor(2);
      //      h1->SetStats(0);
      h2->SetLineColor(4);
      h2->SetStats(0);
      h2->Scale(1./h2->GetEntries());
      h3->SetLineColor(6);
      h3->SetStats(0);
      h3->Scale(1./h3->GetEntries());
      //      l1->AddEntry(h1,"distance by grid search");
      l1->AddEntry(h2,"use blacksheet");
      l1->AddEntry(h3,"use retro, reflectivity=1.0");
      //      h1->Draw("same");
      h3->Draw("same");
      h2->Draw("same");
      l1->Draw("same");
      app.Run();
      delete h2;
      //      delete h1;
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
