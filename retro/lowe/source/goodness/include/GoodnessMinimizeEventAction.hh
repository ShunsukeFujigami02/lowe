#ifndef GOODNESSMINIMIZEEVENTACTION_HH
#define GOODNESSMINIMIZEEVENTACTION_HH
// c++ STL
#include <memory>
// self introduced library
#include "GoodnessMinimizeRunAction.hh"

class GoodnessMinimizeEventAction : public VAction
{
public:
  GoodnessMinimizeEventAction(std::shared_ptr<GoodnessMinimizeRunAction> action)
  {
    goodnessminimizerunaction = action;
  }
  virtual ~GoodnessMinimizeEventAction()
  {
  }
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
private:
  std::shared_ptr<GoodnessMinimizeRunAction> goodnessminimizerunaction = nullptr;
};

#endif
