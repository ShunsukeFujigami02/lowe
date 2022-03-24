#ifndef _MINIMIZEEVENTMANAGER_HH
#define _MINIMIZEEVENTMANAGER_HH

#include <vector>
#include <string>

// self
#include "ProcessManager.hh"
#include "MinimizedFunction.hh"

class MinimizeEventManager : public ProcessManager
{
public:
  MinimizeEventManager()
  {
  };
  virtual ~MinimizeEventManager()
  {
  };
  void Doprocess();
  void SetMinimizedFunction(MinimizedFunction* func)
  {
    function = func;
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
  void SetNval(int num)
  {
    nvar = num;
  }
  void SetVarname(std::vector<std::string> var)
  {
    for(int i = 0;i < nvar;i++)
      {
	varname.push_back(var[i]);
      }
  }
  void Setstep(std::vector<double> s)
  {
    for(int i = 0;i < nvar;i++)
      {
	step.push_back(s[i]);
      }
  }
  void Setlower(std::vector<double> l)
  {
    for(int i = 0;i < nvar;i++)
      {
	lower.push_back(l[i]);
      }
  }
  void Setupper(std::vector<double> u)
  {
    for(int i = 0;i < nvar;i++)
      {
	upper.push_back(u[i]);
      }
  }
private:
  int ncherenkovdigihits;
  int maxfunctioncalls;
  int maxiterations;
  double tolerance;
  MinimizedFunction* function = nullptr;
  int nvar;
  std::vector<std::string> varname;
  std::vector<double> step;
  std::vector<double> lower;
  std::vector<double> upper;
};

#endif
  
  
  
