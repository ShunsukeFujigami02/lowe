#ifndef BIASERROR_HH
#define BIASERROR_HH

#include <TObject.h>

class BiasError : public TObject
{
public:
  BiasError(){}
  virtual ~BiasError()
  {
  }
  
  double bias;
  double biaserror;
  double error;
  double errorerror;
  ClassDef(BiasError,1)
};

#endif
