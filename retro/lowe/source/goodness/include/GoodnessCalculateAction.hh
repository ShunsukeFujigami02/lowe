#ifndef GOODNESSCALCULATEACTION_HH
#define GOODNESSCALCULATEACTION_HH

#include "GoodnessEventAction.hh"

class GoodnessCalculateAction
{
public:
  GoodnessCalculateAction(){};
  virtual ~GoodnessCalculateAction(){};
  GoodnessEventAction* GetGoodnessEventAction(){return goodnesseventaction;}
  void BeginOfGoodnessCalculate(){};
  void EndOfGoodnessCalculate(){};
private:
  GoodnessEventAction* goodnesseventaction = nullptr;
};

#endif
