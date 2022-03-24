// c++
#include <memory>
#include <cmath>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self
#include "fsumgoodness.hh"
#include "fgoodness.hh"
#include "fgoodnessdirection.hh"


void fsumgoodness::SetHitInfo(WCSimRootTrigger* trigger,WCSimRootGeom* geom)
{
  wcsimroottrigger = trigger;
  wcsimrootgeom = geom;
}

      

double fsumgoodnessnoretro::returnvalue()
{
  double sum = 0;
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      hitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      fgoodness goodness;
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      goodness.Setdistance_function(d_p_p);
      goodness.Settof(ftof);
      goodness.SetHitInfo(info);
      goodness.SetReconstructdata(data);
      goodness.Setsigma(sigma);
      fgoodnessdirection goodnessd;
      goodnessd.SetHitInfo(info);
      goodnessd.SetReconstructdata(data);
      goodnessd.Setnoretromode();
      goodnessd.Setsigmaangle(sigmaangle);
      double g = goodness.returnvalue();
      double gd = goodnessd.returnvalue();
      sum += (g*gd);
    }
  return sum;
}

double fsumgoodnessnoretro::returnvalueminus(const double* a)
{
  CLHEP::HepLorentzVector vector;
  vector.set(a[0],a[1],a[2],a[3]);
  data.Set4Vector(vector);
  CLHEP::Hep3Vector vec;
  vec.setRThetaPhi(1.,std::acos(a[4]),a[5]);
  data.Setdirection(vec);
  return -returnvalue();
}


double fsumgoodnesssum::returnvalue()
{
  double sum = 0;
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0; k < ncherenkovdigihits; k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      hitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      fgoodness goodnessnoretro;
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftofnoretro = std::make_shared<tof>();
      goodnessnoretro.Setdistance_function(d_p_p);
      goodnessnoretro.Settof(ftofnoretro);
      goodnessnoretro.SetHitInfo(info);
      goodnessnoretro.SetReconstructdata(data);
      goodnessnoretro.Setsigma(sigma);
      fgoodnessdirection goodnessdnoretro;
      goodnessdnoretro.SetHitInfo(info);
      goodnessdnoretro.SetReconstructdata(data);
      goodnessdnoretro.Setnoretromode();
      goodnessdnoretro.Setsigmaangle(sigmaangle);
      double g = goodnessnoretro.returnvalue();
      double gd = goodnessdnoretro.returnvalue();
      fgoodness goodnessonretro;
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      goodnessonretro.Setdistance_function(d_f_r);
      goodnessonretro.Settof(ftofonretro);
      goodnessonretro.SetHitInfo(info);
      goodnessonretro.SetReconstructdata(data);
      goodnessonretro.Setsigma(sigma);
      fgoodnessdirection goodnessdonretro;
      goodnessdonretro.SetHitInfo(info);
      goodnessdonretro.SetReconstructdata(data);
      goodnessdonretro.Setonretromode();
      goodnessdonretro.Setsigmaangle(sigmaangle);
      double go = goodnessonretro.returnvalue();
      double gdo = goodnessdonretro.returnvalue();
      sum += (g*gd + onretrocorrection*go*gdo);
    }
  return sum;
}

double fsumgoodnesssum::returnvalueminus(const double* a)
{
  CLHEP::HepLorentzVector vector;
  vector.set(a[0],a[1],a[2],a[3]);
  data.Set4Vector(vector);
  CLHEP::Hep3Vector vec;
  vec.setRThetaPhi(1.,std::acos(a[4]),a[5]);
  data.Setdirection(vec);
  return -returnvalue();
}
