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
  double l = 0;
  if(toferrornoretro > -timewindownoretro && toferrornoretro < timewindowonretro)
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
  double l = 0;
  if(toferroronretro > -timewindowonretro && toferroronretro < timewindowonretro)
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
  double l = 0;
  if(toferroronretro > -timewindowonretro && toferroronretro < timewindowonretro)
    {
      double fdir = fdironretro->returnvalue();
      double afunc = afunconretro->returnvalue();
      theta_i_func theta_i_f;
      theta_i_f.SetHitInfo(info);
      theta_i_f.SetReconstructdata(data);
      double theta_i = theta_i_f.returnvalue();
      l += (std::log(fdir))* std::cos(theta_i)/afunc;
    }
  if(toferrornoretro > -timewindownoretro && toferrornoretro < timewindownoretro)
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
