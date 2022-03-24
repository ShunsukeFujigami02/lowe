#ifndef ANGLERANGE_HH
#define ANGLERANGE_HH

// ROOT library
#include <TObject.h>

class AngleRange : public TObject
{
public:
  AngleRange(){};
  virtual ~AngleRange(){};
  void Setrange(AngleRange range);
  double GetCosthetamin() const
  {
    return costhetamin;
  }
  void SetCosthetamin(double costheta)
  {
    costhetamin = costheta;
  }
  double GetCosthetawidth() const
  {
    return costhetawidth;
  }
  void SetCosthetawidth(double width)
  {
    costhetawidth = width;
  }
  int GetCosthetaNum() const
  {
    return costhetanum;
  }
  void SetCosthetaNum(int num)
  {
    costhetanum = num;
  }
  double GetPhimin() const
  {
    return phimin;
  }
  void SetPhimin(double min)
  {
    phimin = min;
  }
  double GetPhiwidth() const
  {
    return phiwidth;
  }
  void SetPhiwidth(double width)
  {
    phiwidth = width;
  }
  int GetPhiNum() const
  {
    return phinum;
  }
  void SetPhiNum(int num)
  {
    phinum = num;
  }
  double GetCosthetamax() const
  {
    return (costhetamin + (costhetanum - 1)* costhetawidth);
  }
  double GetPhimax() const 
  {
    return (phimin + (phinum -1 )* phiwidth);
  }
  
  
private:
  double costhetamin;
  double costhetawidth;
  int costhetanum;
  double phimin;
  double phiwidth;
  int phinum;
public:
  ClassDef(AngleRange,1)
};  

#endif
