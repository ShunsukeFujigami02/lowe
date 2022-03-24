#ifndef GOODNESSMINIMIZEEVENTMANAGER_HH
#define GOODNESSMINIMIZEEVENTMANAGER_HH

// self
#include "ProcessManager.hh"
#include "fsumgoodness.hh"

class GoodnessMinimizeEventManager : public ProcessManager
{
public:
  GoodnessMinimizeEventManager(){};
  virtual ~GoodnessMinimizeEventManager(){};
  void Doprocess();
  void Setfsumgoodness(fsumgoodness* f)
  {
    sumgoodness = f;
  }
  void Setmaxfunctioncalls(int max)
  {
    maxfunctioncalls = max;
  }
  void Setmaxiterations(int max)
  {
    maxiterations = max;
  }
  void Settolerance(double tol)
  {
    tolerance = tol;
  }
  static const int nvar = 6;
  void Setstep(double s[nvar])
  {
    for(int i = 0;i < nvar;i++)
      {
	step[i] = s[i];
      }
  }
  void Setlower(double l[nvar])
  {
    for(int i = 0;i < nvar;i++)
      {
	lower[i] = l[i];
      }
  }
  void Setupper(double u[nvar])
  {
    for(int i = 0;i < nvar;i++)
      {
	upper[i] = u[i];
      }
  }
  
private:
  int ncherenkovdigihits;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
  fsumgoodness* sumgoodness = nullptr;
  int maxfunctioncalls;
  int maxiterations;
  double tolerance;
  double step[nvar];
  double variable[nvar];
  double lower[nvar];
  double upper[nvar];
};

#endif
