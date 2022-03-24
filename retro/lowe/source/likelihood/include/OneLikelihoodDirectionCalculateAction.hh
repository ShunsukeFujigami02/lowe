#ifndef ONELIKELIHOODDIRECTIONCALCULATEACTION_HH
#define ONELIKELIHOODDIRECTIONCALCULATEACTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VAction.hh"
#include "LikelihoodDirectionEventAction.hh"

class OneLikelihoodDirectionCalculateAction : public VAction
{
  OneLikelihoodDirectionCalculateAction(std::shared_ptr<LikelihoodDirectionEventAction> action)
  {
    likelihooddirectioneventaction = action;
  }
  virtual ~OneLikelihoodDirectionCalculateAction()
  {
  }
  void BeginOfEventAction(std::shared_ptr<Process>)
  {
  }
  void EndOfEventAction(std::shared_ptr<Process> process);
private:
  std::shared_ptr<LikelihoodDirectionEventAction> likelihooddirectioneventaction = nullptr;
};

#endif
  
