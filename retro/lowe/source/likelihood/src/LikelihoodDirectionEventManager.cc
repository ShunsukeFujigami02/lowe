// c++ STL
#include <iostream>
#include <cmath>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "LikelihoodDirectionEventManager.hh"
#include "tof.hh"
#include "distance_function.hh"
#include "theta_i_func.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "afunction.hh"
// fmath
#include <fmath.hpp>

LikelihoodDirectionEventManager::LikelihoodDirectionEventManager()
{
}

LikelihoodDirectionEventManager::~LikelihoodDirectionEventManager()
{
}

void LikelihoodDirectionEventManager::Doprocess()
{
  maxlikelihood = -1000000.;
  WCSimRootTrigger* wcsimroottrigger = ProcessManager::GetProcessManager(0)->GetWCSimRootEvent()->GetTrigger(0);
  WCSimRootGeom* wcsimrootgeom = ProcessManager::GetProcessManager(0)->GetWCSimRootGeom();
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  currentprocess->Setncherenkovdigihits(ncherenkovdigihits);
  vonelikelihoodonretro = std::vector<double>(ncherenkovdigihits,0.);
  vonelikelihoodnoretro = std::vector<double>(ncherenkovdigihits,0.);
  vmaxonelikelihoodonretro = std::vector<double>(ncherenkovdigihits,0.);
  vmaxonelikelihoodnoretro = std::vector<double>(ncherenkovdigihits,0.);
  currentprocess->maxonelikelihoodnoretro = std::vector<double>(ncherenkovdigihits,0.);
  currentprocess->maxonelikelihoodonretro = std::vector<double>(ncherenkovdigihits,0.);
  vcostheta_ioveranoretro = std::vector<double>(ncherenkovdigihits,0.);
  vcostheta_ioveraonretro = std::vector<double>(ncherenkovdigihits,0.);
  hminusvxnor = std::vector<double>(ncherenkovdigihits,0.);
  hminusvynor = std::vector<double>(ncherenkovdigihits,0.);
  hminusvznor = std::vector<double>(ncherenkovdigihits,0.);
  isbetweentimewindownoretro = std::vector<int>(ncherenkovdigihits);
  isbetweentimewindowonretro = std::vector<int>(ncherenkovdigihits);
  isbetweentimewindowatleastone = std::vector<int>(ncherenkovdigihits);
  Reconstructdata data;
  data.Set4Vector(currentprocess->Getfitted4Vector());
  fittedposition = currentprocess->Getfitted4Vector().vect();
  afunctionnoretro->SetReconstructdata(data);
  afunctiononretro->SetReconstructdata(data);
  if(slikelihoodfunctype == "sum")
    likelihoodfunctype = 1;
  else if(slikelihoodfunctype == "noretro")
    likelihoodfunctype = 0;
  else
    {
      std::cout << slikelihoodfunctype << " is not valid..." << std::endl;
      throw "void LikelihoodDirectionEventManager::Doprocess()";
    }
  if(sfdirnoretrotype == "prototype")
    fdirnoretrotype = 0;
  else if(sfdirnoretrotype == "bydata")
    fdirnoretrotype = 1;
  else
    {
      std::cout << sfdirnoretrotype << " is not valid..." << std::endl;
      throw "void LikelihoodDirectionEventManager::Doprocess()";
    }
  if(sfdironretrotype == "prototype")
    fdironretrotype = 0;
  else if(sfdironretrotype == "bydata")
    fdironretrotype = 1;
  else
    {
      std::cout << sfdironretrotype << " is not valid..." << std::endl;
      throw "void LikelihoodDirectionEventManager::Doprocess()";
    }
  for(size_t k = 0; k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      hitinfo info;
      info.Sethit(hit,wcsimrootgeom);
      std::shared_ptr<distance_function> dfunconretro = std::make_shared<distance_fly_retro>();
      std::shared_ptr<distance_function> dfuncnoretro = std::make_shared<distance_position_pmt>();
      tof tofnoretro;
      tof tofonretro;
      tofonretro.SetHitInfo(info);
      tofonretro.SetReconstructdata(data);
      tofonretro.Setdistancefunction(dfunconretro);
      double tof_on_retro = tofonretro.returnvalue();
      double toferroronretro = tof_on_retro - data.Get4Vector().t();
      if(toferroronretro < timewindowonretro && toferroronretro > -timewindowonretro)
	isbetweentimewindowonretro[k] = 1;
      else
	isbetweentimewindowonretro[k] = 0;
      tofnoretro.SetHitInfo(info);
      tofnoretro.SetReconstructdata(data);
      tofnoretro.Setdistancefunction(dfuncnoretro);
      double tof_no_retro = tofnoretro.returnvalue();
      double toferrornoretro = tof_no_retro - data.Get4Vector().t();
      if(toferrornoretro < timewindownoretro && toferrornoretro > -timewindownoretro)
	isbetweentimewindownoretro[k] = 1;
      else
	isbetweentimewindownoretro[k] = 0;
      if((isbetweentimewindownoretro[k] == 1) || (isbetweentimewindowonretro[k] == 1))
	isbetweentimewindowatleastone[k] = 1;
      else
	isbetweentimewindowatleastone[k] = 0;
      theta_i_func t_i_f;
      t_i_f.SetHitInfo(info);
      t_i_f.SetReconstructdata(data);
      double theta_i = t_i_f.returnvalue();
      double costheta_i = std::cos(theta_i);
      afunctionnoretro->SetHitInfo(info);
      afunctiononretro->SetHitInfo(info);
      double anoretro = afunctionnoretro->returnvalue();
      double aonretro = afunctiononretro->returnvalue();
      vcostheta_ioveranoretro[k] = costheta_i/anoretro;
      vcostheta_ioveraonretro[k] = costheta_i/aonretro;
      double hminusvx = ( info.Get3Position().x() - data.Get3Position().x());
      double hminusvz = ( info.Get3Position().z() - data.Get3Position().z());	    
      double hminusvy = ( info.Get3Position().y() - data.Get3Position().y());
      double hminusvmag = std::sqrt(hminusvx*hminusvx + hminusvy*hminusvy + hminusvz*hminusvz);
      hminusvxnor[k] = hminusvx/hminusvmag;
      hminusvynor[k] = hminusvy/hminusvmag;
      hminusvznor[k] = hminusvz/hminusvmag;
    }
  double costheta = range.GetCosthetamin();
  for(int i = 0; i < range.GetCosthetaNum(); ++i , costheta += range.GetCosthetawidth())
    {
      currentcostheta = costheta;
      double sintheta = std::sqrt(1-costheta*costheta);
      double phi = range.GetPhimin();
      for(int j = 0; j < range.GetPhiNum(); j++ , phi += range.GetPhiwidth())
	{
	  currentphi = phi;
	  currentdirectionx = sintheta* std::cos(phi);
	  currentdirectiony = sintheta* std::sin(phi);
	  currentdirectionz = costheta;
	  Doloopin();
	}
    }
  currentprocess->SetMaxlikelihood(maxlikelihood);
  CLHEP::Hep3Vector max3direction;
  max3direction.setRThetaPhi(1.,std::acos(maxcostheta),maxphi);
  currentprocess->SetMax3Direction(max3direction);
  for(size_t k = 0;k < ncherenkovdigihits;k++)
    {
      currentprocess->maxonelikelihoodnoretro[k] = vmaxonelikelihoodnoretro[k];
      currentprocess->maxonelikelihoodonretro[k] = vmaxonelikelihoodonretro[k];
    }
  
}

void LikelihoodDirectionEventManager::Doloopin()
{
  currentlikelihood = 0.;
  if(likelihoodfunctype == 0)
    {
      for(size_t k = 0; k < ncherenkovdigihits; ++k)
	{
	  if(isbetweentimewindownoretro[k] == 1)
	    currentlikelihood+= likelihoodnoretro(k);
	}
    }
  if(likelihoodfunctype == 1)
    {
      for(size_t k = 0; k < ncherenkovdigihits; ++k)
	{
	  if(isbetweentimewindowatleastone[k] == 1)
	    currentlikelihood+= likelihoodsum(k);
	}
    }
  if(maxlikelihood < currentlikelihood)
    {
      maxlikelihood = currentlikelihood;
      maxcostheta = currentcostheta;
      maxphi = currentphi;
	  vmaxonelikelihoodonretro = vonelikelihoodonretro;
	  vmaxonelikelihoodnoretro = vonelikelihoodnoretro;
    }
}


double LikelihoodDirectionEventManager::likelihoodnoretro(const size_t& k)
{
  double l = 0.;
  if(isbetweentimewindownoretro[k] == 1)
    {
      double costheta_dir_i = costheta_dir_i_func(k);
      double fdir = 0.;
      if(fdirnoretrotype == 0)
	fdir = fdirectionnoretro_prototype(costheta_dir_i);
      else if(fdirnoretrotype == 1)
	fdir = fdirectionnoretro_bydata(costheta_dir_i);
      l = (std::log(fdir)* vcostheta_ioveranoretro[k]);
      vonelikelihoodnoretro[k] = l;
    }
  return l;
}

double LikelihoodDirectionEventManager::likelihoodsum(const size_t& k)
{
  double l = 0.;
  double lnoretro = 0.;
  double lonretro = 0.;
  double costheta_dir_i = costheta_dir_i_func(k);
  double fdirnoretro = 1.;
  if(isbetweentimewindownoretro[k] == 1)
    {
      if(fdirnoretrotype == 0)
	fdirnoretro = fdirectionnoretro_prototype(costheta_dir_i);
      else if(fdirnoretrotype == 1)
	fdirnoretro = fdirectionnoretro_bydata(costheta_dir_i);
      lnoretro = (std::log(fdirnoretro) * vcostheta_ioveranoretro[k]);
    }
  double fdironretro = 1.;
  if(isbetweentimewindowonretro[k] == 1)
    {
      if(fdironretrotype == 0)
	fdironretro = fdirectiononretro_prototype(costheta_dir_i);
      else if(fdironretrotype == 1)
	fdironretro = fdirectiononretro_bydata(costheta_dir_i);
      lonretro = (std::log(fdironretro) * vcostheta_ioveraonretro[k]);
    }
  vonelikelihoodnoretro[k] = lnoretro;
  vonelikelihoodonretro[k] = lonretro;
  l = lnoretro + lonretro;
  return l;
}

double LikelihoodDirectionEventManager::costheta_dir_i_func(const size_t& k) const
{
  return (hminusvxnor[k]*currentdirectionx + hminusvynor[k]*currentdirectiony + hminusvznor[k]*currentdirectionz);
}

double LikelihoodDirectionEventManager::fdirectionnoretro_prototype(const double& costheta) const
{
  if(costheta < 0.75)
    return (1 + prototypea0 * (fmath::expd(prototypeb0 * (costheta - 0.75 )) -1 ) );
  else
    {
      return (1 + prototypea1 * (fmath::expd(prototypeb1 * (costheta - 0.75)) -1 ));
    }
}

double LikelihoodDirectionEventManager::fdirectionnoretro_bydata(const double& costheta) const
{
    if(costheta < 0.75){
    return (1 + bydatanoretroa0 * (fmath::expd(bydatanoretrob0 * (costheta -0.75 )) -1));
  }
  else{
    return(1 + bydatanoretroa1 * (fmath::expd(bydatanoretrob1 * (costheta - 0.75 )) - 1));
  }
}

double LikelihoodDirectionEventManager::fdirectiononretro_prototype(const double& costheta) const
{
  if(-costheta < 0.75){
    return (1 + prototypea0 * (fmath::expd(prototypeb0 * (-costheta - 0.75 )) -1));
  }
  else{
    return(1 + prototypea1 * (fmath::expd(prototypeb1 * (-costheta - 0.75 )) - 1));
  }
}

double LikelihoodDirectionEventManager::fdirectiononretro_bydata(const double& costheta) const
{
  if(costheta < -0.75){
    return (1 + bydataonretroa0 * (fmath::expd(bydataonretrob0 * (costheta +0.75 )) -1));
  }
  else{
    return(1 + bydataonretroa1 * (fmath::expd(bydataonretrob1 * (costheta + 0.75 )) - 1));
  }
}

