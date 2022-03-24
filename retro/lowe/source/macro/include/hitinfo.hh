#ifndef _HITINFO_HH
#define _HITINFO_HH
// C++
#include <iostream>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"
// self
#include "constants.hh"
class hitinfo
{
public:
  hitinfo()
  {
  }
  virtual ~hitinfo()
  {
  }
  hitinfo& operator=(const hitinfo& info)
  {
    hittime = info.HitTime();
    pmtposition = info.Get3Position();
    pmtdirection = info.Get3Orientation();
    WCradius = info.GetWCradius();
    WClength = info.GetWClength();
    return *this;
  }
  
  void Sethit(WCSimRootCherenkovDigiHit* h,WCSimRootGeom* wcsimrootgeom)
  {
    tubeId = h->GetTubeId();
    hittime = h->GetT();
    static WCSimRootPMT pmt;
    pmt = wcsimrootgeom->GetPMT(tubeId-1);
    pmtposition.setX(pmt.GetPosition(0));
    pmtposition.setY(pmt.GetPosition(1));
    pmtposition.setZ(pmt.GetPosition(2));
    pmtdirection.setX(pmt.GetOrientation(0));
    pmtdirection.setY(pmt.GetOrientation(1));
    pmtdirection.setZ(pmt.GetOrientation(2));
    CylLoc = pmt.GetCylLoc();
    double WCradiustemp = wcsimrootgeom->GetWCCylRadius();
    double WClengthtemp = wcsimrootgeom->GetWCCylLength();
    if(std::abs(WCradiustemp - SKRadius) < 1.)
      {
	WCradius = 1686.;
      }
    else
      {
	WCradius = WCradiustemp;
      }
    
    if(std::abs(WClengthtemp - SKLength) < 1.)
      {
	WClength = 3620.;
      }
    else
      {
	WClength = WClengthtemp;
      }
  }
  CLHEP::Hep3Vector Get3Position() const
  {
    return pmtposition;
  }
  void Set3Position(CLHEP::Hep3Vector position)
  {
    pmtposition = position;
  }
  CLHEP::Hep3Vector Get3Orientation() const
  {
    return pmtdirection;
  }
  double HitTime() const
  {
    return hittime;
  }
  double GetWCradius() const 
  {
    return WCradius;
  }
  double GetWClength() const 
  {
    return WClength;
  }
  double GetCylLoc() const
  {
    return CylLoc;
  }
  void SetWCradius(double r)
  {
    WCradius = r;
  }
  void SetWClength(double l)
  {
    WClength = l;
  }
  int GetTubeId(){
    return tubeId;
  }
private:
  double hittime;
  CLHEP::Hep3Vector pmtposition;
  CLHEP::Hep3Vector pmtdirection;
  double WCradius;
  double WClength;
  int tubeId;
  int CylLoc;
};

#endif
