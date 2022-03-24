// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "CSearch_range.hh"
#include "GoodnessParameters.hh"
#include "GoodnessManager.hh"
#include "GoodnessRunAction.hh"

#include "GoodnessVerboseManager.hh"
#include "GoodnessVerboseEventManager.hh"
#include "GoodnessVerboseCalculateManager.hh"
#include "GoodnessVerboseCalculateAction.hh"

int main()
{
  try
    {
      GoodnessParameters* goodnessparameters = new GoodnessParameters();
      goodnessparameters->SetGoodnessLoop4VectorType(GetEnum<GoodnessLoop4VectorType>("GOODNESSLOOP4VECTORTYPE"));
      goodnessparameters->SetGoodnessFunctionType(GetEnum<GoodnessFunctionType>("GOODNESSFUNCTIONTYPE"));
      goodnessparameters->SetOneGoodnessFunctionType(GetEnum<OneGoodnessFunctionType>("ONEGOODNESSFUNCTIONTYPE"));
      goodnessparameters->Setsigma(Getdouble("SIGMA"));
      CSearch_range range = GetCSearch_range();
      goodnessparameters->SetSearch_range(&range);
      goodnessparameters->SetReflectivity(Getdouble("REFLECTIVITY"));
      goodnessparameters->Print();
      GoodnessManager goodnessmanager(Getchar("INFILE"));
      goodnessmanager.SetGoodnessParameters(goodnessparameters);
      GoodnessRunAction* goodnessrunaction = new GoodnessRunAction(Getchar("OUTFILE"));
      goodnessmanager.SetGoodnessRunAction(goodnessrunaction);
      goodnessmanager.SetGoodnessEventAction(new GoodnessEventAction(goodnessrunaction));
      goodnessmanager.SetParameters();
      
      goodnessmanager.Run(Getint("NEVENTS"));
      //      delete goodnessmanager;


      /*      std::shared_ptr<GoodnessVerboseManager> goodnessverbosemanager = std::make_shared<GoodnessVerboseManager>(Getchar("INFILE"),Getchar("OUTFILE"));
      std::shared_ptr<GoodnessVerboseEventManager> goodnessverboseeventmanager = std::make_shared<GoodnessVerboseEventManager>();
      std::shared_ptr<GoodnessVerboseCalculateManager> goodnessverbosecalculatemanager = std::make_shared<GoodnessVerboseCalculateManager>();
      goodnessverbosemanager->SetProcessManager();
      goodnessverboseeventmanager->SetProcessManager();
      goodnessverbosecalculatemanager->SetProcessManager();
      goodnessverbosemanager->SetNextManager(goodnessverboseeventmanager);
      goodnessverboseeventmanager->SetNextManager(goodnessverbosecalculatemanager);
      goodnessverbosecalculatemanager->Setsigma(Getdouble("SIGMA"));
      goodnessverbosecalculatemanager->SetParameters();
      std::shared_ptr<GoodnessVerboseCalculateAction> goodnessverbosecalculateaction = std::make_shared<GoodnessVerboseCalculateAction>();
      goodnessverbosecalculatemanager->SetAction(goodnessverbosecalculateaction);
      std::shared_ptr<Process> process = std::make_shared<Process>();
      goodnessverbosemanager->SetProcess(process);
      goodnessverbosemanager->Run(Getint("NEVENTS"));*/
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range" << std::endl;
    }
  return 0;
}

