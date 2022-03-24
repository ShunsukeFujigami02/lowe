#ifndef _MINIMIZEEVENTACTION_HH
#define _MINIMIZEEVENTACTION_HH
// c++ STL
#include <memory>
// self introduced library
#include "MinimizeRunAction.hh"

class MinimizeEventAction : public VAction
{
public:
  MinimizeEventAction(std::shared_ptr<MinimizeRunAction> action,int nval)
  {
    minimizerunaction = action;
    npar = nval;
  }
  virtual ~MinimizeEventAction()
  {
  }
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
private:
  int npar;
  std::shared_ptr<MinimizeRunAction> minimizerunaction = nullptr;
};

#endif
