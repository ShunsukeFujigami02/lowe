#ifndef AFUNCTION_HH
#define AFUNCTION_HH

class afunction : public function
{
public:
  afunction()
  {
  }
  
  virtual ~afunction()
  {
  }
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  virtual double returnvalue() = 0; 
private:
  hitinfo info;
  Reconstructdata data;
};
  
class afuncprototype : public afunction
{
public:
  afuncprototype()
  {
  }
  virtual ~afuncprototype()
  {
  }

  double returnvalue()
  {
    return 1.;
  }
};

#endif  
