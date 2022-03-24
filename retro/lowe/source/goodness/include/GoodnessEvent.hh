#ifndef GOODNESSEVENT_HH
#define GOODNESSEVENT_HH
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>

class GoodnessEvent
{
public:
  GoodnessEvent();
  GoodnessEvent(int evID);
  virtual ~GoodnessEvent();
  void SetEventID(int i){ eventID = i;}
  int GetEventID() const 
  { return eventID;}
  double Getgoodness() const {return goodness;}
  void Setgoodness(double goodness_in) { goodness = goodness_in;}
  CLHEP::HepLorentzVector Get4Vector() const
  {
    return hvector;
  }
  void Set4Vector(CLHEP::HepLorentzVector hvector_in)
  {
    hvector = hvector_in;
  }
  void SetNcherenkovdigihits(int n)
  {
    ncherenkovdigihits = n;
  }
  
private:
  int eventID;
  double goodness = 0;
  int ncherenkovdigihits;
  CLHEP::HepLorentzVector hvector;
};

#endif
