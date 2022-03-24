#ifndef _ANALIZEMANAGER_HH
#define _ANALIZEMANAGER_HH
// STL
#include <vector>
#include <map>

// ROOT
#include <TObject.h>
#include <TH1D.h>
#include <TH2D.h>
// self
#include "FileManager.hh"
#include "AnalizeFile.hh"
#include "AnalizeFiledata.hh"

class AnalizeManager : public TObject
{
public:
  AnalizeManager();
  virtual ~AnalizeManager()
  {
  }
  void cpFileList(FileManager* manager,std::string filelistname);
  //  std::vector<std::string> filelistname;
  std::map<std::string,std::map<std::string,AnalizeFile>> listoffilelist;
  static bool GetValue(AnalizeFile manager,AnalizeFiledata* data,std::string valueload,double& value,int ievent=0);
  bool GetValue(std::string flistname,AnalizeFile manager,AnalizeFiledata* data,std::string valueload,double& value);
  bool GetValueRun(AnalizeFile file,AnalizeFiledata* data,std::string valueload,double &value);
  bool GetValuehit(std::string valueload,double& value,AnalizeFile file,AnalizeFiledata* data,int ievent,int hitnum);
  bool isselectedevent(std::string cut,AnalizeFile file,AnalizeFiledata* data,int ievent);
  bool isselectedhit(std::string cut,AnalizeFile file,AnalizeFiledata* data,int ievent,int hitnum);
  void SetTH1D(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ievent);
  void SetTH1D(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname);
  void SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut="no",bool printeventnumber=false);
  AnalizeFile SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ifile,std::string cut="no",bool printeventnumber=false);
  void SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,AnalizeFile file,AnalizeFiledata* data,std::string cut="no",bool printeventnumber=false);
  void SetTH1DEvent(std::vector<TH1D*> h1,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut="no",bool printeventnumber=false);
  void SetTH2DEvent(TH2D* h,std::string xaxis,std::string yaxis,std::string valueaxis,std::string flistname,std::string cut="no",bool printeventnumber=false);
  void SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut="no");
  AnalizeFile SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ifile,std::string cut="no");
  void SetTH2DAllHit(TH2D* h1,std::string xaxis,std::string yaxis,std::string valueaxis,std::string flistname,std::string cut="no");
  AnalizeFile SetdoubleRun(double& value,std::string valueaxis,std::string flistname,int ifile);
  std::vector<double> SetTH1DFunctionDis(TH1D* h1,std::string funcname,int parnum,int variablenumber,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname="default");
  std::vector<double> SetTH2DFunctionDis(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname="default");
  std::vector<double> SetTH2DFunctionDisTrueaxis(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname="default");
  void SetTH2DFunctionDisTrueaxismultievent(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int nevent,std::string flistname,std::string minimizedfuncname="default");
  void SetTH2DCorrectionCoefficient(TH2D* h1,std::string flistname);
  void SetTH2DCorrectionCoefficientTrueAxis(TH2D* h1,std::string flistname);
  void PrintFilename();
  static double EnergyToMeanOnRetrodirectp0(double r);
  static double EnergyToMeanOnRetrodirectp1(double r);
  static double EnergyToMeanOnRetroreflectp0(double r);
  static double EnergyToMeanOnRetroreflectp1(double r);
  static double EnergyToSigmaOnRetrop0(double r);
  static double EnergyToSigmaOnRetrop1(double r);
  static double EnergyToSigmaOnRetrop2(double r);
  double doffset = 1.95775611238980325e+01;
  ClassDef(AnalizeManager,1)
};


#endif
