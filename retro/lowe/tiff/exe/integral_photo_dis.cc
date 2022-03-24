#include "config.hh"
#include <TFile.h>
#include <TH1D.h>
#include <cstring>
#include <sstream>
#include <cmath>
#include "integral_photo.hh"
#include <iostream>
#include <exception>

int main(){
  try{
    Config_integral_photo_dis config;
    TFile* fout = new TFile(config.outfile,"recreate");
    int anglenum = config.anglenum;
    double anglewidth = config.anglewidth;
    double anglemin = config.anglemin;
    double anglemax = config.anglemax;
    double anglehistmin = anglemin - anglewidth/2.;
    double anglehistmax = anglemax + anglewidth/2.;
    TH1D* h1 = new TH1D("rawdata",";angle;integral",anglenum,anglehistmin,anglehistmax);
    TH1D* h2 = new TH1D("rawdataall",";angle;integral",anglenum,anglehistmin,anglehistmax);
    for( double angle = anglemin ; angle < anglemax + anglewidth/2.;angle += anglewidth){
      std::stringstream ssinfile;
      if(angle < 0){
	ssinfile << config.infilehead << "minus" << std::abs(angle) << config.infiletail;
      }
      else{
	ssinfile << config.infilehead << angle << config.infiletail;
      }
      double integralrmbg = integral_photo((char*)ssinfile.str().c_str(),config.sigarea,config.bgarea,config.gamma);

      h1->Fill(angle,integralrmbg);
      double integralall = integral_all((char*)ssinfile.str().c_str(),config.gamma);
      h2->Fill(angle,integralall);
    }
    fout->Write();
    delete h1;
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
