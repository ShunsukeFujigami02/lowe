#ifndef EVENTDISPLAY_HH
#define EVENTDISPLAY_HH
// ROOT library
#include <TObject.h>
#include <TH2D.h>
#include <TArc.h>
#include <TPave.h>
#include <iostream>

class Eventdisplay : public TNamed {

public:
  Eventdisplay() {}
  Eventdisplay(char* name,char* title):TNamed(name,title){}
  Eventdisplay(const char* infile,char* name,char* title,int nevent=0,int xbin=150,int ybin=147);
  virtual ~Eventdisplay();
  void Set(const char* infile,int nevent=0,int xbin=150,int ybin=147);
  void Drawall(Option_t* option="colz");
  void Drawcharge(Option_t* option="colz");
  void Drawtime(Option_t* option="colz");
  void Drawhit(Option_t* option="colz");
  TH2D* Gethall(){return &hall;};
  TH2D* Gethcharge(){return &hcharge;};
  TH2D* Gethtime(){return &htime;};
  TH2D* Gethhit(){return &hhit;};
  Bool_t Add(Eventdisplay* eventdisplay1,Eventdisplay* eventdisplay2,Double_t c1 = 1.,Double_t c2 = 1.);
  Bool_t Add(Eventdisplay* eventdisplay1,Double_t c1 = 1.);
  double GetWCradius(){return WCradius;}
  double GetWClength(){return WClength;}
  static Eventdisplay* Sum(const char* infile,char* name,char* title,int nevents,int xbin=150,int ybin=147);
protected:
  TH2D hall;
  TH2D hcharge;
  TH2D htime;
  TH2D hhit;
  TArc a1;
  TArc a2;
  TPave p1;
  double WCradius;
  double WClength;
public:
  ClassDef(Eventdisplay,1)
};

#endif
