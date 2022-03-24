// c++
#include <cmath>

// self
#include "Tfsumgoodness.hh"
#include "Tfgoodness.hh"
#include "Tfgoodnessdirection.hh"

ClassImp(Tfsumgoodness)

ClassImp(Tfsumgoodnessnoretro)

ClassImp(Tfsumgoodnesssum)

double Tfsumgoodnessnoretro::returnvalue()
{
  double sum = 0.;
  int ncherenkovdigihits = (int)vhitinfo.size();
  Tfgoodness goodness;
  Tdistance_position_pmt* d_p_p = new Tdistance_position_pmt();
  Ttof* tof = new Ttof();
  goodness.Setdistancefunction(d_p_p);
  goodness.Settof(tof);
  goodness.Setsigma(sigma);
  goodness.SetReconstructdata(data);
  Tfgoodnessdirection goodnessd;
  goodnessd.SetReconstructdata(data);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      goodness.SetHitInfo(vhitinfo[k]);
      goodnessd.SetHitInfo(vhitinfo[k]);
      goodnessd.Setnoretromode();
      goodnessd.Setsigmaangle(sigmaangle);
      double g = goodness.returnvalue();
      double gd = goodnessd.returnvalue();
      sum += (g*gd);
    }
  delete d_p_p;
  delete tof;
  return sum;
}

double Tfsumgoodnesssum::returnvalue()
{
  double sum = 0.;
  Tfgoodness goodnessnoretro;
  Tdistance_position_pmt* d_p_p = new Tdistance_position_pmt();
  Ttof* tofnoretro = new Ttof();
  goodnessnoretro.Setdistancefunction(d_p_p);
  goodnessnoretro.Settof(tofnoretro);
  goodnessnoretro.SetReconstructdata(data);
  goodnessnoretro.Setsigma(sigma);
  Tfgoodnessdirection goodnessdnoretro;
  goodnessdnoretro.SetReconstructdata(data);
  goodnessdnoretro.Setnoretromode();
  goodnessdnoretro.Setsigmaangle(sigmaangle);
  Tfgoodness goodnessonretro;
  Tdistance_fly_retro* d_f_r = new Tdistance_fly_retro();
  Ttof* tofonretro = new Ttof();
  goodnessonretro.Setdistancefunction(d_f_r);
  goodnessonretro.Settof(tofonretro);
  goodnessonretro.SetReconstructdata(data);
  goodnessonretro.Setsigma(sigma);
  Tfgoodnessdirection goodnessdonretro;
  goodnessdonretro.SetReconstructdata(data);
  goodnessdonretro.Setonretromode();
  goodnessdonretro.Setsigmaangle(sigmaangle);
  int ncherenkovdigihits = (int)vhitinfo.size();
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      goodnessnoretro.SetHitInfo(vhitinfo[k]);
      goodnessdnoretro.SetHitInfo(vhitinfo[k]);
      double g = goodnessnoretro.returnvalue();
      double gd = goodnessdnoretro.returnvalue();
      goodnessonretro.SetHitInfo(vhitinfo[k]);
      goodnessdonretro.SetHitInfo(vhitinfo[k]);
      double go = goodnessonretro.returnvalue();
      double gdo = goodnessdonretro.returnvalue();
      sum += (g*gd + go* gdo);
    }
  delete d_p_p;
  delete tofnoretro;
  delete d_f_r;
  delete tofonretro;
  return sum;
  
}
  
