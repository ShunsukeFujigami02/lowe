#ifndef HISTBYTREE_HH
#define HISTBYTREE_HH
// ROOT library
#include <TH1D.h>
#include <TTree.h>
#include <TF1.h>
// self-introduced library
#include "goodness_data.hh"


class TH1DByTree :public TH1D
{
public:
  enum Axis
    {
      x,y,z,t
    };
  
    
  TH1DByTree();
  TH1DByTree(TTree* tree,const char* paraname,const char* name,const char* title,int num,double min,double max,double width,Axis axis=x);
  TH1DByTree(TTree* tree,goodness_data* data,const char* name,const char* title,int num,double min,double max,double width,Axis axis);
  virtual ~TH1DByTree();
  void FitByGaussian(double secondpara,double firstpara=100.,double thirdpara=100.);
  void DrawGaussian(Option_t* option="");
  double GetGaussianBias(){return fgaussian->GetParameter(1);}
  double GetGaussianError(){return fgaussian->GetParameter(2);}
  double GetGaussianBiasError()
  {
    return fgaussian->GetParError(1);
  }
  double GetGaussianErrorError()
  {
    return fgaussian->GetParError(2);
  }
  
private:
  TF1* fgaussian = nullptr;
  int Nevent;
  double central;
  Axis axis;
public:
  ClassDef(TH1DByTree,1)
};

#endif
