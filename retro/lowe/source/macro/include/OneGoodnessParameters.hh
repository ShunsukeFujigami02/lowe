#ifndef ONEGOODNESSPARAMETERS_HH
#define ONEGOODNESSPARAMETERS_HH
// c++ STL
#include <vector>
#include <cstring>
#include <utility>
// ROOT library
#include <TObject.h>
#include <TVector3.h>
// self
#include "CSearch_range.hh"

class OneGoodnessParameters
{
public:
  OneGoodnessParameters(){}
  virtual ~OneGoodnessParameters()
  {
  }
  enum Detector
    {
      SK,HK
    };
  Detector detector;
  enum Particle
    {
      electron,positron,muon,antimuon,proton
    };
  Particle particle;
  enum Postype
    {
      postype_fixed,postype_uniformrandom
    };
  Postype postype;
  TVector3 fixedPosition;
  TVector3 uniformPositionmin;
  TVector3 uniformPositionmax;
  enum Dirtype
    {
      dirtype_fixed,dirtype_uniformrandom
    };
  Dirtype dirtype;
  double fixedcostheta;
  double fixedphi;
  double uniformcosthetamin;
  double uniformcosthetamax;
  double uniformphimin;
  double uniformphimax;
  enum Etype
    {
      etype_fixed,etype_uniformrandom
    };
  Etype etype;
  double fixedenergy;
  double uniformenergymin;
  double uniformenergymax;
  enum Inforeflectivity
    {
      Inforeflectivity_blacksheet,Inforeflectivity_conventional,Inforeflectivity_trapezoid
    };
  Inforeflectivity inforeflectivity;
  double trapezoidreflectivity;
  double trapezoidanglemin;
  double trapezoidanglemax;
  enum Reflectspread
    {
      Reflectspread_blacksheet,nospread
    };
  Reflectspread reflectspread;
  int triggerthereshold;
  double triggerwindow;
  double triggerprewindow;
  double triggerpostwindow;
  double darkrate;
  bool adjustfornoise;
  int eventnumber;
  double sigma;
  enum GoodnessType
    {
      GoodnessType_noretro,GoodnessType_onretro,GoodnessType_sum,GoodnessType_compare
    };
  GoodnessType goodnesstype;
  enum GoodnessSearchRangeType
    {
      GSRT_true,GSRT_normal
    };
  GoodnessSearchRangeType goodnesssearchrangetype;
  CSearch_range searchrange;
  int goodnesseventnumber;
  std::vector<std::pair<std::string,std::string>> vp;
  void Setpair(std::string filename);
  void SetValue();
  void PrintValue();
  bool isEqual(OneGoodnessParameters compare,std::vector<std::string> exclusionname);
  std::string Getfile()
  {
    return file;
  }
private:
  std::vector<std::string> split(std::string& str);
  bool hasname(std::vector<std::string> vname,std::string name);
  std::string file;
public:
  ClassDef(OneGoodnessParameters,1)
};

#endif
  
