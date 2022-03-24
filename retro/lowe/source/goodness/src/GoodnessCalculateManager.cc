// geant4-library
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
// WCSim library
#include "WCSimRootEvent.hh"
// self-introduced library
#include "GoodnessCalculateManager.hh"
#include "GoodnessCalculated.hh"
#include "GoodnessManager.hh"
#include "OneGoodnessCalculated.hh"
GoodnessCalculateManager::GoodnessCalculateManager()
{
  onegoodnesscalculatemanager = new OneGoodnessCalculateManager();
}

GoodnessCalculateManager::~GoodnessCalculateManager()
{
  delete goodnesscalculateaction;
  delete onegoodnesscalculatemanager;
}

std::vector<double> GoodnessCalculateManager::GetDistance(CLHEP::Hep3Vector vec)
{
  wcsimroottrigger = GoodnessManager::GetGoodnessManager()->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  std::vector<double> vecd;
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      double distance = s;
    }
}

  
void GoodnessCalculateManager::SetParameters()
{
  
  wcsimrootgeom = GoodnessManager::GetGoodnessManager()->GetWCSimRootGeom();
  goodnessfunctiontype = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetGoodnessFunctionType();
  onegoodnesscalculatemanager->SetParameters();
}

void GoodnessCalculateManager::DoProcess(GoodnessCalculated* goodnesscalculated)
{
    wcsimroottrigger = GoodnessManager::GetGoodnessManager()->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  currentgoodnesscalculated = goodnesscalculated;
  goodnesscalculateaction->BeginOfGoodnessCalculate();
  
  if(goodnessfunctiontype == GoodnessFunctionType::normal)
    {
      goodness_given_4Vector();
    }
  goodnesscalculateaction->EndOfGoodnessCalculate();
}

void GoodnessCalculateManager::goodness_given_4Vector()
{
  for( int k = 0; k < ncherenkovdigihits ; ++k){
    goodness_given_4Vector_in(k);
  }
}

void GoodnessCalculateManager::goodness_given_4Vector_in(int k)
{
  static WCSimRootCherenkovDigiHit* hit;
  hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
  double time = hit->GetT();
  onegoodnesscalculated.SetHitTime(time);
  int tubeId = hit->GetTubeId();
  static WCSimRootPMT pmt;
  pmt = wcsimrootgeom->GetPMT(tubeId-1);
  double pmtX = pmt.GetPosition(0);
  double pmtY = pmt.GetPosition(1);
  double pmtZ = pmt.GetPosition(2);
  CLHEP::Hep3Vector pmt_position(pmtX,pmtY,pmtZ);
  onegoodnesscalculated.SetPMTPosition(pmt_position); 
  currentgoodnesscalculated->AddGoodness(onegoodnesscalculated.GetOneGoodness());
}
