#include <iostream>
#include <cmath>
#include <TF1.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>

double f_direction_2ndorder(double* x,double* par){
  double aminus = par[0];
  double bminus = par[1];
  double cminus = par[2];
  double aplus = par[3];
  double bplus = par[4];
  double cplus = par[5];
  double xx = x[0];
  double value;
  if(xx < 0.75){
    value = aminus * xx * xx + bminus * xx + cminus;
  }
  else{
    value = aplus * xx * xx + bplus * xx + cplus;
  }
  return value;
}

double f_direction_exp(double* x,double* par){
  double aminus = par[0];
  double bminus = par[1];
  double cminus = par[2];
  double aplus = par[3];
  double bplus = par[4];
  double cplus = par[5];
  double xx = x[0];
  double value;
  if(xx < 0.75){
    value = aminus * std::exp(bminus * xx ) + cminus;
  }
  else{
    value = aplus * std::exp(bplus * xx )+ cplus;
  }
  return value;
}

double f_direction_exp_ver2(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = par[2];
  double xx = x[0];
  double value;
  if(xx < 0.75)
    value = a * std::exp(b * xx ) + c;
  else
    value = 0;
  return value;
}

double f_direction_exp_ver3(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = par[2];
  double xx = x[0];
  double value;
  if(xx > 0.75)
    value = a * std::exp(b * xx ) + c;
  else
    value = 0;
  return value;
}

double f_direction_exp_ver4(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = par[2];
  double xx = x[0];
  double value;
  value = a * std::exp(b * xx ) + c;
  return value;
}

double f_direction_exp_ver5(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double xx = x[0];
  double value;
  value = 1 + a * (std::exp(b * (xx - 0.75) ) - 1 );
  return value;
}

double f_direction_exp_ver6(double* x,double* par){
  double aminus = par[0];
  double bminus = par[1];
  double aplus = par[2];
  double bplus = par[3];
  double xx = x[0];
  double value;
  if(xx < 0.75)
    value = 1 + aminus * (std::exp(bminus * (xx - 0.75) ) - 1);
  else
    value = 1 + aplus * (std::exp(bplus * (xx - 0.75) ) -1);
  return value;
}

int main(){
  TF1* f1 = new TF1("func1",f_direction_exp_ver5,-1.,1.,2);
  TF1* f2 = new TF1("func2",f_direction_exp_ver5,-1.,1.,2);
  f1->SetParameters(1.,1.,0.);
  f2->SetParameters(10.,-10.,0.);
  double costhetaminus[9] = {-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.625,0.75};
  double fminus[9] = {0.04,0.05,0.07,0.09,0.13,0.2,0.34,0.57,1.};
  double costhetaplus[4] = {0.75,0.8,0.875,1.};
  double fplus[4] = {1.,0.85,0.6,0.46};
  double costheta[12] = {-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.625,0.75,0.8,0.875,1.};
  double f[12] = {0.04,0.05,0.07,0.09,0.13,0.2,0.34,0.57,1.,0.85,0.6,0.46};
  TGraph* g1 = new TGraph(9,costhetaminus,fminus);
  TGraph* g2 = new TGraph(4,costhetaplus,fplus);
  TGraph* g3 = new TGraph(12,costheta,f);
  g1->Fit(f1);
  g2->Fit(f2);
  TF1* f3 = new TF1("func3",f_direction_exp_ver6,-1.,1.,4);
  f3->SetParameters(f1->GetParameter(0),f1->GetParameter(1),f2->GetParameter(0),f2->GetParameter(1));
  for(int i = 0;i < 2;i++){
    std::cout << "f1 p[" << i << "]=" << f1->GetParameter(i) << std::endl;
  }
  for(int j = 0;j < 2;j++){
    std::cout << "f2 p[" << j << "]=" << f2->GetParameter(j) << std::endl;
  }
  TCanvas* c1 = new TCanvas("c1","c1");
  //  f1->Draw();
  //  f2->Draw("same");
  //  g1->SetMarkerStyle(20);
  //  g1->SetMarkerSize(1.);
  //  g1->Draw("sameAP");
  //  g2->SetMarkerStyle(20);
  //  g2->SetMarkerSize(1.);
  //  g2->Draw("sameAP");
  g3->SetMarkerStyle(20);
  g3->SetMarkerSize(1.);
  g3->Draw("AP");
  f3->Draw("same");
  c1->SaveAs("/home/fujigami/retro/lowe/picture/2020July/f_direction_expver3.png");
  return 0;
}
