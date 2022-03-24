#ifndef _MINIMIZEMANAGER_HH
#define _MINIMIZEMANAGER_HH

// self
#include "ProcessManager.hh"

class MinimizeManager : public ProcessManager
{
public:
  MinimizeManager() = delete;
  MinimizeManager(const char* infile);
  virtual ~MinimizeManager(){};
  void Doprocess()
  {
  }
  void ProcessOneEvent(int i);
private:
  int Nevents;
};

#endif
