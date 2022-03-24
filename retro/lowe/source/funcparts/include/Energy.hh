#ifndef ENERGY_HH
#define ENERGY_HH

#include "function.hh"
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "AnalizeFile.hh"
#include "AnalizeFiledata.hh"
class EnergyFunction : public function
{
public:
  EnergyFunction()
  {
  }
  virtual ~EnergyFunction()
  {
  }
  void SetData(AnalizeFile filein,AnalizeFiledata* datain);
  virtual double returnvalue() = 0;
protected:
  AnalizeFile file;
  AnalizeFiledata* data;
  int type = 0.; // 0: default 1: only NoRetro 2: only OnRetro 3: complex
};

class NeffNoRetro : public EnergyFunction
{
public:
  NeffNoRetro()
  {
  }
  ;
  virtual ~NeffNoRetro()
  {
  }
  ;
  double returnvalue();
};

class NeffOnRetro : public EnergyFunction
{
public:
  NeffOnRetro()
  {
  }
  ;
  virtual ~NeffOnRetro()
  {
  }
  ;
  double returnvalue();
};

#endif
  
