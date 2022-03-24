#ifndef ONEDATAPARAMETERS_HH
#define ONEDATAPARAMETERS_HH
// c++ STL
#include <vector>
#include <cstring>
#include <utility>
// ROOT library
#include <TObject.h>
#include <TVector3.h>

class OneDataParameters : public TObject
{
public:
  OneDataParameters()
  {
  }
  
  virtual ~OneDataParameters()
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
  std::vector<std::pair<std::string,std::string>> vp;
  void Setpair(std::string filename);
  void SetValue();
  void PrintValue();
  bool isEqual(OneDataParameters compare,std::vector<std::string> exclusionname);
  std::string Getfile()
  {
    return file;
  }
  
private:
  std::vector<std::string> split(std::string& str);
  bool hasname(std::vector<std::string> vname,std::string name);
  std::string file;
public:
  ClassDef(OneDataParameters,1)
};

#endif
