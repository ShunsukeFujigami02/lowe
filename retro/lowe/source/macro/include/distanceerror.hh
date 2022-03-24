#ifndef DISTANCEERROR_HH
#define DISTANCEERROR_HH

#include <TH1D.h>
#include <iostream>

class distanceerror
{
public:
  distanceerror()
  {
  }
  virtual ~distanceerror()
  {
  }
  void Setd(double din)
  {
    d = din;
    double thetamin = std::atan((sphereradius + PMToffset)/d);
    randcosthetamin = std::cos(thetamin);
  }
  void SetCosTheta(double costheta_in)
  {
    costheta = costheta_in;
  }
  void DrawTH1D(TH1D* h1,int number);
  double GetMean(int number);
private:
  double d = 1000.;
  double costheta = 1.;
  double randcosthetamin = 0.9;
  double sphereradius = 26.921;
  double PMToffset = 8.921;
};

double direcminusdtrue_direct(double d,double cosangle)
{
  double logd = std::log(d);
  double p0,p1,p2 = 0.;
  if(d > 3000.)
    {
      p0 = 1.78735723978606131e+01;
      p1 = -3.56589723310854367e+00;
      p2 = -5.07447157382910063e+00;
    }
  else if(logd > 3.83)
    {	  
      p0 = 54.8411 -15.3876*logd + 2.16874* logd*logd -0.102858*logd*logd*logd;
      p1 = -78.3825 + 31.6236 *logd -4.49083*logd*logd + 0.213352*logd*logd*logd;
      p2 = 115.732 -65.4698 *logd + 13.3604*logd*logd -1.21384*logd*logd*logd + 0.0413508*logd*logd*logd*logd;
    }
  else
    {
      p0 = 54.8411 -15.3876*logd + 2.16874* logd*logd -0.102858*logd*logd*logd;
      p1 = -2.01176e+00*(logd - 3.83) - 1.11533115231416211e+01;
      p2 = 3.29467e+00*(logd - 3.83) + 1.66637782455158678e+00;
    }
  double drecminusdtrue = p0 + p1*cosangle + p2*cosangle*cosangle;
  return drecminusdtrue;
}


#endif
