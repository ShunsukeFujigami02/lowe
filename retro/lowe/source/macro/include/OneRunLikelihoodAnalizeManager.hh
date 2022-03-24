#ifndef ONERUNLIKELIHOODANALIZEMANAGER_HH
#define ONERUNLIKELIHOODANALIZEMANAGER_HH

// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
// self-introduced library
#include "AngleRange.hh"
#include "TReconstructdata.hh"
#include "OneLikelihoodParameters.hh"

class OneRunLikelihoodAnalizeManager : public TObject
{
public:
  OneRunLikelihoodAnalizeManager();
  OneRunLikelihoodAnalizeManager(const char* likelihoodfile);
  void Setlikelihoodfile(const char* likelihoodfile);
  virtual ~OneRunLikelihoodAnalizeManager();
  void GetEntry(int i);
  AngleRange GetAngleRange()
  {
    return *range;
  }
  TVector3 GetDirection(int ievent)
  {
    GetEntry(ievent);
    return data->Getdirection();
  }
  
  int Getevent()
  {
    return neventlikelihood;
  }
  OneLikelihoodParameters* GetLikelihoodParameters()
  {
    return onelikelihoodparameters;
  }
  
private:
  TFile* lfile = nullptr;
  TTree* likelihoodT = nullptr;
  TTree* loptionT = nullptr;
  TReconstructdata* data = nullptr;
  AngleRange* range = nullptr;
  int neventlikelihood;
  OneLikelihoodParameters* onelikelihoodparameters;
public:
  ClassDef(OneRunLikelihoodAnalizeManager,1)
};

#endif
  
