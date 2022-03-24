#ifndef ONELIKELIHOODPARAMETERS_HH
#define ONELIKELIHOODPARAMETERS_HH

// ROOT library
#include <TObject.h>
#include <TVector3.h>
// self
#include "CSearch_range.hh"
#include "AngleRange.hh"

class OneLikelihoodParameters : public TObject
{
public:
  OneLikelihoodParameters()
  {
  }
  virtual ~OneLikelihoodParameters()
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
  enum LikelihoodType
    {
      LikelihoodType_noretro,LikelihoodType_onretro,LikelihoodType_sum
    };
  LikelihoodType likelihoodtype;
  enum NoRetroFdirection
    {
      NoRetroFdirection_notuse,NoRetroFdirection_prototype,NoRetroFdirection_bydata
    };
  NoRetroFdirection noretrofdirection;
  enum OnRetroFdirection
    {
      OnRetroFdirection_notuse,OnRetroFdirection_prototype,OnRetroFdirection_bydata
    };
  OnRetroFdirection onretrofdirection;
  enum NoRetroAfunction
    {
      NoRetroAfunction_notuse,NoRetroAfunction_prototype
    };
  NoRetroAfunction noretroafunction;
  enum OnRetroAfunction
    {
      OnRetroAfunction_notuse,OnRetroAfunction_prototype
    };
  OnRetroAfunction onretroafunction;
  enum LikelihoodSearchRangeType
  {
    likelihoodsearchrangetype_true,likelihoodsearchrangetype_normal
  };
  LikelihoodSearchRangeType likelihoodsearchrangetype;
  double costhetanum;
  double phinum;
  double timewindownoretro;
  double timewindowonretro;
  std::vector<std::pair<std::string,std::string>> vp;
  void Setpair(std::string filename);
  void SetValue();
  void PrintValue();
  bool isEqual(OneLikelihoodParameters compare,std::vector<std::string> exclusionname);
  std::string Getfile()
  {
    return file;
  }
private:
  std::vector<std::string> split(std::string& str);
  bool hasname(std::vector<std::string> vname,std::string name);
  std::string file;
public:
  ClassDef(OneLikelihoodParameters,1)
};

#endif
    
    
    
    
