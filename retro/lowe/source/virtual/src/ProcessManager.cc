
// c++ STL
#include "ProcessManager.hh"
#include "Process.hh"

std::vector<std::shared_ptr<ProcessManager>> ProcessManager::vprocessmanager(0);

ProcessManager::ProcessManager()
{
}
void ProcessManager::SetProcessManager()
{
  vprocessmanager.push_back(shared_from_this());
}

void ProcessManager::Run(int N)
{
  std::cout << N << "event run start" << std::endl;
  if(action)
    action->BeginOfAction(currentprocess);
  for(int i = 0;i < N;i++)
    {
      std::cout << "event" << i << "start" << std::endl;
      ProcessOneEvent(i);
      std::cout << "event" << i << "end" << std::endl;
    }
  if(action)
    action->EndOfAction(currentprocess);
}

void ProcessManager::ProcessOneEvent(int)
{
  nextmanager->ProcessOne(currentprocess);
}

void ProcessManager::ProcessOne(std::shared_ptr<Process> process)
{
  currentprocess = process;
  if(action)
    action->BeginOfAction(currentprocess);
  Doprocess();
  if(action)
    action->EndOfAction(currentprocess);
}

void ProcessManager::SetHit(WCSimRootCherenkovDigiHit*)
{
}

