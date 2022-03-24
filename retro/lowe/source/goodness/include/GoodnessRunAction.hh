#ifndef GOODNESSRUNACTION_HH
#define GOODNESSRUNACTION_HH

// ROOT library
#include <TTree.h>
// self-introduced library
#include "TReconstructdata.hh"
#include "CSearch_range.hh"
#include "MyString.hh"

class GoodnessRunAction
{
public:
  GoodnessRunAction(const char* outfile_in);
  virtual ~GoodnessRunAction(){};
public:
  void BeginOfRunAction();
  void EndOfRunAction();
  const char* Getoutfile(){return outfile;}
  TReconstructdata* GetReconstructdata(){ return data;}
  TTree* GetTTree(){ return goodnesstree;}
private:
  const char* outfile;
  TFile* file = nullptr;
  TTree* goodnesstree = nullptr;
  TReconstructdata* data = nullptr;
};

#endif
