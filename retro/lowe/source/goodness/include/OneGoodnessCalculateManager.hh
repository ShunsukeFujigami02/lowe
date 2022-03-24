#ifndef ONEGOODNESSCALCULATEMANAGER_HH
#define ONEGOODNESSCALCULATEMANAGER_HH

#include "OneGoodnessCalculated.hh"
#include "OneGoodnessCalculateAction.hh"
#include "GoodnessParameters.hh"
class OneGoodnessCalculateManager
{
public:
  OneGoodnessCalculateManager();
  virtual ~OneGoodnessCalculateManager();
  void SetParameters();
  void DoProcess(OneGoodnessCalculated& onegoodnesscalculated_in);
  void SetOneGoodnessCalculated(const OneGoodnessCalculated& onegoodnesscalculated_in){onegoodnesscalculated = onegoodnesscalculated_in;}
  void one_goodness_on_retro();
  void one_goodness_no_retro();
  void one_goodness_sum();
  void one_goodness_compare();
  void SetOneGoodnessCalculateAction(OneGoodnessCalculateAction* onegoodnesscalculateaction_in)
  {
    onegoodnesscalculateaction = onegoodnesscalculateaction_in;
  }
  
private:
  OneGoodnessCalculateAction* onegoodnesscalculateaction = nullptr;
  OneGoodnessFunctionType::type onegoodnessfunctiontype;
  OneGoodnessCalculated onegoodnesscalculated;
  double sigma;
  double WCradius;
  double WClength;
};

#endif
