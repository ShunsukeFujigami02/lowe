#include "distanceerror.hh"
#include "constants.hh"
#include <random>
#include <cmath>
#include <CLHEP/Vector/ThreeVector.h>

void distanceerror::DrawTH1D(TH1D* h1,int number)
{
  double pmtX = 0.;
  double pmtY = 0.;
  double pmtZ = d;
  CLHEP::Hep3Vector pmtpos(pmtX,pmtY,pmtZ);
  double SphereMoveX = -PMToffset*std::sqrt(1-costheta*costheta);
  double SphereMoveY = 0.;
  double SphereMoveZ = PMToffset*costheta;
  CLHEP::Hep3Vector movevector(SphereMoveX,SphereMoveY,SphereMoveZ);
  CLHEP::Hep3Vector SphereCenter = pmtpos + movevector;
  double SphereCenterX = SphereCenter.x();
  double SphereCenterY = SphereCenter.y();
  double SphereCenterZ = SphereCenter.z();
  std::random_device rndcostheta;
  std::mt19937 mtcostheta(rndcostheta());
  std::uniform_real_distribution<> randcostheta(randcosthetamin,1.);
  std::random_device rndphi;
  std::mt19937 mtphi(rndphi());
  std::uniform_real_distribution<> randphi(0.,2*PI);
  for(int i = 0;i < number;i++)
    {
      double randcosthetavalue = randcostheta(mtcostheta);
      double randphivalue = randphi(mtphi);
      double directionX = std::sqrt(1-randcosthetavalue*randcosthetavalue)*std::cos(randphivalue);
      double directionY = std::sqrt(1-randcosthetavalue*randcosthetavalue)*std::sin(randphivalue);
      double directionZ = randcosthetavalue;
      CLHEP::Hep3Vector direction(directionX,directionY,directionZ);
      double a = directionX*directionX + directionY*directionY + directionZ*directionZ;
      double b = directionX*SphereCenterX + directionY*SphereCenterY + directionZ*SphereCenterZ;
      double c = SphereCenterX*SphereCenterX + SphereCenterY*SphereCenterY + SphereCenterZ*SphereCenterZ -sphereradius*sphereradius ;
      if((b*b - a*c) < 0.)
	continue;
      double tminus = (b - std::sqrt(b*b - a*c))/a;
      CLHEP::Hep3Vector intersectionminus(directionX*tminus,directionY*tminus,directionZ*tminus);
      CLHEP::Hep3Vector intersectiondirectionminus = intersectionminus - SphereCenter;
      double cosangle = intersectiondirectionminus.cosTheta(-movevector);
      if(cosangle < 0.)
	continue;
      double distance = intersectionminus.mag();
      h1->Fill(d - distance);
    }
}

double distanceerror::GetMean(int number)
{
  std::vector<double> vecvalue;
  double pmtX = 0.;
  double pmtY = 0.;
  double pmtZ = d;
  CLHEP::Hep3Vector pmtpos(pmtX,pmtY,pmtZ);
  double SphereMoveX = -PMToffset*std::sqrt(1-costheta*costheta);
  double SphereMoveY = 0.;
  double SphereMoveZ = PMToffset*costheta;
  CLHEP::Hep3Vector movevector(SphereMoveX,SphereMoveY,SphereMoveZ);
  CLHEP::Hep3Vector SphereCenter = pmtpos + movevector;
  double SphereCenterX = SphereCenter.x();
  double SphereCenterY = SphereCenter.y();
  double SphereCenterZ = SphereCenter.z();
  std::random_device rndcostheta;
  std::mt19937 mtcostheta(rndcostheta());
  std::uniform_real_distribution<> randcostheta(randcosthetamin,1.);
  std::random_device rndphi;
  std::mt19937 mtphi(rndphi());
  std::uniform_real_distribution<> randphi(0.,2*PI);
  for(int i = 0;i < number;i++)
    {
      double randcosthetavalue = randcostheta(mtcostheta);
      double randphivalue = randphi(mtphi);
      double directionX = std::sqrt(1-randcosthetavalue*randcosthetavalue)*std::cos(randphivalue);
      double directionY = std::sqrt(1-randcosthetavalue*randcosthetavalue)*std::sin(randphivalue);
      double directionZ = randcosthetavalue;
      CLHEP::Hep3Vector direction(directionX,directionY,directionZ);
      double a = directionX*directionX + directionY*directionY + directionZ*directionZ;
      double b = directionX*SphereCenterX + directionY*SphereCenterY + directionZ*SphereCenterZ;
      double c = SphereCenterX*SphereCenterX + SphereCenterY*SphereCenterY + SphereCenterZ*SphereCenterZ -sphereradius*sphereradius ;
      if((b*b - a*c) < 0.)
	continue;
      double tminus = (b - std::sqrt(b*b - a*c))/a;
      CLHEP::Hep3Vector intersectionminus(directionX*tminus,directionY*tminus,directionZ*tminus);
      CLHEP::Hep3Vector intersectiondirectionminus = intersectionminus - SphereCenter;
      double cosangle = intersectiondirectionminus.cosTheta(-movevector);
      if(cosangle < 0.)
	continue;
      double distance = intersectionminus.mag();
      vecvalue.emplace_back(d - distance);
    }
  double sum = 0.;
  double c = 0.;
  for(auto iter = vecvalue.begin();iter != vecvalue.end(); iter++)
    {
      double y = (*iter) - c;
      double t = sum + y;
      c = (t - sum) - y;
      sum = t;
    }
  return sum/vecvalue.size();
}

      
      
  
  
