// c++ STL
#include <iostream>

// ROOT library
#include <TLorentzVector.h>

// self-introduced library
#include "C4Number.hh"
#include "CSearch_range.hh"

ClassImp(CSearch_range)

CSearch_range::CSearch_range(TLorentzVector search_min,TLorentzVector search_width,C4Number search_number)
  :search_min(search_min),search_width(search_width),search_number(search_number)
{
  if((search_width.X() <= 0) || (search_width.Y() <= 0) || (search_width.Z() <= 0) || (search_width.T() <= 0))
    {
      std::cout << "invalid search width!" << std::endl;
      throw "CSearch_range::CSearch_range(TLorentzVector search_min,TLorentzVector search_width,C4Number search_number)";
    }
}

int CSearch_range::GetN() const
{
  return GetXNum() * GetYNum() * GetZNum() * GetTNum();
}

double CSearch_range::GetXmin() const
{
  return search_min.X();
}

double CSearch_range::GetYmin() const
{
  return search_min.Y();
}

double CSearch_range::GetZmin() const
{
  return search_min.Z();
}

double CSearch_range::GetTmin() const
{
  return search_min.T();
}

double CSearch_range::GetXwidth() const
{
  return search_width.X();
}

double CSearch_range::GetYwidth() const
{
  return search_width.Y();
}

double CSearch_range::GetZwidth() const
{
  return search_width.Z();
}

double CSearch_range::GetTwidth() const
{
  return search_width.T();
}

int CSearch_range::GetXNum() const
{
  return search_number.GetX();
}

int CSearch_range::GetYNum() const
{
  return search_number.GetY();
}

int CSearch_range::GetZNum() const
{
  return search_number.GetZ();
} 

int CSearch_range::GetTNum() const
{
  return search_number.GetT();
}

double CSearch_range::GetXmax() const
{
  return GetXmin() + (GetXNum()-1)*GetXwidth();
}

double CSearch_range::GetYmax() const
{
  return GetYmin() + (GetYNum()-1)*GetYwidth();
}

double CSearch_range::GetZmax() const
{
  return GetZmin() + (GetZNum()-1)*GetZwidth();
}

double CSearch_range::GetTmax() const
{
  return GetTmin() + (GetTNum()-1)*GetTwidth();
}

double CSearch_range::GetXcentral() const
{
  return (GetXmax() + GetXmin())/2.;
}

double CSearch_range::GetYcentral() const
{
  return (GetYmax() + GetYmin())/2.;
}

double CSearch_range::GetZcentral() const
{
  return (GetZmax() + GetZmin())/2.;
}

double CSearch_range::GetTcentral() const
{
  return (GetTmax() + GetTmin())/2.;
}

double CSearch_range::GetXallwidth() const
{
  return GetXmax() - GetXmin();
}

double CSearch_range::GetYallwidth() const
{
  return GetYmax() - GetYmin();
}

double CSearch_range::GetZallwidth() const
{
  return GetZmax() - GetZmin();
}

double CSearch_range::GetTallwidth() const
{
  return GetTmax() - GetTmin();
}

void CSearch_range::Setmin(TLorentzVector search_min_input)
{
  search_min = search_min_input;
}

void CSearch_range::Setwidth(TLorentzVector search_width_input)
{
  if((search_width_input.X() <= 0) || (search_width_input.Y() <= 0) || (search_width_input.Z() <= 0) || (search_width_input.T() <= 0)){
    std::cout << "invalid search width!";
    throw "CSearch_range::Setwidth(TLorentzVector search_width_input)";
  }
  else{
    search_width = search_width_input;
  }
}

void CSearch_range::SetNum(C4Number search_number_input)
{
  search_number = search_number_input;
}

void CSearch_range::Printrange()
{
  std::cout << "search min:";
  search_min.Print();
  std::cout << "search width:";
  search_width.Print();
  std::cout << "search_number:";
  search_number.Printnumber();
}

