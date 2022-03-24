#ifndef _MINIMIZEDFUNCTION_HH
#define _MINIMIZEDFUNCTION_HH

#include "AnalizeFiledata.hh"
#include "hitinfo.hh"
#include <vector>
#include <TH2D.h>
#include <TFile.h>

class MinimizedFunction
{
public:
  MinimizedFunction() = delete;
  MinimizedFunction(const char* funcname,AnalizeFile file,AnalizeFiledata* data,int parnumber=6);
  virtual ~MinimizedFunction(){;}
  double returnvalue(const double* a);
  double returnvaluecontents(std::vector<double> a);
  double returnvaluecontentshit(std::vector<double> a,int ihit);
  std::vector<double> Getfirstvalue();
  void SetEventNumber(int n);
  void SetPhotoCoverageHist(TH2D* h){
    hPhotoCoverage = h;
  }
  double GetTruevalue(int parnumin);
  double goodnessnoretro(double x,double y,double z,double t);
  double goodnesscomparenodigitalver2(double x,double y,double z,double t,std::string cut="default");
  double likelihooddirectionsum(double x,double y,double z,double t,double costheta,double phi,std::string cut="default");
  double minimizedfuncnoretroadddarkratenumaddacceptancever2(double x,double y,double z,double t,double costheta,double phi,double k);
  double minimizedfunconretroadddarkratenumaddacceptance(double x,double y,double z,double t,double costheta,double phi,double k);
  double minimizedfunconretroadddarkratenumaddacceptancereflectpart(double x,double y,double z,double t,double costheta,double phi,double k);
  double pmtcostheta(hitinfo info,double x,double y,double z);
  double toferrorfunc(hitinfo info,double x,double y,double z,double t,std::string toferrorfuncname,std::string distancefuncname);
  double distancefunction(hitinfo info,double x,double y,double z,std::string distancefuncname);
  double NormalizedCherenkovAngleDis(double costhetahit);
  double cherenkovanglefunc(hitinfo info,double x,double y,double z,double costheta,double phi,std::string cherenkovanglefuncname);
  double effectiveReflectivity(double x,double y,double z,double costheta,double phi);
  double effectiveReflectivityConsiderCoverage(double x,double y,double z,double costheta,double phi);
  hitinfo Gethitinfo(int k){
    return allhitinfo[k];
  }
  double pdir(double x,double y,double z,double t,double costheta,double phi,double k,int ihit);
  double pref(double x,double y,double z,double t,double costheta,double phi,double k,int ihit);
  double pdark(double k);
  double pdirtime(double x,double y,double z,double t,double k,int ihit);
  double preftime(double x,double y,double z,double t,double k,int ihit);
  double ReflectCoverage(double x,double y,double z,int ihit);
  double effectiveReflectivityBroad(double x,double y,double z,double costheta,double phi);
private:
  AnalizeFiledata* data;
  AnalizeFile file;
  std::string funcname;
  int eventnum;
  int paranum;
  std::vector<hitinfo> allhitinfo;
  double doffset = 1.95775611238980325e+01;
  double retroratio = 0.;
  double expecteddarkhit;
  double conretro;
  TH2D* hPhotoCoverage = nullptr;
};

#endif
