#ifndef GOODNESSMINIMIZERUNACTION_HH
#define GOODNESSMINIMIZERUNACTION_HH
// c++ STL
#include <memory>
// ROOT library
#include <TFile.h>
#include <TTree.h>

// self-introduced library
#include "TOption_minimize.hh"
#include "VAction.hh"
#include "TReconstructdata.hh"
#include "MyString.hh"

class GoodnessMinimizeRunAction : public VAction
{
public:
  GoodnessMinimizeRunAction(const char* outfile_in,const char* infilelikelihood_in);
  virtual ~GoodnessMinimizeRunAction(){};
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
  TTree* GetTTree()
  {
    return goodnessminimizetree;
  }
  void SetOption_minimize(TOption_minimize op)
  {
    optionin = op;
  }
  TReconstructdata_minimize* GetTReconstructdata_minimize()
  {
    return data;
  }
  
private:
  const char* outfile;
  const char* cinfilelikelihood;
  MyString* infiledata = nullptr;
  MyString* infilegoodness = nullptr;
  MyString* infilelikelihood = nullptr;
  TFile* file = nullptr;
  TTree* goodnessminimizetree = nullptr;
  TTree* optiontree = nullptr;
  TReconstructdata_minimize* data = nullptr;
  TOption_minimize* option = nullptr;
  TOption_minimize optionin;
};

#endif
  
