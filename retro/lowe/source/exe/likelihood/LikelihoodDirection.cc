// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "AngleRange.hh"
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionRunAction.hh"
#include "LikelihoodDirectionEventAction.hh"
#include "likelihood.hh"
#include "fdirection.hh"
#include "afunction.hh"

int main()
{
  try
    {
      std::shared_ptr<LikelihoodDirectionManager> likelihooddirectionmanager = std::make_shared<LikelihoodDirectionManager>(Getchar("INFILEGOODNESS"));
      std::shared_ptr<LikelihoodDirectionEventManager> likelihooddirectioneventmanager = std::make_shared<LikelihoodDirectionEventManager>();
      likelihooddirectionmanager->SetProcessManager();
      likelihooddirectioneventmanager->SetProcessManager();
      likelihooddirectionmanager->SetNextManager(likelihooddirectioneventmanager);
      AngleRange range = GetAngleRange();
      likelihooddirectioneventmanager->SetAngleRange(range);
      likelihooddirectioneventmanager->Settimewindownoretro(Getdouble("TIMEWINDOWNORETRO"));
      likelihooddirectioneventmanager->Settimewindowonretro(Getdouble("TIMEWINDOWONRETRO"));
      std::string slikelihoodfunctype = Getchar("ONELIKELIHOODDIRECTIONCALCULATETYPE");
      likelihooddirectioneventmanager->Setlikelihoodfunctype(slikelihoodfunctype);
      std::string sfdirfuncnoretrotype = Getchar("FDIRFUNCNORETROTYPE");
      std::string sfdirfunconretrotype = Getchar("FDIRFUNCONRETROTYPE");
      likelihooddirectioneventmanager->Setfdirnoretrotype(sfdirfuncnoretrotype);
      likelihooddirectioneventmanager->Setfdironretrotype(sfdirfunconretrotype);
      std::shared_ptr<afunction> afunctionnoretro = std::make_shared<afuncprototype>();
      std::shared_ptr<afunction> afunctiononretro = std::make_shared<afuncprototype>();
      likelihooddirectioneventmanager->Setafunctionnoretro(afunctionnoretro);
      likelihooddirectioneventmanager->Setafunctiononretro(afunctiononretro);
      std::shared_ptr<LikelihoodDirectionRunAction> likelihooddirectionrunaction = std::make_shared<LikelihoodDirectionRunAction>(Getchar("OUTFILE"));
      likelihooddirectionrunaction->SetAngleRange(range);
      likelihooddirectionmanager->SetAction(likelihooddirectionrunaction);
      std::shared_ptr<LikelihoodDirectionEventAction> likelihooddirectioneventaction = std::make_shared<LikelihoodDirectionEventAction>(likelihooddirectionrunaction);
      likelihooddirectioneventmanager->SetAction(likelihooddirectioneventaction);
      std::shared_ptr<Process> process = std::make_shared<Process>();
      likelihooddirectionmanager->SetProcess(process);
      likelihooddirectionmanager->Run(Getint("NEVENTS"));
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
