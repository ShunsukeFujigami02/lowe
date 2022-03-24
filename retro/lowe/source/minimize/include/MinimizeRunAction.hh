#ifndef _MINIMIZERUNACTION_HH
#define _MINIMIZERUNACTION_HH
// STL
#include <memory>
// ROOT
#include <TFile.h>
#include <TTree.h>
#include <Math/Minimizer.h>
// self
#include "VAction.hh"
#include "TReconstructdata.hh"


class MinimizeRunAction : public VAction
{
public:
  MinimizeRunAction(const char* outfile_in,const char* outtree_in);
  virtual ~MinimizeRunAction()
  {
  };
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
  TTree* GetTTree()
  {
    return minimizetree;
  }
  TReconstructdata_minimize* GetTReconstructdata_minimize()
  {
    return data;
  }
private:
  const char* outfile;
  const char* outtree;
  TFile* file = nullptr;
  TTree* minimizetree = nullptr;
  TReconstructdata_minimize* data = nullptr;
};

#endif
