#include <TH2D.h>
#include "photo_to_hist.hh"
#include <iostream>
#include "CArea.hh"

double integral_photo(const char* infile,CArea sigarea,CArea bgarea,double gamma = 1.){
  TH2D* h1 = photo_to_hist(infile,"h1",gamma);
  double signal = Integral(h1,sigarea);
  double background = Integral(h1,bgarea);
  delete h1;
  std::cout << "signal:" << signal << std::endl;
  std::cout << "background:" << background << std::endl;
  std::cout << "bgarea:" << bgarea.Area() << std::endl;
  return signal - background * sigarea.Area()/bgarea.Area();
}

double integral_all(const char* infile,double gamma = 1.){
  TH2D* h1 = photo_to_hist(infile,"h1",gamma);
  double integral = h1->Integral();
  delete h1;
  return integral;
}

double integral_photo(const char* infile,CArea sigarea,double gamma = 1.){
  TH2D* h1 = photo_to_hist(infile,"h1",gamma);
  double signal = Integral(h1,sigarea);
  return signal;
}
