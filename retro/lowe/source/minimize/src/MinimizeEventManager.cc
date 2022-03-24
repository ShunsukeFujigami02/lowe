
// ROOT
#include <TPython.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>

#include "MinimizeEventManager.hh"

void MinimizeEventManager::Doprocess()
{
  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer();
  min->SetMaxFunctionCalls(maxfunctioncalls);
  min->SetMaxIterations(maxiterations);
  min->SetTolerance(tolerance);
  function->SetEventNumber(currentprocess->GetCurrentEventNumber());
  std::vector<double> firstvalue = function->Getfirstvalue();
  ROOT::Math::Functor f(function,&MinimizedFunction::returnvalue,nvar);
  min->SetFunction(f);
  for(int i = 0;i != nvar;i++)
    {
      min->SetLimitedVariable(i,varname[i].c_str(),firstvalue[i],step[i],lower[i],upper[i]);
    }
  min->Minimize();

  min->PrintResults();
  currentprocess->SetMinimizer(min);
}
