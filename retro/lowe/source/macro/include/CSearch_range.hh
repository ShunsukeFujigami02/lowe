#ifndef CSEARCH_RANGE_HH
#define CSEARCH_RANGE_HH

// ROOT library
#include <TLorentzVector.h>
#include <TObject.h>

// self-introduced library
#include "C4Number.hh"

class CSearch_range : public TObject
{
  // This class represent the range of 4-dimension grid search. This is composed of minimum value of search range, width value of search, and number of search for each direction.
public:
  CSearch_range(TLorentzVector search_min,TLorentzVector search_width,C4Number search_number);
  CSearch_range(){}
  
  virtual ~CSearch_range(){}
  void Setrange(CSearch_range range_in)
  {
    *this = range_in;
  }
  
  int GetN() const; // Number of grid search.
  double GetXmin() const;
  double GetYmin() const;
  double GetZmin() const;
  double GetTmin() const;
  double GetXwidth() const;
  double GetYwidth() const;
  double GetZwidth() const;
  double GetTwidth() const;
  int GetXNum() const;
  int GetYNum() const;
  int GetZNum() const;
  int GetTNum() const;
  double GetXmax() const;
  double GetYmax() const;
  double GetZmax() const;
  double GetTmax() const;
  double GetXcentral() const; 
  double GetYcentral() const;
  double GetZcentral() const;
  double GetTcentral() const;
  double GetXallwidth() const; // whole range of each direction. max - min
  double GetYallwidth() const;
  double GetZallwidth() const;
  double GetTallwidth() const;
  void Setmin(TLorentzVector search_min_input);
  void Setwidth(TLorentzVector search_width_input);
  void SetNum(C4Number search_number_input);
  TLorentzVector Getmin(){ return search_min;}
  TLorentzVector Getwidth()
  {
    return search_width;
  }
  C4Number GetNum()
  {
    return search_number;
  }
  void Printrange();
private:
  TLorentzVector search_min;
  TLorentzVector search_width;
  C4Number search_number;
public:
  ClassDef(CSearch_range,1)
};
#endif
