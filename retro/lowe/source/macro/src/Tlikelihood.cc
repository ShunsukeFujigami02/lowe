// c++ STL
#include <cmath>

// self-introduced library
#include "Tlikelihood.hh"
#include "Tdistance_function.hh"
#include "Ttof.hh"
#include "Ttheta_i_func.hh"
#include "constants.hh"

ClassImp(Tlikelihood)
ClassImp(Tlikelihoodnoretro)
ClassImp(Tlikelihoodonretro)
ClassImp(Tlikelihoodsum)

double Tlikelihoodnoretro::returnvalue()
{
  fdirnoretro->SetHitInfo(info);
  fdirnoretro->SetReconstructdata(data);
  afuncnoretro->SetHitInfo(info);
  afuncnoretro->SetReconstructdata(data);
  Tdistance_function* dfuncnoretro = new Tdistance_position_pmt();
  Ttof tofnoretro;
  tofnoretro.SetHitInfo(info);
  tofnoretro.SetReconstructdata(data);
  tofnoretro.Setdistancefunction(dfuncnoretro);
  double tof_no_retro = tofnoretro.returnvalue();
  double toferror = tof_no_retro - data.Get4Vector().T();
  double l = 0;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir = fdirnoretro->returnvalue();
      double afunc = afuncnoretro->returnvalue();
      Ttheta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l = (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  delete dfuncnoretro;
  return l;
}

double Tlikelihoodonretro::returnvalue()
{
  fdironretro->SetHitInfo(info);
  fdironretro->SetReconstructdata(data);
  afunconretro->SetHitInfo(info);
  afunconretro->SetReconstructdata(data);
  Tdistance_function* dfunconretro = new Tdistance_fly_retro();
  Ttof tofonretro;
  tofonretro.SetHitInfo(info);
  tofonretro.SetReconstructdata(data);
  tofonretro.Setdistancefunction(dfunconretro);
  double tof_on_retro = tofonretro.returnvalue();
  double toferror = tof_on_retro - data.Get4Vector().T();
  double l = 0;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir = fdironretro->returnvalue();
      double afunc = afunconretro->returnvalue();
      Ttheta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l = (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  delete dfunconretro;
  return l;
}

double Tlikelihoodsum::returnvalue()
{
  fdirnoretro->SetHitInfo(info);
  fdirnoretro->SetReconstructdata(data);
  afuncnoretro->SetHitInfo(info);
  afuncnoretro->SetReconstructdata(data);
  fdironretro->SetHitInfo(info);
  fdironretro->SetReconstructdata(data);
  afunconretro->SetHitInfo(info);
  afunconretro->SetReconstructdata(data);
  Tdistance_function* dfunconretro = new Tdistance_fly_retro();
  Tdistance_function* dfuncnoretro = new Tdistance_position_pmt();
  Ttof tofnoretro;
  Ttof tofonretro;
  tofonretro.SetHitInfo(info);
  tofonretro.SetReconstructdata(data);
  tofonretro.Setdistancefunction(dfunconretro);
  double tof_on_retro = tofonretro.returnvalue();
  double toferroronretro = tof_on_retro - data.Get4Vector().T();
  tofnoretro.SetHitInfo(info);
  tofnoretro.SetReconstructdata(data);
  tofnoretro.Setdistancefunction(dfunconretro);
  double tof_no_retro = tofnoretro.returnvalue();
  double toferrornoretro = tof_no_retro - data.Get4Vector().T();
  double l = 0;
  if(toferroronretro > -20. && toferroronretro < 20.)
    {
      double fdir = fdironretro->returnvalue();
      double afunc = afunconretro->returnvalue();
      Ttheta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l += (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  if(toferrornoretro > -20. && toferrornoretro < 20.)
    {
      double fdir = fdirnoretro->returnvalue();
      double afunc = afuncnoretro->returnvalue();
      Ttheta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l += (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  delete dfunconretro;
  delete dfuncnoretro;
  return l;
} 
