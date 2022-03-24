#ifndef PROCESS_HH
#define PROCESS_HH
// c++ STL
#include <vector>
// ROOT
#include <Math/Minimizer.h>

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>
// self
#include "hitinfo.hh"
#include "Reconstructdata.hh"

class Process 
{
public:
  Process(){};
  virtual ~Process(){};
    void Setfitted4Vector(CLHEP::HepLorentzVector vector)
  {
    fitted4Vector = vector;
  }
  CLHEP::HepLorentzVector Getfitted4Vector() const
  {
    return fitted4Vector;
  }
  void SetCurrentlikelihood(double l)
  {
    currentlikelihood = l;
  }
  double GetCurrentlikelihood() const
  {
    return currentlikelihood;
  }
  void SetCurrent3Direction(CLHEP::Hep3Vector vec)
  {
    currentdirection = vec;
  }
  CLHEP::Hep3Vector GetCurrent3Direction()
  {
    return currentdirection;
  }
  void Set3PMTPosition(CLHEP::Hep3Vector vec)
  {
    pmtposition = vec;
  }
  CLHEP::Hep3Vector Get3PMTPosition()
  {
    return pmtposition;
  }
  
  void AddLikelihoodDirection(double l)
  {
    currentlikelihood +=l;
  }
  void SetnumberOfEvent(int n)
  {
    nevents = n;
  }
  int GetnumberOfEvent()
  {
    return nevents;
  }
  void SetMaxlikelihood(double l)
  {
    maxlikelihood = l;
  }
  int GetMaxlikelihood()
  {
    return maxlikelihood;
  }
  void SetMax3Direction(CLHEP::Hep3Vector vector)
  {
    maxdirection = vector;
  }
  CLHEP::Hep3Vector GetMax3Direction()
  {
    return maxdirection;
  }
  void Setgoodness(double g)
  {
    goodness = g;
  }
  double Getgoodness()
  {
    return goodness;
  }
  
  void Setgoodness_onretro(double g)
  {
    goodness_onretro = g;
  }
  double Getgoodness_onretro()
  {
    return goodness_onretro;
  }
  void Setgoodness_noretro(double g)
  {
    goodness_noretro = g;
  }
  double Getgoodness_noretro()
  {
    return goodness_noretro;
  }
  void Sethittype(int t)
  {
    hittype = t;
  }
  int Gethittype()
  {
    return hittype;
  }
  void Sethitnumber(int hitnum)
  {
    currenthitnumber = hitnum;
  }
  int Gethitnumber()
  {
    return currenthitnumber;
  }
  void Setncherenkovdigihits(int n)
  {
    ncherenkovdigihits = n;
  }
  int Getncherenkovdigihits()
  {
    return ncherenkovdigihits;
  }
  std::vector<double> maxonelikelihoodonretro;
  std::vector<double> maxonelikelihoodnoretro;

  ROOT::Math::Minimizer* GetMinimizer()
  {
    return min;
  }
  void SetMinimizer(ROOT::Math::Minimizer* minimizer)
  {
    min = minimizer;
  }
  void SetCurrentEventNumber(int i)
  {
    currentevent = i;
  }
  int GetCurrentEventNumber()
  {
    return currentevent;
  }
  
private:
  CLHEP::HepLorentzVector fitted4Vector;
  CLHEP::Hep3Vector currentdirection;
  CLHEP::Hep3Vector pmtposition;
  double goodness;
  double goodness_onretro;
  double goodness_noretro;
  int hittype;
  double currentlikelihood = -10000000.;
  CLHEP::Hep3Vector maxdirection;
  double maxlikelihood = -10000000.;
  int nevents;
  int currentevent;
  int currenthitnumber;
  int ncherenkovdigihits;
  ROOT::Math::Minimizer* min = nullptr;
};

#endif
