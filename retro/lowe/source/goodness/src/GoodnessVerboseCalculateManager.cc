// c++ STL
#include <memory>
// self-introduced library
#include "GoodnessVerboseCalculateManager.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "fgoodness.hh"
#include "tof.hh"
#include "distance_function.hh"

GoodnessVerboseCalculateManager::GoodnessVerboseCalculateManager()
{
}

GoodnessVerboseCalculateManager::~GoodnessVerboseCalculateManager()
{
}

void GoodnessVerboseCalculateManager::SetParameters()
{
  wcsimrootgeom = ProcessManager::GetProcessManager(0)->GetWCSimRootGeom();
}

void GoodnessVerboseCalculateManager::Doprocess()
{
  hitinfo info;
  info.Sethit(hit,wcsimrootgeom);
  Reconstructdata data;
  data.Set4Vector(currentprocess->Getfitted4Vector());
  std::shared_ptr<fgoodness> goodness_noretro = std::make_shared<fgoodness>();
  goodness_noretro->SetHitInfo(info);
  goodness_noretro->SetReconstructdata(data);
  std::shared_ptr<tof> ftof = std::make_shared<tof>();
  std::shared_ptr<distance_position_pmt> fdistance_function_noretro = std::make_shared<distance_position_pmt>();
  goodness_noretro->Settof(ftof);
  goodness_noretro->Setdistance_function(fdistance_function_noretro);
  goodness_noretro->Setsigma(sigma);
  double g_noretro = goodness_noretro->returnvalue();
  std::shared_ptr<fgoodness> goodness_onretro = std::make_shared<fgoodness>();
  goodness_onretro->SetHitInfo(info);
  goodness_onretro->SetReconstructdata(data);
  std::shared_ptr<distance_fly_retro> fdistance_function_onretro = std::make_shared<distance_fly_retro>();
  goodness_onretro->Settof(ftof);
  goodness_onretro->Setdistance_function(fdistance_function_onretro);
  goodness_onretro->Setsigma(sigma);
  double g_onretro = goodness_onretro->returnvalue();
  currentprocess->Setgoodness_onretro(g_onretro);
  currentprocess->Setgoodness_noretro(g_noretro);
  int hittype;
  if(g_noretro > g_onretro)
    hittype = 2;
  else
    hittype = 1;
  currentprocess->Sethittype(hittype);
}  
