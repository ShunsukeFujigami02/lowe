#include "CArea.hh"
#include <TH2D.h>

CArea::CArea(int firstxbin,int lastxbin,int firstybin,int lastybin)
  :firstxbin(firstxbin)
  ,lastxbin(lastxbin)
  ,firstybin(firstybin)
  ,lastybin(lastybin)
{}

double CArea::XLength(){
  return (double)(lastxbin - firstxbin + 1);
}

double CArea::YLength(){
  return (double)(lastybin - firstybin + 1);
}
double CArea::Area(){
  return XLength() * YLength();
}

double Integral(TH2D* h1,CArea area){
  return h1->Integral(area.Getfirstxbin(),area.Getlastxbin(),area.Getfirstybin(),area.Getlastybin());
}
