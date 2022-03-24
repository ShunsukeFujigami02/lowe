#include "GoodnessVerboseEventManager.hh"

GoodnessVerboseEventManager::GoodnessVerboseEventManager()
{
}

GoodnessVerboseEventManager::~GoodnessVerboseEventManager()
{
}

void GoodnessVerboseEventManager::Doprocess()
{
  wcsimroottrigger = ProcessManager::GetProcessManager(0)->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0;k < ncherenkovdigihits; ++k)
    {
      Doloopin(k);
    }
}

void GoodnessVerboseEventManager::Doloopin(int k)
{
  currentprocess->Sethitnumber(k);
  static WCSimRootCherenkovDigiHit* hit;
  hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
  nextmanager->SetHit(hit);
  nextmanager->ProcessOne(currentprocess);
}

