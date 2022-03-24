// ROOT
#include <TPython.h>
// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "MinimizeManager.hh"
#include "MinimizeEventManager.hh"
#include "MinimizeRunAction.hh"
#include "MinimizeEventAction.hh"
#include "AnalizeFiledata.hh"
int main()
{
  AnalizeFiledata* data = new AnalizeFiledata();
  try
    {
      std::string sinfile = Getchar("INFILE");
      AnalizeFile file(sinfile);
      data->Construct(file);
      std::shared_ptr<MinimizeManager> minimizemanager = std::make_shared<MinimizeManager>(Getchar("INFILE"));
      std::shared_ptr<MinimizeEventManager> minimizeeventmanager = std::make_shared<MinimizeEventManager>();
      minimizemanager->SetProcessManager();
      minimizeeventmanager->SetProcessManager();
      minimizemanager->SetNextManager(minimizeeventmanager);
      MinimizedFunction* func = new MinimizedFunction(Getchar("MINIMIZEDFUNCNAME"),file,data,Getint("VNUM"));
      minimizeeventmanager->SetMinimizedFunction(func);
      minimizeeventmanager->Setmaxfunctioncalls(Getint("MAXFUNCTIONCALLS"));
      minimizeeventmanager->Setmaxiterations(Getint("MAXITERATIONS"));
      minimizeeventmanager->Settolerance(Getdouble("TOLERANCE"));
      int nvar = Getint("VNUM");
      std::vector<double> step;
      std::vector<double> lower;
      std::vector<double> upper;
      std::vector<std::string> varname = {"x","y","z","t","costheta","phi","darkrate"};
      for(int i = 0;i < nvar;i++)
	{
	  std::string sstep = "STEP" + std::to_string(i);
	  step.push_back(Getdouble(sstep.c_str()));
	  std::string slower = "LOWER" + std::to_string(i);
	  lower.push_back(Getdouble(slower.c_str()));
	  std::string supper = "UPPER" + std::to_string(i);
	  upper.push_back(Getdouble(supper.c_str()));
	}
      minimizeeventmanager->SetNval(nvar);
      minimizeeventmanager->Setstep(step);
      minimizeeventmanager->Setlower(lower);
      minimizeeventmanager->Setupper(upper);
      minimizeeventmanager->SetVarname(varname);
      std::shared_ptr<MinimizeRunAction> minimizerunaction = std::make_shared<MinimizeRunAction>(Getchar("OUTFILE"),Getchar("OUTTREE"));
      minimizemanager->SetAction(minimizerunaction);
      std::shared_ptr<MinimizeEventAction> minimizeeventaction = std::make_shared<MinimizeEventAction>(minimizerunaction,Getint("VNUM"));
      minimizeeventmanager->SetAction(minimizeeventaction);
      std::shared_ptr<Process> process = std::make_shared<Process>();
      minimizemanager->SetProcess(process);
      minimizemanager->Run(Getint("NEVENTS"));
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
      delete data;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range&" << std::endl;
    }
  delete data;
  return 0;
}
