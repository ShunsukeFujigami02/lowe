#include <cmath>
#include <cstring>
#include <iostream>

#include <TH2D.h>

void BinaryOperation(TH2D* hist,TH2D* h1,TH2D* h2,const char* type){
  std::string s_type = type;
  if(s_type == "+"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = h1->GetBinContent(i,j) + h2->GetBinContent(i,j);
	hist->SetBinContent(i,j,temp);
      }
    }
  }
  else if(s_type == "-"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = h1->GetBinContent(i,j) - h2->GetBinContent(i,j);
	hist->SetBinContent(i,j,temp);
      }
    }
  }
  else if(s_type == "*"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = h1->GetBinContent(i,j) * h2->GetBinContent(i,j);
	hist->SetBinContent(i,j,temp);
      }
    }
  }
  else if(s_type == "/"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = h1->GetBinContent(i,j) / h2->GetBinContent(i,j);
	hist->SetBinContent(i,j,temp);
      }
    }
  }
  else if(s_type == "gamma"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      for(int j = 1;j <= hist->GetYaxis()->GetNbins();j++){
	double temp = (std::log(h1->GetBinContent(i,j) / h2->GetBinContent(i,j))/std::log(10.));
	hist->SetBinContent(i,j,temp);
      }
    }
  }
  else{
    std::cout << "invalid type" << std::endl;
    throw "Binary Operation";
  }
}

void BinaryOperation(TH1D* hist,TH1D* h1,TH1D* h2,const char* type){
  std::string s_type = type;
  if(s_type == "+"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      double temp = h1->GetBinContent(i) + h2->GetBinContent(i);
      hist->SetBinContent(i,temp);
    }
  }
  else if(s_type == "-"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      double temp = h1->GetBinContent(i) - h2->GetBinContent(i);
      hist->SetBinContent(i,temp);
    }
  }
  else if(s_type == "*"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      double temp = h1->GetBinContent(i) * h2->GetBinContent(i);
      hist->SetBinContent(i,temp);
    }
  }
  else if(s_type == "/"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      double temp = h1->GetBinContent(i) / h2->GetBinContent(i);
      hist->SetBinContent(i,temp);
    }
  }
  else if(s_type == "gamma"){
    for(int i = 1;i <= hist->GetXaxis()->GetNbins();i++){
      double temp = (std::log(h1->GetBinContent(i) / h2->GetBinContent(i))/std::log(10.));
      hist->SetBinContent(i,temp);
    }
  }
  else{
    std::cout << "invalid type" << std::endl;
    throw "Binary Operation";
  }
}
