#include <TH2D.h>
#include "histmacro.hh"
#include "funcmap.hh"
#include <iostream>

void Fillconstvalue(TH2D* h1,double value)
{
  for(int i = 1;i <= h1->GetXaxis()->GetNbins() ; i++){
    for(int j = 1;j <= h1->GetYaxis()->GetNbins() ; j++){
      double temp = value + h1->GetBinContent(i,j);
      h1->SetBinContent(i,j,temp);
    }
  }
}

bool Issamestructure(TH2D* h1,TH2D* h2){
  int NX1 = h1->GetXaxis()->GetNbins();
  int NX2 = h2->GetXaxis()->GetNbins();
  bool issamexnum = (NX1 == NX2);
  bool issamexlowedge = (h1->GetXaxis()->GetBinCenter(1) == h2->GetXaxis()->GetBinCenter(1));
  bool issamexupedge = (h1->GetXaxis()->GetBinCenter(NX1) == h2->GetXaxis()->GetBinCenter(NX2));
  int NY1 = h1->GetYaxis()->GetNbins();
  int NY2 = h1->GetYaxis()->GetNbins();
  bool issameynum = (NY1 == NY2);
  bool issameylowedge = (h1->GetYaxis()->GetBinCenter(1) == h2->GetYaxis()->GetBinCenter(1));
  bool issameyupedge = (h1->GetYaxis()->GetBinCenter(NY1) == h2->GetYaxis()->GetBinCenter(NY2));
  return (issamexnum && issamexlowedge && issamexupedge && issameynum && issameylowedge && issameyupedge);
}

bool Issamestructure(TH1D* h1,TH2D* h2){
  int NX1 = h1->GetXaxis()->GetNbins();
  int NX2 = h2->GetXaxis()->GetNbins();
  bool issamexnum = (NX1 == NX2);
  bool issamexlowedge = (h1->GetXaxis()->GetBinCenter(1) == h2->GetXaxis()->GetBinCenter(1));
  bool issamexupedge = (h1->GetXaxis()->GetBinCenter(NX1) == h2->GetXaxis()->GetBinCenter(NX2));
  return (issamexnum && issamexlowedge && issamexupedge);
}
TH2D* calculate(TH2D* h1,TH2D* h2,const char* histname,const char* type){
  if(Issamestructure(h1,h2)){
    int xNbins = h1->GetXaxis()->GetNbins();
    double xlowedge = h1->GetXaxis()->GetBinLowEdge(1);
    double xupedge = h1->GetXaxis()->GetBinUpEdge(xNbins);
    int yNbins = h1->GetYaxis()->GetNbins();
    double ylowedge = h1->GetYaxis()->GetBinLowEdge(1);
    double yupedge = h1->GetYaxis()->GetBinUpEdge(yNbins);
    TH2D* hist = new TH2D(histname,";x;y",xNbins,xlowedge,xupedge,yNbins,ylowedge,yupedge);
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = (funcmap.at(type))(h1->GetBinContent(i,j),h2->GetBinContent(i,j));
	hist->SetBinContent(i,j,temp);
      }
    }
    return hist;
  }
  else{
    std::cout << "2 histogram has not same structure." << std::endl;
    throw "TH2D* calculate(TH2D*,TH2D*,const char*,const char*)";
  }
}

void Test(){}
