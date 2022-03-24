#ifndef ONEGOODNESSCALCULATED_HH
#define ONEGOODNESSCALCULATED_HH

// geant4-library
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>

class OneGoodnessCalculated
{
public:
  OneGoodnessCalculated(){};
  virtual ~OneGoodnessCalculated(){};
  void SetHitTime(double t){ hittime = t;}
  double GetHitTime() const { return hittime;}
  void SetPMTPosition(const CLHEP::Hep3Vector& position){ pmtposition = position;}
  CLHEP::Hep3Vector GetPMTPosition() const { return pmtposition;}
  void SetVertex(const CLHEP::HepLorentzVector& vertex_in){ vertex = vertex_in;}
  CLHEP::HepLorentzVector GetVertex() const { return vertex;}
  double GetOneGoodness() const { return onegoodness;}
  void SetOneGoodness(double goodness){ onegoodness = goodness;}
  double GetWCradius() const { return WCradius; }
  void SetWCradius(double WCradius_in)
  {
    WCradius = WCradius_in;
  }

  double GetWClength() const 
  {
    return WClength;
  }

  void SetWClength(double WClength_in)
  {
    WClength = WClength_in;
  }
  
  double distance_position_pmt() const ;
  double distance_position_retro() const;
  double distance_fly_retro() const;
  double tof(double distance) const;
  double tof_no_retro() const ;
  double tof_on_retro() const ;
  
private:
  CLHEP::Hep3Vector pmtposition;
  double hittime;
  CLHEP::HepLorentzVector vertex;
  double onegoodness = 0;
  double WCradius;
  double WClength;
  double doffset = 1.95775611238980325e+01;
};

#endif
