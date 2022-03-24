#include "config.hh"
#include <TFile.h>
#include <TH2D.h>
#include "photo_to_hist.hh"
#include <iostream>
#include <exception>
int main(){
  try{
    config_makehist config;
    TFile* fout = new TFile(config.outfile,"recreate");
    TH2D* h1 = photo_to_hist(config.infile,"h1");
    fout->Write();
    fout->Close();
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
