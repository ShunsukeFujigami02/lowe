// c++ STL
#include <cmath>

// self-introduced library
#include "likelihood.hh"
#include "distance_function.hh"
#include "tof.hh"
#include "theta_i_func.hh"
#include "constants.hh"

double likelihoodnoretro::returnvalue()
{
  fdirnoretro->SetHitInfo(info);
  fdirnoretro->SetReconstructdata(data);
  afuncnoretro->SetHitInfo(info);
  afuncnoretro->SetReconstructdata(data);
  std::shared_ptr<distance_function> dfuncnoretro = std::make_shared<distance_position_pmt>();
  tof tofnoretro;
  tofnoretro.SetHitInfo(info);
  tofnoretro.SetReconstructdata(data);
  tofnoretro.Setdistancefunction(dfuncnoretro);
  double tof_no_retro = tofnoretro.returnvalue();
  double toferror = tof_no_retro - data.Get4Vector().t();
  double l = 0;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir = fdirnoretro->returnvalue();
      double afunc = afuncnoretro->returnvalue();
      theta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l = (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  return l;
}

double likelihoodonretro::returnvalue()
{
  fdironretro->SetHitInfo(info);
  fdironretro->SetReconstructdata(data);
  afunconretro->SetHitInfo(info);
  afunconretro->SetReconstructdata(data);
  std::shared_ptr<distance_function> dfunconretro = std::make_shared<distance_fly_retro>();
  tof tofonretro;
  tofonretro.SetHitInfo(info);
  tofonretro.SetReconstructdata(data);
  tofonretro.Setdistancefunction(dfunconretro);
  double tof_on_retro = tofonretro.returnvalue();
  double toferror = tof_on_retro - data.Get4Vector().t();
  double l = 0;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir = fdironretro->returnvalue();
      double afunc = afunconretro->returnvalue();
      theta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l = (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  return l;
}

double likelihoodsum::returnvalue()
{
  fdirnoretro->SetHitInfo(info);
  fdirnoretro->SetReconstructdata(data);
  afuncnoretro->SetHitInfo(info);
  afuncnoretro->SetReconstructdata(data);
  fdironretro->SetHitInfo(info);
  fdironretro->SetReconstructdata(data);
  afunconretro->SetHitInfo(info);
  afunconretro->SetReconstructdata(data);
  std::shared_ptr<distance_function> dfunconretro = std::make_shared<distance_fly_retro>();
  std::shared_ptr<distance_function> dfuncnoretro = std::make_shared<distance_position_pmt>();
  tof tofnoretro;
  tof tofonretro;
  tofonretro.SetHitInfo(info);
  tofonretro.SetReconstructdata(data);
  tofonretro.Setdistancefunction(dfunconretro);
  double tof_on_retro = tofonretro.returnvalue();
  double toferroronretro = tof_on_retro - data.Get4Vector().t();
  tofnoretro.SetHitInfo(info);
  tofnoretro.SetReconstructdata(data);
  tofnoretro.Setdistancefunction(dfunconretro);
  double tof_no_retro = tofnoretro.returnvalue();
  double toferrornoretro = tof_no_retro - data.Get4Vector().t();
  double l = 0;
  if(toferroronretro > -20. && toferroronretro < 20.)
    {
      double fdir = fdironretro->returnvalue();
      double afunc = afunconretro->returnvalue();
      theta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l += (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  if(toferrornoretro > -20. && toferrornoretro < 20.)
    {
      double fdir = fdirnoretro->returnvalue();
      double afunc = afuncnoretro->returnvalue();
      theta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l += (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  return l;
} 
