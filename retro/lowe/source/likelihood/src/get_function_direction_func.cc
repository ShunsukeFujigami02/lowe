// c++ STL
#include <vector>
#include <cmath>

// ROOT library
#include <TVector3.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "get_function_direction_func.hh"

double gettheta_i(WCSimRootCherenkovDigiHit* hit,WCSimRootGeom* wcsimrootgeom,TVector3 truevertex,TVector3 truedirection){
  int tubeId = hit->GetTubeId();
  WCSimRootPMT pmt  = wcsimrootgeom->GetPMT(tubeId-1);
  TVector3 pmt_position(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
  TVector3 vminush = pmt_position - truevertex;
  return truedirection.Angle(vminush);
}

void setvtheta_i(std::vector<double> vtheta_i,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,TVector3 truevertex,TVector3 truedirection){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int i = 0; i < (int)vtheta_i.size();i++){
    vtheta_i.pop_back();
  }
  for(int k = 0; k< ncherenkovdigihits;k++){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double theta_i = gettheta_i(hit,wcsimrootgeom,truevertex,truedirection);
    vtheta_i.emplace_back(theta_i);
  }
}

void setvcostheta_i(std::vector<double> vcostheta_i,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,TVector3 truevertex,TVector3 truedirection){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  for(int i = 0; i < (int)vcostheta_i.size();i++){
    vcostheta_i.pop_back();
  }
  for(int k = 0; k< ncherenkovdigihits;k++){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double theta_i = gettheta_i(hit,wcsimrootgeom,truevertex,truedirection);
    vcostheta_i.emplace_back(std::cos(theta_i));
  }
}
