#include "config.hh"
#include <TH2D.h>
#include "photo_to_hist.hh"
#include <cmath>
#include <iostream>
#include "integral_photo.hh"
#include <exception>

int main(){
  try{
    Config_fitting_responce_ccd config;
    //    TFile* fout = new TFile(config.outfile,"recreate");
    //    TF1* f1 = new TF1("f1","x^[0]",0.,1.,1);
    //    f1->SetParameters(1.,0.);
    TH2D* hND30 = photo_to_hist(config.infileND30,"hN30");
    TH2D* hND3010 = photo_to_hist(config.infileND3010,"hND3010");
    double pixel30 = hND30->GetBinContent(config.x1,config.y1);
    double bg30 = integral_photo(config.infileND30,config.bgarea);
    double areabg = (config.bgarea).Area();
    double averagebg30 = bg30/areabg;
    double pixel3010 = hND3010->GetBinContent(config.x1,config.y1);
    double bg3010 = integral_photo(config.infileND3010,config.bgarea);
    double averagebg3010 = bg3010/areabg;
    double gamma = std::log(pixel30/pixel3010)/std::log(10.);
    double gamma_rmbg = std::log((pixel30-averagebg30)/(pixel3010-averagebg3010))/std::log(10.);
    std::cout << "pixel30 = " << pixel30 << std::endl;
    std::cout << "pixel3010 = " << pixel3010 << std::endl;
    std::cout << "gamma = " << gamma << std::endl;
    std::cout << "bg30 = " << bg30 << std::endl;
    std::cout << "areabg = " << areabg << std::endl;
    std::cout << "averagebg30 = " << averagebg30 << std::endl;
    std::cout << "averagebg3010 = " << averagebg3010 << std::endl;
    std::cout << "gamma_rmbg = " << gamma_rmbg << std::endl;
    delete hND30;
    delete hND3010;
  }
  catch(std::exception& e){
    std::cout << "expection is occured" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(const char* str){
    std::cout << "Error in " << str << std::endl;
  }
  return 0;
}
