#ifndef MULTIRUNANALIZEMANAGER_HH
#define MULTIRUNANALIZEMANAGER_HH
// c++ STL
#include <vector>
#include <cstring>
// ROOT library
#include <TClonesArray.h>
#include <TH1D.h>
// self-introduced library
#include "OneDataParameters.hh"
#include "OneGoodnessParameters.hh"
#include "OneLikelihoodParameters.hh"
#include "OneGoodnessMinimizeParameters.hh"
#include "OneRunAnalizeManager.hh"

class MultiRunAnalizeManager : public TObject
{
public:
  MultiRunAnalizeManager();
  void SetBasefile(const char* file);
  void SetComparefile(std::vector<std::string> vexclusionname);
  void SetAllfile();
  void PrintAllfile();
  void PrintComparefile();
  virtual ~MultiRunAnalizeManager();
  void GetTH1D(TH1D* h1,const char* xvar,const char* yvar,bool berror=false,const char* errorval="");
  double GetVariable(const char* var,OneRunAnalizeManager* oram);
  OneDataParameters basefileparameters;
  OneGoodnessParameters basegoodnessparameters;
  OneLikelihoodParameters baselikelihoodparameters;
  OneGoodnessMinimizeParameters basegoodnessminimizeparameters;
  std::vector<OneDataParameters> vdataparameters;
  std::vector<OneGoodnessParameters> vgoodnessparameters;
  std::vector<OneLikelihoodParameters> vlikelihoodparameters;
  std::vector<OneGoodnessMinimizeParameters> vgoodnessminimizeparameters;
  std::vector<OneRunAnalizeManager*> vrunanalizemanager;
private:
  std::string sbasefile;
  int mode; // datamode 0;goodnessmode 1;likelihoodmode 2;goodnessminimizemode 3
public:
  ClassDef(MultiRunAnalizeManager,1)
};

#endif
