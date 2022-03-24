#include "config.hh"
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include "integral_photo.hh"
#include <sstream>
#include <cstring>
#include <cmath>
#include <exception>

int main(){
  try{
    //    Config_reflectivity_angle_dis config;
    std::cout << "1" << std::endl;
    double gammares = 0.0631;
    TFile* fout = new TFile("/rhome/fujigami/retro/lowe/tiff/analize/reflectivity_angle_dis.root","RECREATE");
    int anglenum = 25;
    double anglewidth = 5.;
    double anglemin = -60.;
    double anglemax = 60.;
    double anglehistmin = anglemin - anglewidth/2.;
    double anglehistmax = anglemax + anglewidth/2.;
    TH1D* h1 = new TH1D("rawdata",";angle;integral",anglenum,anglehistmin,anglehistmax);
    TH1D* h2 = new TH1D("rawdataall",";angle;integral",anglenum,anglehistmin,anglehistmax);
    TH1D* href = new TH1D("reflectivity",";angle;reflectivity",anglenum,anglehistmin,anglehistmax);
    CArea sigarea(100,800,500,900);
    CArea bgarea(800,1200,100,400);
    double gamma = 1.1867;
    double reference = integral_photo("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-04-mirror-reference-set-exposuretime-as-retro_convert.tif",sigarea,bgarea,gamma);
    double referencelow = integral_photo("/rhome/fujigami/retro/lowe/tiff/photo_convert/20200818-04-mirror-reference-set-exposuretime-as-retro_convert.tif",sigarea,bgarea,gamma - gammares);
    std::cout << "2" << std::endl;
    for( double angle = anglemin ; angle < anglemax + anglewidth/2.;angle += anglewidth){
      std::stringstream ssinfile;
      if(angle < 0){
	ssinfile << "/rhome/fujigami/retro/lowe/tiff/photo_convert/20200806-retro-" << "minus" << std::abs(angle) << "angle_convert.tif";
      }
      else{
	ssinfile << "/rhome/fujigami/retro/lowe/tiff/photo_convert/20200806-retro-" << angle << "angle_convert.tif";
      }
      double integralrmbg = integral_photo((char*)ssinfile.str().c_str(),sigarea,bgarea,gamma);
      double integralrmbglow = integral_photo((char*)ssinfile.str().c_str(),sigarea,bgarea,gamma - gammares);
      h1->Fill(angle,integralrmbg);
      href->Fill(angle,integralrmbg/(10.*reference));
      href->SetBinError(href->GetXaxis()->FindBin(angle),std::abs((integralrmbg/(10.*reference) - integralrmbglow/(10.*referencelow))));
      double integralall = integral_all((char*)ssinfile.str().c_str(),gamma);
      h2->Fill(angle,integralall);
    }
    std::cout << "3" << std::endl;
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
