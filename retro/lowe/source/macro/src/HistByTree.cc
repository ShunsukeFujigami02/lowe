// ROOT library
#include <TTree.h>
// self-introduced library
#include "HistByTree.hh"
#include "goodness_data.hh"
ClassImp(TH1DByTree)

TH1DByTree::TH1DByTree():TH1D()
{
}

TH1DByTree::TH1DByTree(TTree* tree,const char* paraname,const char* name,const char* title,int num,double min,double max,double width,Axis axis)
  :TH1D(name,title,num,min-width/2.,max+width/2.)
{
  central = (GetXaxis()->GetXmin()+GetXaxis()->GetXmax())/2.;
  Nevent = tree->GetEntries();
  goodness_data* data;
  tree->SetBranchAddress(paraname,&data);
  for(int i = 0; i < Nevent; i++)
    {      
      tree->GetEntry(i);
      if(axis == x)
	{
	  Fill(data->GetX());
	}
    }
  SetStats(0);
}

TH1DByTree::TH1DByTree(TTree* tree,goodness_data* data,const char* name,const char* title,int num,double min,double max,double width,Axis axis)
  :TH1D(name,title,num,min-width/2.,max+width/2.)
{
  central = (GetXaxis()->GetXmin()+GetXaxis()->GetXmax())/2.;
  Nevent = tree->GetEntries();
  for(int i = 0; i < Nevent; i++)
    {      
      tree->GetEntry(i);
      if(axis == x)
	{
	  Fill(data->GetX());
	}
    }
  SetStats(0);
}

TH1DByTree::~TH1DByTree()
{
  if(fgaussian)
    {
      delete fgaussian;
    }
}


void TH1DByTree::FitByGaussian(double secondpara,double firstpara,double thirdpara)
{
  fgaussian = new TF1("fgaussian","[0]*exp(-0.5*pow((x-[1])/[2],2))",GetXaxis()->GetXmin(),GetXaxis()->GetXmax());
  fgaussian->SetParameters(firstpara,secondpara,thirdpara);
  Fit("fgaussian");
}

void TH1DByTree::DrawGaussian(Option_t* option)
{
  fgaussian->Draw(option);
}
