#include <TH2D.h>
#include <TFile.h>
#include <iostream>

int main(){
  try{
    TFile* fin = new TFile("/rhome/fujigami/retro/lowe/tiff/analize/gamma_correction_bgconsideredver2.root");
    TH2D* h2 = (TH2D*)fin->Get("hgamma");
    TFile* fout = new TFile("/rhome/fujigami/retro/lowe/tiff/analize/gamma1d.root");
    TH1D* h1 = new TH1D("h1",";gamma;# of pixel",100,1.0,1.5);
    for(int i = 1;i < hgamma->GetXaxis()->GetNbins();i++){
      for(int j = 1;j < hgamma->GetYaxis()->GetNbins();j++){
	double gamma = 
