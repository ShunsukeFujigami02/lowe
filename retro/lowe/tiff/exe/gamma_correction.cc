#include "config.hh"
#include <TFile.h>
#include <TH2D.h>
#include "photo_to_hist.hh"
#include <cmath>
#include <iostream>
#include "histmacro.hh"
#include <exception>
int main(){
  try{
    std::cout << "0" << std::endl;
    TH2D* hbg30 = photo_to_hist_empty("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-05-ND03_convert.tif","hbg30");
    Fillconstvalue(hbg30,1.9198);
    TH2D* hbg3010 = photo_to_hist_empty("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-06-ND03ND01_convert.tif","hbg3010");
    Fillconstvalue(hbg3010,1.01475);
    TFile* fout = new TFile("/rhome/fujigami/retro/lowe/tiff/analize/gamma_correction_bgconsideredver2.root","recreate");
    TH1D* hgamma1 = new TH1D("hgamma1",";gamma;# of pixel",100,0.9,1.4);
    TH2D* hND30 = photo_to_hist("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-05-ND03_convert.tif","hN30");
    TH2D* hND30_rmbg = photo_to_hist("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-05-ND03_convert.tif","hND30_rmbg");
    hND30_rmbg->Add(hbg30,-1.);
    TH2D* hND3010_rmbg = photo_to_hist("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-06-ND03ND01_convert.tif","hND3010_rmbg");
    hND3010_rmbg->Add(hbg3010,-1.);
    TH2D* hND3010 = photo_to_hist("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-06-ND03ND01_convert.tif","hND3010");
    TH2D* hgamma = photo_to_hist_empty("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-05-ND03_convert.tif","hgamma");
    std::cout << "1" << std::endl;
    for(int i = 1; i < hgamma->GetXaxis()->GetNbins() ; i++){
      for(int j = 1 ;j < hgamma->GetYaxis()->GetNbins() ;j++){
	double temp = std::log(hND30_rmbg->GetBinContent(i,j)/hND3010_rmbg->GetBinContent(i,j))/std::log(10.);
	hgamma->SetBinContent(i,j,temp);
	double x = hgamma->GetXaxis()->GetBinCenter(i);
	double y = hgamma->GetYaxis()->GetBinCenter(j);
	if((x > 500.) && (x < 800.) && ( y > -600.) && (y < -400.))
	  hgamma1->Fill(temp);
      }
    }
    //    double gamma = config.gamma;
    //    double gamma10 = std::pow(10.,gamma);
    //    TH2D* hND3010_corrected = photo_to_hist_empty(config.infileND3010,"hND3010_corrected");
    //    hND3010_corrected->Add(hND3010_rmbg,gamma10);
    fout->Write();
    fout->Close();
    std::cout << "1" << std::endl;
    //    delete hND30;
    //    delete hND3010;
    //    delete hND3010_corrected;
  }
  catch(std::exception& e){
    std::cout << "exception is occured" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(const char* str){
    std::cout << "Error in " << str << std::endl;
  }
  return 0;
}
