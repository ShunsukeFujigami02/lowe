// c++ STL
#include <cmath>

// self-introduced library
#include "GoodnessManager.hh"
#include "OneGoodnessCalculateManager.hh"
#include "OneGoodnessCalculated.hh"

OneGoodnessCalculateManager::OneGoodnessCalculateManager()
{
}

OneGoodnessCalculateManager::~OneGoodnessCalculateManager()
{
  delete onegoodnesscalculateaction;
}

void OneGoodnessCalculateManager::SetParameters()
{
  onegoodnessfunctiontype = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetOneGoodnessFunctionType();
  sigma = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->Getsigma();
  double WCradiustemp = GoodnessManager::GetGoodnessManager()->GetWCSimRootGeom()->GetWCCylRadius();
  double WClengthtemp = GoodnessManager::GetGoodnessManager()->GetWCSimRootGeom()->GetWCCylLength();
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
}

void OneGoodnessCalculateManager::DoProcess(OneGoodnessCalculated& onegoodnesscalculated_in)
{
  SetOneGoodnessCalculated(onegoodnesscalculated_in);
  onegoodnesscalculated.SetWCradius(WCradius);
  onegoodnesscalculated.SetWClength(WClength);
  onegoodnesscalculateaction->BeginOfAction();
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::no_retro){
    one_goodness_no_retro();
  }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::on_retro){
    one_goodness_on_retro();
  }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::sum){
    one_goodness_sum();
  }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare){
    one_goodness_compare();
  }
  onegoodnesscalculateaction->EndOfAction();
  onegoodnesscalculated_in = onegoodnesscalculated;
}

void OneGoodnessCalculateManager::one_goodness_on_retro()
{
  double tof_on_retro = onegoodnesscalculated.tof_on_retro();
  double goodness = std::exp(-0.5*std::pow((tof_on_retro/sigma),2.0));
  onegoodnesscalculated.SetOneGoodness(goodness);
}
  
void OneGoodnessCalculateManager::one_goodness_no_retro()
{
  double tof_no_retro = onegoodnesscalculated.tof_no_retro();
  double goodness = std::exp(-0.5*std::pow((tof_no_retro/sigma),2.0));
  onegoodnesscalculated.SetOneGoodness(goodness);
}

void OneGoodnessCalculateManager::one_goodness_sum()
{
  double tof_no_retro = onegoodnesscalculated.tof_no_retro();
  double tof_on_retro = onegoodnesscalculated.tof_on_retro();
  double goodness = std::exp(-0.5*std::pow((tof_no_retro/sigma),2.0));
  goodness += std::exp(-0.5*std::pow((tof_on_retro/sigma),2.0));
  onegoodnesscalculated.SetOneGoodness(goodness);
}

void OneGoodnessCalculateManager::one_goodness_compare()
{
  double distance_position_pmt = onegoodnesscalculated.distance_position_pmt();
  double distance_position_retro = onegoodnesscalculated.distance_position_retro();
  double distance_fly_retro = distance_position_pmt + 2* distance_position_retro;
  double tof_no_retro = onegoodnesscalculated.tof(distance_position_pmt);
  double tof_on_retro = onegoodnesscalculated.tof(distance_fly_retro);
  double goodness_no_retro = std::exp(-0.5*std::pow((tof_no_retro/sigma),2.0));
  double goodness_on_retro = std::exp(-0.5*std::pow((tof_on_retro/sigma),2.0));
  if( goodness_no_retro > goodness_on_retro){
    onegoodnesscalculated.SetOneGoodness(goodness_no_retro);
  }
  else{
    onegoodnesscalculated.SetOneGoodness(goodness_on_retro);
  }
}
      
  
