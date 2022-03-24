#include <cmath>
#include <TH1D.h>
#include <TF1.h>

double f_direction_exp_noretro(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = par[2];
  double xx = x[0];
  double value;
  value = a * (std::exp(b * (xx - 0.75) ) - 1 ) + c;
  return value;
}

double f_direction_exp_noretro2(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = 9.75097e+03;
  double xx = x[0];
  double value;
  value = a * (std::exp(b * (xx - 0.75) ) - 1 ) + c;
  return value;
}

double f_direction_exp_onretro(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = par[2];
  double xx = x[0];
  double value;
  value = a * (std::exp(b * (xx + 0.75) ) -1 ) + c;
  return value;
}

double f_direction_exp_onretro2(double* x,double* par){
  double a = par[0];
  double b = par[1];
  double c = 1.05106e+03;
  double xx = x[0];
  double value;
  value = a * (std::exp(b * (xx + 0.75) ) -1 ) + c;
  return value;
}

void fitting_f_direction_noretro(TH1D* h1){
  TF1* f1 = new TF1("func1",f_direction_exp_noretro,-1.,1.,3);
  f1->SetParameters(1.,1.,18000.);
  h1->Fit(f1,"","",-1.,0.75);
  h1->Draw();
  f1->Draw("same");
}

void fitting_f_direction_noretro2(TH1D* h1){
  TF1* f1 = new TF1("func1",f_direction_exp_noretro,-1.,1.,3);
  TF1* f2 = new TF1("func2",f_direction_exp_noretro2,-1.,1.,2);
  f1->SetParameters(1.,1.,18000.);
  f2->SetParameters(10.,-1.);
  h1->Fit(f1,"","",-1.,0.75);
  h1->Fit(f2,"","",0.75,1.);
  h1->Draw();
  f1->Draw("same");
  f2->Draw("same");
}

void fitting_f_direction_onretro(TH1D* h1){
  TF1* f1 = new TF1("func1",f_direction_exp_onretro,-1.,1.,3);
  f1->SetParameters(1.,-1.,1200.);
  h1->Fit(f1,"","",-0.75,1);
  h1->Draw();
  f1->Draw("same");
}

void fitting_f_direction_onretro2(TH1D* h1){
  TF1* f1 = new TF1("func1",f_direction_exp_onretro,-1.,1.,3);
  TF1* f2 = new TF1("func2",f_direction_exp_onretro2,-1.,1.,2);
  f1->SetParameters(1.,-1.,18000.);
  f2->SetParameters(10.,1.);
  h1->Fit(f1,"","",-0.75,1.);
  h1->Fit(f2,"","",-1.,-0.75);
  h1->Draw();
  f1->Draw("same");
  f2->Draw("same");
}
