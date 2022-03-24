// ROOT
#include <TPython.h>

#include "MinimizeManager.hh"

MinimizeManager::MinimizeManager(const char* infile):ProcessManager()
{
  std::string sinfile = infile;
  TPython::Exec(("manager = macro.filemanager('" + sinfile + "')").c_str());
  Nevents = TPython::Eval("manager.GetNeventmax()");
}

void MinimizeManager::ProcessOneEvent(int i)
{
  currentprocess->SetCurrentEventNumber(i);
  nextmanager->ProcessOne(currentprocess);
}

