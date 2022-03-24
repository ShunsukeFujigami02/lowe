#ifndef CAREA_HH
#define CAREA_HH

#include <TH2D.h>

class CArea
{
public:
  CArea(){};
  CArea(int firstxbin,int lastxbin,int firstybin,int lastybin);
  virtual ~CArea(){};
  double Area();
  double XLength();
  double YLength();
  double Getfirstxbin(){return firstxbin;}
  double Getlastxbin(){return lastxbin;}
  double Getfirstybin(){return firstybin;}
  double Getlastybin(){return lastybin;}
private:
  int firstxbin;
  int lastxbin;
  int firstybin;
  int lastybin;
};

double Integral(TH2D* h1,CArea area);

#endif
