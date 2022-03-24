#ifndef GOODNESSEVENTACTION_HH
#define GOODNESSEVENTACTION_HH

// self-introduced library
#include "GoodnessRunAction.hh"
#include "GoodnessEvent.hh"

class GoodnessEventAction
{
public:
  GoodnessEventAction(GoodnessRunAction* goodnessrunaction_in);
  virtual ~GoodnessEventAction(){};
  GoodnessRunAction* GetRunAction(){ return goodnessrunaction;}
  void BeginOfEventAction();
  void EndOfEventAction(const GoodnessEvent* goodnessevent);
private:
  GoodnessRunAction* goodnessrunaction;
};
#endif
