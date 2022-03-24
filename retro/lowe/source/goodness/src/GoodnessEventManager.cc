// c++ STL
#include <math.h>
// fmath
#include "fmath.hpp"
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "GoodnessEventManager.hh"
#include "GoodnessEvent.hh"
#include "GoodnessManager.hh"
#include "constants.hh"

GoodnessEventManager::GoodnessEventManager(){
  
}

GoodnessEventManager::~GoodnessEventManager()
{
  delete goodnesseventaction;
}

void GoodnessEventManager::SetParameters()
{
  range = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetSearch_range();
  GoodnessLoop4VectorType::type  goodnessloop4vectortypevar = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetGoodnessLoop4VectorType();
  if(goodnessloop4vectortypevar == GoodnessLoop4VectorType::normal)
    goodnessloop4vectortype = 0;
  OneGoodnessFunctionType::type onegoodnessfunctiontypepar = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetOneGoodnessFunctionType();
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::no_retro)
    onegoodnesstype = 0;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::compare)
    onegoodnesstype = 1;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::sum)
    onegoodnesstype = 2;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::on_retro)
    onegoodnesstype = 3;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::no_retro_digital)
    onegoodnesstype = 4;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::compare_digital)
    onegoodnesstype = 5;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::compare_nodigital)
    onegoodnesstype = 6;
  if(onegoodnessfunctiontypepar == OneGoodnessFunctionType::compare_nodigital_ver3)
    onegoodnesstype = 7;
  wcsimrootgeom = GoodnessManager::GetGoodnessManager()->GetWCSimRootGeom();
  double WClengthtemp = wcsimrootgeom->GetWCCylLength();
  double WCradiustemp = wcsimrootgeom->GetWCCylRadius();
  double WClength = 0.;
  if(std::abs(WCradiustemp - SKRadius) < 1.)
    {
      WCradius = 1686.;
    }
  else
    {
      WCradius = WCradiustemp;
    }
  
  if(std::abs(WClengthtemp - SKLength) < 1.)
    {
      WClength = 3620.;
    }
  else
    {
      WClength = WClengthtemp;
    }
  half_WClength = WClength/2.;
  sigma = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->Getsigma();
  double rsigma = 1./sigma;
  minusrsigmasquare_half = -0.5*rsigma*rsigma;
  reflectivity = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetReflectivity();
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  log1minusp = std::log(1 - retroratio);
  logp = std::log(retroratio);
  conretro = 0.74265 + 2.64586* reflectivity - 1.01048 * reflectivity * reflectivity;
}

void GoodnessEventManager::ProcessOneEvent(GoodnessEvent* event)
{
  currentevent = event;
  wcsimroottrigger = GoodnessManager::GetGoodnessManager()->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = (size_t)wcsimroottrigger->GetNcherenkovdigihits();
  pmtposition = std::vector<CLHEP::Hep3Vector>(ncherenkovdigihits);
  hittimeminusoffset = std::vector<double>(ncherenkovdigihits);
  hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater = std::vector<double>(ncherenkovdigihits);
  hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater = std::vector<double>(ncherenkovdigihits);
  for(int k = 0;k < (int)ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      double time = hit->GetT();
      hittimeminusoffset[k] = time - offset;
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt;
      pmt = wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      CLHEP::Hep3Vector pmt_position(pmtX,pmtY,pmtZ);
      pmtposition[k] = pmt_position;
    }
  currenttime = std::vector<double>(range->GetTNum());
  double t = range->GetTmin();
  for(int l = 0;l < range->GetTNum();++l, t+= range->GetTwidth())
    {
      currenttime[l] = t;
    }
  goodnesseventaction->BeginOfEventAction();
  if(goodnessloop4vectortype == 0)
    {
      Doloop();
    }
  currentevent->Setgoodness(maxgoodness);
  currentevent->Set4Vector(maxvertex);
  maxgoodness = 0.;
  goodnesseventaction->EndOfEventAction(currentevent);
}

void GoodnessEventManager::Doloop()
{
  double x = range->GetXmin();
  unsigned int tnum = range->GetTNum();
  for( int i = 0; i < range->GetXNum() ; ++i , x += range->GetXwidth() )
    {
      double y = range->GetYmin();
      for( int j = 0 ; j < range->GetYNum() ; ++j , y += range->GetYwidth() )
	{
	  double z = range->GetZmin();
	  for(int k = 0; k < range->GetZNum() ; ++k , z += range->GetZwidth() )
	    {
	      currentposition.set(x,y,z);
	      Setdistance();
	      for(size_t l = 0; l != tnum ; ++l)
		{
		  Doloopin(l);
		}
	    }
	}
    }
}

void GoodnessEventManager::Setdistance()
{
  for(size_t k = 0;k != ncherenkovdigihits;k++)
    {
      double d_position_pmt = distance_position_pmt(k);
      double d_position_retro = distance_position_retro(k);
      double d_fly_retro = d_position_pmt + 2* d_position_retro;
      hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] = hittimeminusoffset[k] - (d_position_pmt-doffset)*rv_light_in_water;
      hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k] = hittimeminusoffset[k] - (d_fly_retro-doffset)*rv_light_in_water;;
    }
}


void GoodnessEventManager::Doloopin(const int& l)
{
  double goodness = 0;
  if(onegoodnesstype == 1)
    {
      for(size_t k = 0; k != ncherenkovdigihits; k++)
	{
	  goodness += one_goodness_compare(k,l);
	}
    }
  else if(onegoodnesstype == 0)
    {
      for(size_t k = 0; k != ncherenkovdigihits; k++)
	{
	  goodness += one_goodness_no_retro(k,l);
	}
    }
  else if(onegoodnesstype == 2)
    {
      for(size_t k = 0; k != ncherenkovdigihits; k++)
	{
	  goodness += one_goodness_sum(k,l);
	}
    }
  else if(onegoodnesstype == 3)
    {
      for(size_t k = 0; k != ncherenkovdigihits; k++)
	{
	  goodness += one_goodness_on_retro(k,l);
	}
    }
  else if(onegoodnesstype == 4)
    {
      for(size_t k = 0; k != ncherenkovdigihits;k++)
	{
	  goodness += one_goodness_no_retro_digital(k,l);
	}
    }
  else if(onegoodnesstype == 5)
    {
      ndigidir = 0;
      ndigiref = 0;
      for(size_t k = 0; k != ncherenkovdigihits;k++)
	{
	  one_goodness_compare_digital(k,l);
	}
      goodness = 4.05643*ndigidir +  conretro*ndigiref;
    }
  else if(onegoodnesstype == 6)
    {
      for(size_t k = 0; k != ncherenkovdigihits;k++)
	{
	  goodness += one_goodness_compare_nodigital(k,l);
	}
    }
  else if(onegoodnesstype == 7)
    {
      for(size_t k = 0;k != ncherenkovdigihits;k++)
	{
	  goodness += one_goodness_compare_nodigital_ver3(k,l);
	}
    }
  else
    {
      std::cout << "invalid one goodness type!" << std::endl;
      std::cout << "type number is " << onegoodnesstype << std::endl;
      throw "void GoodnessEventManager::Doloopin()";
    }
  if(maxgoodness < goodness)
    {
      maxgoodness = goodness;
      maxvertex.set(currentposition,currenttime[l]);
    }
}

double GoodnessEventManager::distance_position_pmt(size_t k) const
{
  CLHEP::Hep3Vector position_pmt = currentposition - pmtposition[k];
  double d1 = std::sqrt(position_pmt*position_pmt);
  return d1;
}

double GoodnessEventManager::distance_position_retro(size_t k) const
{
  CLHEP::Hep3Vector pmt = pmtposition[k];
  double positionX = currentposition.x();
  double positionY = currentposition.y();
  double positionZ = currentposition.z();
  double pmtX = pmt.x();
  double pmtY = pmt.y();
  double pmtZ = pmt.z();
  double a = (pmtX-positionX)*(pmtX-positionX)+(pmtY-positionY)*(pmtY-positionY);
  double b = positionX*(positionX-pmtX)+positionY*(positionY-pmtY);
  double c = positionX*positionX+positionY*positionY-WCradius*WCradius;
  double t;
  if(a != 0){
    t = (b-sqrt(b*b-a*c))/a;
  }
  else{
    t = -c/(2*b);
  }
  double z = positionZ + (pmtZ - positionZ)*t;
  if(-half_WClength < z && half_WClength > z){

}
  else if(z > half_WClength){
    t = (half_WClength - positionZ)/(pmtZ-positionZ);
    z = half_WClength;
  }
  else{
    t = (-half_WClength - positionZ)/(pmtZ-positionZ);
    z = - half_WClength;
  }
  double x = positionX + (pmtX-positionX)*t;
  double y = positionY + (pmtY-positionY)*t;
  double d2 = std::sqrt((positionX-x)*(positionX-x)+(positionY-y)*(positionY-y)+(positionZ-z)*(positionZ-z));
  return d2;
}

double GoodnessEventManager::tof(const double& hittimeminusoffset_minus_dcrossrv_light_in_water,const size_t& l) const
{
  double tof = hittimeminusoffset_minus_dcrossrv_light_in_water - currenttime[l];
  return tof;
}


double GoodnessEventManager::one_goodness_no_retro(const size_t& k,const size_t& l) const
{
  double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
  double tof_noretrosquare = tof_noretro*tof_noretro;
  double goodness = fmath::expd(minusrsigmasquare_half*tof_noretrosquare);
  return goodness;
}

double GoodnessEventManager::one_goodness_compare(const size_t& k,const size_t& l) const 
{
  double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
  double tof_onretro = hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k] - currenttime[l];
  if(std::abs(tof_noretro) < std::abs(tof_onretro))
    {
      double tof_noretrosquare = tof_noretro*tof_noretro;
      double goodnessnoretro = fmath::expd(minusrsigmasquare_half*tof_noretrosquare);
      return goodnessnoretro;
    }
  double tof_onretrosquare = tof_onretro*tof_onretro;
  double goodnessonretro = fmath::expd(minusrsigmasquare_half*tof_onretrosquare);
  return goodnessonretro;
}

double GoodnessEventManager::one_goodness_sum(const size_t& k,const size_t& l) const
{
  double tof_noretro = tof(hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k],l);
  double goodnessnoretro = fmath::expd(minusrsigmasquare_half*tof_noretro*tof_noretro);
  double tof_onretro = tof(hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k],l);
  double goodnessonretro = fmath::expd(minusrsigmasquare_half*tof_onretro*tof_onretro);
  return goodnessonretro + goodnessnoretro;
}

double GoodnessEventManager::one_goodness_on_retro(const size_t& k,const size_t& l) const
{
  double tof_onretro = tof(hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k],l);
  double goodnessonretro = fmath::expd(minusrsigmasquare_half*tof_onretro*tof_onretro);
  return goodnessonretro;
}

double GoodnessEventManager::one_goodness_no_retro_digital(const size_t&k,const size_t& l) const
{
  double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
  if(std::abs(tof_noretro) < sigma)
    return 1.;
  return 0.;
}

double GoodnessEventManager::one_goodness_compare_nodigital(const size_t&k,const size_t& l) const
{
  double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
  double goodnessnoretro = log1minusp + 4.*fmath::expd(minusrsigmasquare_half*tof_noretro*tof_noretro);
  double tof_onretro = hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k] - currenttime[l];
  double goodnessonretro = logp + 4.*fmath::expd(minusrsigmasquare_half*tof_onretro*tof_onretro);
  if(goodnessnoretro > goodnessonretro)
    return goodnessnoretro;
  return goodnessonretro;
}

double GoodnessEventManager::one_goodness_compare_nodigital_ver3(const size_t&k,const size_t& l) const
{
  double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
  double goodnessnoretro = 4.05643 *fmath::expd(minusrsigmasquare_half*tof_noretro*tof_noretro);
  double tof_onretro = hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k] - currenttime[l];
  if(std::abs(tof_noretro) < std::abs(tof_onretro)){
    return goodnessnoretro;
  }
  double goodnessonretro = conretro*fmath::expd(minusrsigmasquare_half*tof_onretro*tof_onretro);
  if(goodnessnoretro > goodnessonretro)
    return goodnessnoretro;
  return goodnessonretro;
}
  

 void GoodnessEventManager::one_goodness_compare_digital(const size_t&k,const size_t& l)
 {
   double tof_noretro = hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater[k] - currenttime[l];
   if(std::abs(tof_noretro) < sigma)
     {
       ndigidir++;
       return;
     }
   double tof_onretro = hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater[k] - currenttime[l];
   if(std::abs(tof_onretro) < sigma)
     {
       ndigiref++;
       return;
     }
   return;
 }
 
