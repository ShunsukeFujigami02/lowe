#ifndef ONERUNGOODNESSANALIZEMANAGER_HH
#define ONERUNGOODNESSANALIZEMANAGER_HH
// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
// self-introduced library
#include "CSearch_range.hh"
#include "TReconstructdata.hh"
#include "OneGoodnessParameters.hh"

class OneRunGoodnessAnalizeManager : public TObject
{
public:
  OneRunGoodnessAnalizeManager();
  OneRunGoodnessAnalizeManager(const char* goodnessfile);
  void Setgoodnessfile(const char* goodnessfile);
  virtual ~OneRunGoodnessAnalizeManager();
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
  double Getgoodness(int i)
  {
    GetEntry(i);
    return data->Getgoodness();
  }
  
  CSearch_range GetCSearch_range()
  {
    return *range;
  }
  int Getnevent()
  {
    return neventgoodness;
  }
  OneGoodnessParameters* GetGoodnessParameters()
  {
    return onegoodnessparameters;
  }
  
private:
  TFile* gfile = nullptr;
  TTree* goodnessT = nullptr;
  TTree* optionT = nullptr;
  TReconstructdata* data = nullptr;
  CSearch_range* range = nullptr;
  int neventgoodness;
  OneGoodnessParameters* onegoodnessparameters;
public:
  ClassDef(OneRunGoodnessAnalizeManager,1)
};

#endif
