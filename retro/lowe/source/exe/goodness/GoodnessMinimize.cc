// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "GoodnessMinimizeManager.hh"
#include "GoodnessMinimizeEventManager.hh"
#include "GoodnessMinimizeRunAction.hh"
#include "GoodnessMinimizeEventAction.hh"
#include "fsumgoodness.hh"


int main()
{
  try
    {
      std::shared_ptr<GoodnessMinimizeManager> goodnessminimizemanager = std::make_shared<GoodnessMinimizeManager>(Getchar("INFILELIKELIHOOD"));
      std::shared_ptr<GoodnessMinimizeEventManager> goodnessminimizeeventmanager = std::make_shared<GoodnessMinimizeEventManager>();
      goodnessminimizemanager->SetProcessManager();
      goodnessminimizeeventmanager->SetProcessManager();
      goodnessminimizemanager->SetNextManager(goodnessminimizeeventmanager);
      goodnessminimizeeventmanager->Setmaxfunctioncalls(Getint("MAXFUNCTIONCALLS"));
      goodnessminimizeeventmanager->Setmaxiterations(Getint("MAXITERATIONS"));
      goodnessminimizeeventmanager->Settolerance(Getdouble("TOLERANCE"));
      int nvar = 6;
      double step[nvar] = {Getdouble("STEPX"),Getdouble("STEPY"),Getdouble("STEPZ"),Getdouble("STEPT"),Getdouble("STEPCOSTHETA"),Getdouble("STEPPHI")};
      double lower[nvar] = {Getdouble("LOWERX"),Getdouble("LOWERY"),Getdouble("LOWERZ"),Getdouble("LOWERT"),Getdouble("LOWERCOSTHETA"),Getdouble("LOWERPHI")};
      double upper[nvar] = {Getdouble("UPPERX"),Getdouble("UPPERY"),Getdouble("UPPERZ"),Getdouble("UPPERT"),Getdouble("UPPERCOSTHETA"),Getdouble("UPPERPHI")};
      goodnessminimizeeventmanager->Setstep(step);
      goodnessminimizeeventmanager->Setlower(lower);
      goodnessminimizeeventmanager->Setupper(upper);
      TOption_minimize option;
      option.stepvec.SetXYZT(Getdouble("STEPX"),Getdouble("STEPY"),Getdouble("STEPZ"),Getdouble("STEPT"));
      option.stepcostheta = Getdouble("STEPCOSTHETA");
      option.stepphi = Getdouble("STEPPHI");
      option.lowervec.SetXYZT(Getdouble("LOWERX"),Getdouble("LOWERY"),Getdouble("LOWERZ"),Getdouble("LOWERT"));
      option.lowercostheta = Getdouble("LOWERCOSTHETA");
      option.lowerphi = Getdouble("LOWERPHI");
      option.uppervec.SetXYZT(Getdouble("UPPERX"),Getdouble("UPPERY"),Getdouble("UPPERZ"),Getdouble("UPPERT"));
      option.uppercostheta = Getdouble("UPPERCOSTHETA");
      option.upperphi = Getdouble("UPPERPHI");
      option.maxfunctioncalls = Getint("MAXFUNCTIONCALLS");
      option.maxiterations = Getint("MAXITERATIONS");
      option.tolerance = Getdouble("TOLERANCE");
      std::string sfsumgoodnesstype = Getchar("FSUMGOODNESSTYPE");
      std::shared_ptr<GoodnessMinimizeRunAction> goodnessminimizerunaction = std::make_shared<GoodnessMinimizeRunAction>(Getchar("OUTFILE"),Getchar("INFILELIKELIHOOD"));
      goodnessminimizerunaction->SetOption_minimize(option);
      goodnessminimizemanager->SetAction(goodnessminimizerunaction);
      std::shared_ptr<GoodnessMinimizeEventAction> goodnessminimizeeventaction = std::make_shared<GoodnessMinimizeEventAction>(goodnessminimizerunaction);
      goodnessminimizeeventmanager->SetAction(goodnessminimizeeventaction);
      if(sfsumgoodnesstype == "noretro")
	{
	  fsumgoodnessnoretro* sumgoodnessnoretro = new fsumgoodnessnoretro();
	  sumgoodnessnoretro->Setsigma(Getdouble("SIGMA"));
	  sumgoodnessnoretro->Setsigmaangle(Getdouble("SIGMAANGLE"));
	  goodnessminimizeeventmanager->Setfsumgoodness(sumgoodnessnoretro);
	  std::shared_ptr<Process> process = std::make_shared<Process>();
	  goodnessminimizemanager->SetProcess(process);
	  goodnessminimizemanager->Run(Getint("NEVENTS"));
	  delete sumgoodnessnoretro;
	}
      else if(sfsumgoodnesstype == "sum")
	{
	  fsumgoodnesssum* sumgoodnesssum = new fsumgoodnesssum();
	  sumgoodnesssum->Setsigma(Getdouble("SIGMA"));
	  sumgoodnesssum->Setsigmaangle(Getdouble("SIGMAANGLE"));
	  sumgoodnesssum->Setonretrocorrection(Getdouble("ONRETROCORRECTION"));
	  goodnessminimizeeventmanager->Setfsumgoodness(sumgoodnesssum);
	  std::shared_ptr<Process> process = std::make_shared<Process>();
	  goodnessminimizemanager->SetProcess(process);
	  goodnessminimizemanager->Run(Getint("NEVENTS"));
	  delete sumgoodnesssum;
	}
      else
	{
	  std::cout << sfsumgoodnesstype << " is not valid!" << std::endl;
	  throw "int main()";
	}
      
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range&" << std::endl;
    }
  return 0;
}

      
      
	
