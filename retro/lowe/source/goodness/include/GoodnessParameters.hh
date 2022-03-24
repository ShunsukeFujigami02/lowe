#ifndef GOODNESSPARAMETERS_HH
#define GOODNESSPARAMETERS_HH

#include "CSearch_range.hh"
#include "EnumManager.hh"

ENUM(GoodnessLoop4VectorType,normal,True);

ENUM(GoodnessFunctionType,normal);

ENUM(OneGoodnessFunctionType,no_retro,on_retro,sum,compare,no_retro_digital,compare_digital,compare_nodigital,compare_nodigital_ver3);

class GoodnessParameters
{
public:
  GoodnessParameters();
  virtual ~GoodnessParameters();
  GoodnessLoop4VectorType::type GetGoodnessLoop4VectorType() const 
  {
    return goodnessloop4vectortype;
  }
  void SetGoodnessLoop4VectorType(GoodnessLoop4VectorType::type type)
  {
    goodnessloop4vectortype = type;
  }
  
  GoodnessFunctionType::type GetGoodnessFunctionType() const {return goodnessfunctiontype;}
  void SetGoodnessFunctionType(GoodnessFunctionType::type type){goodnessfunctiontype = type;}
  OneGoodnessFunctionType::type GetOneGoodnessFunctionType() const {return onegoodnessfunctiontype;}
  void SetOneGoodnessFunctionType(OneGoodnessFunctionType::type type){onegoodnessfunctiontype = type;}
  double Getsigma() const {return sigma;}
  void Setsigma(double sigma_in){sigma = sigma_in;}
  CSearch_range* GetSearch_range() const {return range;}
  void SetSearch_range(CSearch_range* range_in){range = (CSearch_range*)range_in->Clone();}
  double GetReflectivity() const 
  {
    return reflectivity;
  }
  void SetReflectivity(double ref)
  {
    reflectivity = ref;
  }
  
  void Print();
private:
  GoodnessLoop4VectorType::type goodnessloop4vectortype;
  GoodnessFunctionType::type goodnessfunctiontype;
  OneGoodnessFunctionType::type onegoodnessfunctiontype;
  double sigma;
  CSearch_range* range;
  double reflectivity;
};

#endif
