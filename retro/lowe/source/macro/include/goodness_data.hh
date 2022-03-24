#ifndef GOODNESS_DATA_HH
#define GOODNESS_DATA_HH

// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>

class goodness_data : public TObject
{
  // class to manage analysis data by goodness search
public:
  goodness_data(TLorentzVector vector,double goodness = 0)
    :vector(vector), goodness(goodness)
  {}
  goodness_data()
    :vector(0.,0.,0.,0.),goodness(0.)
  {}
  virtual ~goodness_data(){}
  double GetT() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  TVector3 GetPosition() const;
  TLorentzVector Get4Vector() const;
  double Getgoodness() const;
  void Set4Vector(TLorentzVector vector_input);
  void Setgoodness(double goodness_input);
  void Setdata(goodness_data data);
private:
  TLorentzVector vector;
  double goodness;
public:
  ClassDef(goodness_data,1)
};
#endif
