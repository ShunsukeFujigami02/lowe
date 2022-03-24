#ifndef TRECONSTRUCTDATA_HH
#define TRECONSTRUCTDATA_HH
// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TLorentzVector.h>
#include <TVector3.h>

class TReconstructhit;


class TReconstructdata : public TObject
{
public:
  TReconstructdata();
  virtual ~TReconstructdata();
  TLorentzVector Get4Vector()
  {
    return vector;
  }
  void Set4Vector(TLorentzVector vec)
  {
    vector = vec;
  }
  
  TVector3 Get3Position()
  {
    return vector.Vect();
  }
  TVector3 Getdirection()
  {
    return direction;
  }
  void Setdirection(TVector3 vec)
  {
    direction = vec;
  }
  
  double Getenergy()
  {
    return energy;
  }
  void Setgoodness(double g)
  {
    goodness = g;
  }
  double Getgoodness()
  {
    return goodness;
  }
  void Setlikelihood(double l)
  {
    likelihood = l;
  }
  double Getlikelihood()
  {
    return likelihood;
  }
  void Setlikelihoodonretro(double l)
  {
    likelihoodonretro = l;
  }
  double Getlikelihoodonretro()
  {
    return likelihoodonretro;
  }
  void Setlikelihoodnoretro(double l)
  {
    likelihoodnoretro = l;
  }
  double Getlikelihoodnoretro()
  {
    return likelihoodnoretro;
  }
  
  void addhit(int hittype=0);
  TReconstructhit& Gethit(int i);
  std::vector<TReconstructhit>& Getvhit()
  {
    return fhit;
  }
  
  void Setdata(TReconstructdata data);
protected:
  TLorentzVector vector;
  TVector3 direction;
  double energy;
  double goodness;
  double likelihood;
  double likelihoodonretro;
  double likelihoodnoretro;
  std::vector<TReconstructhit> fhit;
public:
  ClassDef(TReconstructdata,2)
};

class TReconstructdata_minimize
{
public:
  TReconstructdata_minimize()
  {
  }
  virtual ~TReconstructdata_minimize()
  {
  }
  void SetNParameters(int n)
  {
    nparameter = n;
  }

  int GetNParameters()
  {
    return nparameter;
  }
  void SetParameters(const double* s)
  {
    for(int i = 0;i < nparameter;i++)
      {
	parameters.push_back(s[i]);
      }
  }

  double GetParameter(int num)
  {
    return parameters.at(num);
  }
  
  void Setstatus(int s)
  {
    status = s;
  }
  int Getstatus() const
  {
    return status;
  }
  void Setncalls(int n)
  {
    ncalls = n;
  }
  int Getncalls() const
  {
    return ncalls;
  }
  void SetnIterations(int n)
  {
    nIterations = n;
  }
  int GetnIterations()
  {
    return nIterations;
  }
  void Setdata(TReconstructdata_minimize data);
  
private:
  int nparameter;
  std::vector<double> parameters;
  int status;
  int ncalls;
  int nIterations;
public:
  ClassDef(TReconstructdata_minimize,1)
};


class TReconstructhit : public TObject
{
public:
  TReconstructhit()
  {
  }
  TReconstructhit(int hittype)
    :hittype(hittype)
  {
  }
  
  virtual ~TReconstructhit(){}
  int Gethittype()
  {
    return hittype;
  }
  
  void Setonegoodnessnoretro(double g)
  {
    onegoodnessnoretro = g;
  }
  double Getonegoodnessnoretro()
  {
    return onegoodnessnoretro;
  }
  void Setonegoodnessonretro(double g)
  {
    onegoodnessonretro = g;
  }
  double Getonegoodnessonretro()
  {
    return onegoodnessonretro;
  }
  void Setonelikelihoodnoretro(double l)
  {
    onelikelihoodnoretro = l;
  }
  double Getonelikelihoodnoretro()
  {
    return onelikelihoodnoretro;
  }
  void Setonelikelihoodonretro(double l)
  {
    onelikelihoodonretro = l;
  }
  double Getonelikelihoodonretro()
  {
    return onelikelihoodonretro;
  }
  
private:
  int hittype; // 1: onretro , 2: noretro 3: darkrate 4: others
  double onegoodnessnoretro;
  double onegoodnessonretro;
  double onelikelihoodnoretro;
  double onelikelihoodonretro;
public:
  ClassDef(TReconstructhit,1)
};

  
#endif
