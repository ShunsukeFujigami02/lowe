#ifndef LIKELIHOOD_DIRECTION_DATA_HH
#define LIKELIHOOD_DIRECTION_DATA_HH

#include <TObject.h>

class l_dir_data : public TObject 
{
  // class for the storage of likelihood direction analisys data
public:
  l_dir_data();
  l_dir_data(double costheta_in,double phi_in,double likelihood_in);
  virtual ~l_dir_data(){};
  void Setdata(l_dir_data data);
  void SetL(double l) { likelihood = l;}
  void SetCosTheta(double costheta_in){ costheta = costheta_in;}
  void SetPhi(double phi_in){ phi = phi_in;}
  double GetL(){return likelihood;}
  double GetCosTheta(){return costheta;}
  double GetPhi(){ return phi;}
private:
  double likelihood;
  double costheta;
  double phi;
public:
  ClassDef(l_dir_data,1)
};

#endif
