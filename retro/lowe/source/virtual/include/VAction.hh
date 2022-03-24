#ifndef VACTION_HH
#define VACTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "Process.hh"

class VAction
{
public:
  VAction(){}
  virtual ~VAction()
  {
  }
  virtual void BeginOfAction(std::shared_ptr<Process> process);
  virtual void EndOfAction(std::shared_ptr<Process> process);
};

#endif
  
