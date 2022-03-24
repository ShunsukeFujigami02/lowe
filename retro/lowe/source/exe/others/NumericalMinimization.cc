#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
 
double RosenBrock(const double *xx )
{
  const double x = xx[0];
  const double y = xx[1];
  const double tmp1 = y-x*x;
  const double tmp2 = 1-x;
  return 100*tmp1*tmp1+tmp2*tmp2;
}
 
int main()
{
    ROOT::Math::Minimizer* min = 
            ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("Minuit2", "Simplex");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("Minuit2", "Combined");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("Minuit2", "Scan");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("Minuit2", "Fumili");
  //  ROOT::Math::Minimizer* min = 
  //    ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "ConjugateFR");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "ConjugatePR");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "BFGS");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "BFGS2");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "SteepestDescent");
  //   ROOT::Math::Minimizer* min = 
  //          ROOT::Math::Factory::CreateMinimizer("GSLMultiFit", "");
  //   ROOT::Math::Minimizer* min = 
  //     ROOT::Math::Factory::CreateMinimizer();
 
  min->SetMaxFunctionCalls(1000000);
  min->SetMaxIterations(100000);
  min->SetTolerance(0.001);
 
  ROOT::Math::Functor f(&RosenBrock,2); 
  double step[2] = {0.01,0.01};
  double variable[2] = { -1.,1.2};
 
  min->SetFunction(f);
 
  // Set the free variables to be minimized!
  min->SetVariable(0,"x",variable[0], step[0]);
  min->SetVariable(1,"y",variable[1], step[1]);
 
  min->Minimize(); 
 
  const double *xs = min->X();
  std::cout << "Minimum: f(" << xs[0] << "," << xs[1] << "): " 
	    << RosenBrock(xs) << std::endl;
 
  return 0;
}
