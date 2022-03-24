#ifndef ONERUNGOODNESSMINIMIZEANALIZEMANAGER_HH
#define ONERUNGOODNESSMINIMIZEANALIZEMANAGER_HH

// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
// self
#include "TReconstructdata.hh"
#include "TOption_minimize.hh"
#include "OneGoodnessMinimizeParameters.hh"

class OneRunGoodnessMinimizeAnalizeManager : public TObject
{
public:
  OneRunGoodnessMinimizeAnalizeManager();
  OneRunGoodnessMinimizeAnalizeManager(const char* goodnessminimizefile);
  void Setgoodnessminimizefile(const char* goodnessminimizefile);
  virtual ~OneRunGoodnessMinimizeAnalizeManager();
  void GetEntry(int i);
  double GetT(int i)
  {
    GetEntry(i);
    return data->Get4Vector().T();
  }
  double GetX(int i)
  {
    GetEntry(i);
    return data->Get4Vector().X();
  }
  double GetY(int i)
  {
    GetEntry(i);
    return data->Get4Vector().Y();
  }
  double GetZ(int i)
  {
    GetEntry(i);
    return data->Get4Vector().Z();
  }
  double Getcostheta(int i)
  {
    GetEntry(i);
    return data->Getdirection().CosTheta();
  }
  double Getphi(int i)
  {
    GetEntry(i);
    return data->Getdirection().Phi();
  }

  TVector3 GetDirection(int i)
  {
    GetEntry(i);
    return data->Getdirection();
  }
  
  
  double Getgoodness(int i)
  {
    GetEntry(i);
    return data->Getgoodness();
  }
  
  int Getevent()
  {
    return neventgoodnessminimize;
  }
  OneGoodnessMinimizeParameters* GetGoodnessMinimizeParameters()
  {
    return onegoodnessminimizeparameters;
  }
private:
  TFile* gfile = nullptr;
  TTree* goodnessminimizeT = nullptr;
  TTree* gmoptionT = nullptr;
  TReconstructdata_minimize* data = nullptr;
  TOption_minimize* option = nullptr;
  int neventgoodnessminimize;
  OneGoodnessMinimizeParameters* onegoodnessminimizeparameters;
public:
  ClassDef(OneRunGoodnessMinimizeAnalizeManager,1)
};

#endif
  
