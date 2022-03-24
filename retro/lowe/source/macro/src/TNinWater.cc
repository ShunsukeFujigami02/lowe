#include "TNinWater.hh"
#include <cmath>

ClassImp(TNinWater)

double TNinWater::nlambda(double lambda)
{
  return std::sqrt(a1/(lambda*lambda - lambdaa2) + a2 + a3*lambda*lambda + a4*lambda*lambda*lambda + a5*lambda*lambda* lambda* lambda* lambda* lambda);
}

double TNinWater::dndlambda(double lambda)
{
  return (nlambda(lambda + dlambda) - nlambda(lambda))/dlambda;
}

double TNinWater::returnvalue(double lambda)
{
  return nlambda(lambda) - lambda* dndlambda(lambda);
}
