#include <TH2D.h>
#include "../include/histmacro.hh"
#include "../include/funclist.hh"
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

bool Issamestructure(TH1D* h1,TH1D* h2){
  int NX1 = h1->GetXaxis()->GetNbins();
  int NX2 = h2->GetXaxis()->GetNbins();
  bool issamexnum = (NX1 == NX2);
  bool issamexlowedge = (h1->GetXaxis()->GetBinCenter(1) == h2->GetXaxis()->GetBinCenter(1));
  bool issamexupedge = (h1->GetXaxis()->GetBinCenter(NX1) == h2->GetXaxis()->GetBinCenter(NX2));
  return (issamexnum && issamexlowedge && issamexupedge);
}
TH2D* calculate(TH2D* h1,TH2D* h2,const char* histname,const char* title,const char* type){
  if(Issamestructure(h1,h2)){
    int xNbins = h1->GetXaxis()->GetNbins();
    double xlowedge = h1->GetXaxis()->GetBinLowEdge(1);
    double xupedge = h1->GetXaxis()->GetBinUpEdge(xNbins);
    int yNbins = h1->GetYaxis()->GetNbins();
    double ylowedge = h1->GetYaxis()->GetBinLowEdge(1);
    double yupedge = h1->GetYaxis()->GetBinUpEdge(yNbins);
    TH2D* hist = new TH2D(histname,title,xNbins,xlowedge,xupedge,yNbins,ylowedge,yupedge);
    BinaryOperation(hist,h1,h2,type);
    return hist;
  }
  else{
    std::cout << "2 histogram has not same structure." << std::endl;
    throw "TH2D* calculate(TH2D*,TH2D*,const char*,const char*)";
  }
}

TH1D* calculate(TH1D* h1,TH1D* h2,const char* histname,const char* title,const char* type){
  if(Issamestructure(h1,h2)){
    int Nbins = h1->GetXaxis()->GetNbins();
    double lowedge = h1->GetXaxis()->GetBinLowEdge(1);
    double upedge = h1->GetXaxis()->GetBinUpEdge(Nbins);
    TH1D* hist = new TH1D(histname,title,Nbins,lowedge,upedge);
    BinaryOperation(hist,h1,h2,type);
    return hist;
  }
  else{
    std::cout << "2 histogram has not same structure." << std::endl;
    throw "TH1D* calculate(TH1D*,TH1D*,const char*,const char*)";
  }
}

void projectionX_compare(TH2D* hin1,TH2D* hin2){
  TH1D* h1 = hin1->ProjectionX("h1");
  TH1D* h2 = hin2->ProjectionX("h2");
  h1->SetStats(0);
  h2->SetStats(0);
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->Draw();
  h2->Draw("same");
}

void projectionY_compare(TH2D* hin1,TH2D* hin2){
  TH1D* h1 = hin1->ProjectionY("h1");
  TH1D* h2 = hin2->ProjectionY("h2");
  h1->SetStats(0);
  h2->SetStats(0);
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->Draw();
  h2->Draw("same");
}

void Test(){};
