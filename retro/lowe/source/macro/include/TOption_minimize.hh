#ifndef TOPTION_MINIMIZE_HH
#define TOPTION_MINIMIZE_HH

#include <TObject.h>
#include <TLorentzVector.h>

class TOption_minimize : public TObject
{
public:
  TOption_minimize(){};
  virtual ~TOption_minimize(){};
  TLorentzVector stepvec;
  double stepcostheta;
  double stepphi;
  TLorentzVector lowervec;
  double lowercostheta;
  double lowerphi;
  TLorentzVector uppervec;
  double uppercostheta;
  double upperphi;
  int maxfunctioncalls;
  int maxiterations;
  double tolerance;
  void SetOption(TOption_minimize op)
  {
    stepvec = op.stepvec;
    stepcostheta = op.stepcostheta;
    stepphi = op.stepphi;
    lowervec = op.lowervec;
    lowercostheta = op.lowercostheta;
    lowerphi = op.lowerphi;
    uppervec = op.uppervec;
    uppercostheta = op.uppercostheta;
    upperphi = op.upperphi;
    maxfunctioncalls = op.maxfunctioncalls;
    maxiterations = op.maxiterations;
    tolerance = op.tolerance;
  }
  
public:
  ClassDef(TOption_minimize,1)
};

#endif
  
