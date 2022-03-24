#ifndef TNINWATER_HH
#define TNINWATER_HH

#include <TObject.h>

class TNinWater : public TObject
{
public:
  TNinWater()
  {
  };
  virtual ~TNinWater()
  {
  };
  double nlambda(double lambda);
  double dndlambda(double lambda);
  double returnvalue(double lambda);
  
private:
  double lambdaa2 = 0.018085;
  double a1 = 5.7473534e-3;
  double a2 = 1.769238;
  double a3 = -2.797222e-2;
  double a4 = 8.715348e-3;
  double a5 = -1.413942e-3;
  double dlambda = 0.00001;
public:
  ClassDef(TNinWater,1)
};

#endif  
