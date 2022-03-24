#ifndef GOODNESSEVENTMANAGER_HH
#define GOODNESSEVENTMANAGER_HH
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "GoodnessEvent.hh"
#include "GoodnessEventAction.hh"
#include "GoodnessParameters.hh"
#include "CSearch_range.hh"
class GoodnessEventManager
{
public:
  GoodnessEventManager();
  virtual ~GoodnessEventManager();
  void SetParameters();
  void ProcessOneEvent(GoodnessEvent* event);
  void Doloop();
  void Doloopin(const int& l);
  void Setdistance();
  void SetGoodnessEventAction(GoodnessEventAction* goodnesseventaction_in)
  {
    goodnesseventaction = goodnesseventaction_in;
  }
  inline double distance_position_pmt(size_t k) const;
  inline double distance_position_retro(size_t k) const;
  inline double tof(const double& hittimeminusoffset_minus_dcrossrv_light_in_water,const size_t& l) const;
  inline double one_goodness_no_retro(const size_t& k,const size_t& l) const;
  inline double one_goodness_compare(const size_t& k,const size_t& l) const;
  double one_goodness_sum(const size_t& k,const size_t& l) const;
  double one_goodness_on_retro(const size_t& k,const size_t& l) const;
  inline double one_goodness_no_retro_digital(const size_t& k,const size_t& l) const;
  inline void one_goodness_compare_digital(const size_t&k,const size_t& l);
  inline double one_goodness_compare_nodigital(const size_t&k,const size_t& l) const;
  inline double one_goodness_compare_nodigital_ver3(const size_t&k,const size_t& l) const;
private:
  GoodnessEventAction* goodnesseventaction = nullptr;
  GoodnessEvent* currentevent = nullptr;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  size_t ncherenkovdigihits;
  CSearch_range* range;
  std::vector<int> hitvec;
  std::vector<double> hittimeminusoffset;
  std::vector<CLHEP::Hep3Vector> pmtposition;
  std::vector<double> hittimeminusoffset_minus_vdistancenoretrocrossrv_lightinwater;
  std::vector<double> hittimeminusoffset_minus_vdistanceonretrocrossrv_lightinwater;
  CLHEP::Hep3Vector currentposition;
  //  double currenttime;
  std::vector<double> currenttime;
  double WCradius;
  double sigma;
  double minusrsigmasquare_half;
  double half_WClength;
  double maxgoodness = 0.;
  double doffset = 1.95775611238980325e+01;
  double reflectivity = 0.3;
  double retroratio = 0.08;
  double log1minusp = 0.;
  double logp = 0.;
  int ndigidir = 0;
  int ndigiref = 0;
  double conretro = 0.;
  CLHEP::HepLorentzVector maxvertex;
  int goodnessloop4vectortype; // 0 : normal
  int onegoodnesstype; // 0 : noretro, 1: compare, 2: sum, 3: onretro, 4: noretro_digital, 5: compare_digital
};

#endif
