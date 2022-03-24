#include <iostream>

#include "GoodnessVerboseCalculateAction.hh"
#include "ProcessManager.hh"
void GoodnessVerboseCalculateAction::EndOfAction(std::shared_ptr<Process> process)
{
  TReconstructdata* data = (ProcessManager::GetProcessManager(0))->GetTReconstructdata();
  
  data->addhit(process->Gethittype());
  data->Gethit(process->Gethitnumber()).Setonegoodnessnoretro(process->Getgoodness_noretro());
  data->Gethit(process->Gethitnumber()).Setonegoodnessonretro(process->Getgoodness_onretro());
}

