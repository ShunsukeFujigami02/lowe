#include "AngleRange.hh"

ClassImp(AngleRange)

void AngleRange::Setrange(AngleRange range)
{
  SetCosthetamin(range.GetCosthetamin());
  SetCosthetawidth(range.GetCosthetawidth());
  SetCosthetaNum(range.GetCosthetaNum());
  SetPhimin(range.GetPhimin());
  SetPhiwidth(range.GetPhiwidth());
  SetPhiNum(range.GetPhiNum());
}

