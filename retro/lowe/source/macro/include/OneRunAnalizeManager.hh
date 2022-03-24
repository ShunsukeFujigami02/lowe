#ifndef ANALIZEMANAGER_HH
#define ANALIZEMANAGER_HH

// ROOT library
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TH2D.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "goodness_data.hh"
#include "CSearch_range.hh"
#include "likelihood_direction_data.hh"
#include "AngleRange.hh"
#include "TReconstructdata.hh"
#include "OneRunDataAnalizeManager.hh"
#include "OneRunGoodnessAnalizeManager.hh"
#include "OneRunLikelihoodAnalizeManager.hh"
#include "OneRunGoodnessMinimizeAnalizeManager.hh"
#include "BiasError.hh"

class OneRunAnalizeManager : public TObject
{
public:
  OneRunAnalizeManager();
  OneRunAnalizeManager(const char* datafile,const char* mode);
  void Setdatafile(const char* datafile);
  void SetGoodnessfile(const char* goodnessfile);
  void SetLikelihoodfile(const char* likelihoodfile);
  void SetGoodnessMinimizefile(const char* goodnessminimizefile);
  virtual ~OneRunAnalizeManager();
  OneRunDataAnalizeManager* Getdatamanager()
  {
    return datamanager;
  }
  OneRunGoodnessAnalizeManager* Getgoodnessmanager()
  {
    return goodnessmanager;
  }
  OneRunLikelihoodAnalizeManager* Getlikelihoodmanager()
  {
    return likelihoodmanager;
  }
  OneRunGoodnessMinimizeAnalizeManager* Getgoodnessminimizemanager()
  {
    return goodnessminimizemanager;
  }
  void GetTH2DEvent(TH2D* h1,int n,const char* xvar,const char* yvar);
  void GetTH2DHit(TH2D* h1,int n,const char* xvar,const char* yvar);
  void GetTH1DEvent(TH1D* h1,int n,const char* var);
  void GetTH1DHit(TH1D* h1,int n,const char* var);
  void GetFuncmap1DTrue(TH1D* h1,const char* xvar,const char* yvar,int ievent);
  BiasError GetXBiasErrorbygoodness();
  BiasError GetYBiasErrorbygoodness();
  BiasError GetZBiasErrorbygoodness();
  double angleerror1sigma();
private:
  OneRunDataAnalizeManager* datamanager = nullptr;
  OneRunGoodnessAnalizeManager* goodnessmanager = nullptr;
  OneRunLikelihoodAnalizeManager* likelihoodmanager = nullptr;
  OneRunGoodnessMinimizeAnalizeManager* goodnessminimizemanager = nullptr;
  double GetVariableEvent(const char* valname,int i);
  double GetVariableHit(const char* valname,int ievent,int jhit);
public:
  ClassDef(OneRunAnalizeManager,1)
};


#endif
