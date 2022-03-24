#ifndef GOODNESSCALCULATEMANAGER_HH
#define GOODNESSCALCULATEMANAGER_HH
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "OneGoodnessCalculateManager.hh"
#include "GoodnessCalculated.hh"
#include "GoodnessCalculateAction.hh"
#include "GoodnessParameters.hh"

class GoodnessCalculateManager
{
public:
  GoodnessCalculateManager();
  virtual ~GoodnessCalculateManager();
  void SetParameters();
  std::vector<double> GetDistance(CLHEP::Hep3Vector vec);
  void DoProcess(GoodnessCalculated* goodnesscalculated);
  void  goodness_given_4Vector();
  void goodness_given_4Vector_in(int k);
  void SetGoodnessCalculateAction(GoodnessCalculateAction* goodnesscalculateaction_in)
  {
    goodnesscalculateaction = goodnesscalculateaction_in;
  }
  void SetOneGoodnessCalculateAction(OneGoodnessCalculateAction* onegoodnesscalculateaction)
  {
   onegoodnesscalculatemanager->SetOneGoodnessCalculateAction(onegoodnesscalculateaction);
  }
private:
  OneGoodnessCalculateManager* onegoodnesscalculatemanager = nullptr;
  GoodnessCalculated* currentgoodnesscalculated = nullptr;
  GoodnessCalculateAction* goodnesscalculateaction = nullptr;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  int ncherenkovdigihits;
  GoodnessFunctionType::type goodnessfunctiontype;
};
#endif
