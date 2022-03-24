#ifndef GOODNESSVERBOSECALCULATEACTION_HH
#define GOODNESSVERBOSECALCULATEACTION_HH

// self-introduced library
#include "VAction.hh"

class GoodnessVerboseCalculateAction : public VAction
{
public:
  GoodnessVerboseCalculateAction(){}
  virtual ~GoodnessVerboseCalculateAction()
  {
  }
  void EndOfAction(std::shared_ptr<Process> process);
};

#endif
