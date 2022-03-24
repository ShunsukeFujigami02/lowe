#ifndef ENERGY_HH
#define ENERGY_HH

#include "function.hh"
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "AnalizeFile.hh"
#include "AnalizeFiledata.hh"
class EnergyFunction
{
public:
  EnergyFunction()
  {
  }
  virtual ~EnergyFunction()
  {
  }
  void SetData(AnalizeFile filein,AnalizeFiledata* datain);
  virtual double returnvalue(std::vector<double>& doubleval) = 0; // doubleval : 0 Neffdirect 1 Neffreflect
  void SetN(int nin){n = nin;}
  void SetLambda(double lambda){
    lambdarun = lambda;
  }
  void SetLambdaRetro(double lambda){
    lambdarunRetro = lambda;
  }
  double GetLambda(double reflectivity);
protected:
  AnalizeFile file;
  AnalizeFiledata* data;
public:
  int type = 0; // 0: default 1: only NoRetro 2: only OnRetro 3: complex
  int n = 0;
  double lambdarun = 10000.;
  double lambdarunRetro = 10000.;
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
  double returnvalue(std::vector<double>& doubleval);
};

class NeffNoRetroTrue : public EnergyFunction
{
public:
  NeffNoRetroTrue()
  {
  }
  ;
  virtual ~NeffNoRetroTrue()
  {
  }
  ;
  double returnvalue(std::vector<double>& doubleval);
};

/*class NeffOnRetro : public EnergyFunction
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
  double returnvalue(std::vector<int>& intval,std::vector<double>& doubleval);
};

class NeffOnRetroaddretrotail : public EnergyFunction
{
public:
  NeffOnRetroaddretrotail()
  {
  }
  ;
  virtual ~NeffOnRetroaddretrotail()
  {
  }
  ;
  double returnvalue(std::vector<int>& intval,std::vector<double>& doubleval);
};
*/
class NeffOnRetroFinal : public EnergyFunction
{
public:
  NeffOnRetroFinal()
  {};
  virtual ~NeffOnRetroFinal(){};
  double returnvalue(std::vector<double>& doubleval);
};

class NeffOnRetroFinalver2 : public EnergyFunction
{
public:
  NeffOnRetroFinalver2()
  {};
  virtual ~NeffOnRetroFinalver2(){};
  double returnvalue(std::vector<double>& doubleval);
};

class NeffOnRetroFinalTrue : public EnergyFunction
{
public:
  NeffOnRetroFinalTrue()
  {};
  virtual ~NeffOnRetroFinalTrue(){};
  double returnvalue(std::vector<double>& doubleval);
};

class NeffOnRetroFinalver2True : public EnergyFunction
{
public:
  NeffOnRetroFinalver2True()
  {};
  virtual ~NeffOnRetroFinalver2True(){};
  double returnvalue(std::vector<double>& doubleval);
};

class NeffOnRetroFinalver3True : public EnergyFunction
{
public:
  NeffOnRetroFinalver3True()
  {};
  virtual ~NeffOnRetroFinalver3True(){};
  double returnvalue(std::vector<double>& doubleval);
};

class NeffOnRetroFinalver3 : public EnergyFunction
{
public:
  NeffOnRetroFinalver3()
  {};
  virtual ~NeffOnRetroFinalver3(){};
  double returnvalue(std::vector<double>& doubleval);
};


#endif
  
