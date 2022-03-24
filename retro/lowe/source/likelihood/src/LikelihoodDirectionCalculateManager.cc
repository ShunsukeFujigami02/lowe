// c++ STL
#include <iostream>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "LikelihoodDirectionCalculateManager.hh"
#include "LikelihoodDirectionManager.hh"
#include "OneLikelihoodDirectionCalculateManager.hh"
#include "Process.hh"

LikelihoodDirectionCalculateManager::LikelihoodDirectionCalculateManager()
{
}

LikelihoodDirectionCalculateManager::~LikelihoodDirectionCalculateManager()
{
}

void LikelihoodDirectionCalculateManager::Doprocess()
{
  wcsimroottrigger = ProcessManager::GetProcessManager(0)->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = currentprocess->Getncherenkovdigihits();
  for( int k = 0; k < ncherenkovdigihits; ++k)
    {
      Doloopin(k);
    }
}

void LikelihoodDirectionCalculateManager::Doloopin(int k)
{
  currentprocess->Sethitnumber(k);
  static WCSimRootCherenkovDigiHit* hit;
  hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
  nextmanager->SetHit(hit);
  nextmanager->ProcessOne(currentprocess);
}

