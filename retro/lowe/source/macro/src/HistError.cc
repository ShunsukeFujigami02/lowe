// ROOT library
#include <TFile.h>
#include <TTree.h>
// self-introduced library
#include "FileList.hh"
#include "HistByTree.hh"
#include "HistError.hh"

ClassImp(HistError)

HistError::HistError()
:TH1D()
{
}

HistError::HistError(FileList* list,const char* paraname_in,const char* name,const char* title,int num,double min,double max,double width,int numorig_in,double minorig_in,double maxorig_in,double widthorig_in)
  :TH1D(name,title,num,min-width/2.,max+width/2.),paraname(paraname_in)
{
  numorig = numorig_in;
  minorig = minorig_in;
  maxorig = maxorig_in;
  widthorig = widthorig_in;
  filelist.Copy(*list);
  double iter = min;
  for(int i = 0; i < num ; i++, iter += width)
    {
      fillloop(i,iter);
    }
  SetStats(0);
}


void HistError::fillloop(int i,double iter)
{
  TFile* file = (TFile*)filelist.At(i);
  TTree* tree = (TTree*)file->Get("goodness_time_and_position");
  TH1DByTree* h1 = new TH1DByTree(tree,paraname,"","",numorig,minorig,maxorig,widthorig);
  h1->FitByGaussian(0.);
  Fill(iter,h1->GetGaussianError());
  SetBinError(i+1,h1->GetGaussianErrorError());
  delete h1;
}

