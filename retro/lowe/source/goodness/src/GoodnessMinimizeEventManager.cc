// c++ STL
#include <iostream>
#include <cmath>
// ROOT library
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>

// Geant4 library
#include <CLHEP/Vector/ThreeVector.h>

// self
#include "GoodnessMinimizeEventManager.hh"

void GoodnessMinimizeEventManager::Doprocess()
{
  wcsimroottrigger = ProcessManager::GetProcessManager(0)->GetWCSimRootEvent()->GetTrigger(0);
  WCSimRootGeom* wcsimrootgeom = ProcessManager::GetProcessManager(0)->GetWCSimRootGeom();
  sumgoodness->SetHitInfo(wcsimroottrigger,wcsimrootgeom);
  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer();
  min->SetMaxFunctionCalls(maxfunctioncalls);
  min->SetMaxIterations(maxiterations);
  min->SetTolerance(tolerance);
  ROOT::Math::Functor f(sumgoodness,&fsumgoodness::returnvalueminus,nvar);
  min->SetFunction(f);
  variable[0] = currentprocess->Getfitted4Vector().x();
  variable[1] = currentprocess->Getfitted4Vector().y();
  variable[2] = currentprocess->Getfitted4Vector().z();
  variable[3] = currentprocess->Getfitted4Vector().t();
  variable[4] = currentprocess->GetCurrent3Direction().cosTheta();
  variable[5] = currentprocess->GetCurrent3Direction().phi();
  for(int i = 0;i < nvar;i++)
    {
      std::cout << "variable[" << i << "] is " << variable[i] << std::endl;
    }
  
  min->SetLimitedVariable(0,"x",variable[0],step[0],lower[0],upper[0]);
  min->SetLimitedVariable(1,"y",variable[1],step[1],lower[1],upper[1]);
  min->SetLimitedVariable(2,"z",variable[2],step[2],lower[2],upper[2]);
  min->SetLimitedVariable(3,"t",variable[3],step[3],lower[3],upper[3]);
  min->SetLimitedVariable(4,"costheta",variable[4],step[4],lower[4],upper[4]);
  min->SetLimitedVariable(5,"phi",variable[5],step[5],lower[5],upper[5]);
  
  min->Minimize();
  
  min->PrintResults();
  int status = min->Status();
  int ncalls = min->NCalls();
  int nIterations = min->NIterations();
  std::cout << "status is " << status << std::endl;
  std::cout << "ncalls is " << ncalls << std::endl;
  std::cout << "nIterations is " << nIterations << std::endl;
  const double* variable_out = min->X();
  double min_x = variable_out[0];
  double min_y = variable_out[1];
  double min_z = variable_out[2];
  double min_t = variable_out[3];
  std::cout << "min_x is " << min_x << std::endl;
  std::cout << "min_y is " << min_y << std::endl;
  std::cout << "min_z is " << min_z << std::endl;
  std::cout << "min_t is " << min_t << std::endl;
  currentprocess->Setminimizestatus(status);
  currentprocess->Setminimizencalls(ncalls);
  currentprocess->SetminimizenIterations(nIterations);
  CLHEP::HepLorentzVector vector_min;
  vector_min.set(min_x,min_y,min_z,min_t);
  currentprocess->Setfitted4Vector(vector_min);
  double min_costheta = variable_out[4];
  double min_phi = variable_out[5];
  std::cout << "min_costheta is " << min_costheta << std::endl;
  std::cout << "min_phi is " << min_phi << std::endl;
  CLHEP::Hep3Vector direction_min;
  double min_theta = std::acos(min_costheta);
  direction_min.setRThetaPhi(1.,min_theta,min_phi);
  currentprocess->SetCurrent3Direction(direction_min);
  double max_goodness_out = -f(variable_out);
  std::cout << "max_goodness_out is " << max_goodness_out << std::endl;
  currentprocess->Setgoodness(max_goodness_out);
}
