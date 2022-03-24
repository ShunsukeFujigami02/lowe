#ifndef GOODNESSCALCULATED_HH
#define GOODNESSCALCULATED_HH
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>

class GoodnessCalculated
{
public:
  GoodnessCalculated():goodness(0.){};
  virtual ~GoodnessCalculated(){};
  double GetGoodness() const { return goodness;}
  void SetGoodness(double goodness_in){ goodness = goodness_in;}
  void AddGoodness(double goodness_in)
  {
    goodness += goodness_in;
  }
  
  CLHEP::HepLorentzVector Get4Vector() const 
  {
    return vector;
  }
  void SetLorentzVector(const CLHEP::HepLorentzVector vertex_in)
  {
    vector = vertex_in;
  }
  
private:
  double goodness = 0.;
  CLHEP::HepLorentzVector vector;
  CLHEP::Hep3Vector pmtposition;
  
};

#endif
