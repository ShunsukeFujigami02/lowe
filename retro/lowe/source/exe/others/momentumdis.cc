#include <TLorentzVector.h>
#include <TRint.h>
#include <cmath>
#include <random>
#include <TH1D.h>
#include <TCanvas.h>
int main(int argc,char** argv)
{
  TRint app("app",&argc,argv);
  double M = 175.;
  TLorentzVector Mvec;
  TVector3 Mvec3(0.,0.,100.);
  Mvec.SetVectM(Mvec3,M);
  TVector3 boost = Mvec.BoostVector();
  double mass1 = 173.;
  double mass2 = 1.;
  double pstatic = std::sqrt((M*M - (mass1+mass2)*(mass1+mass2))*(M*M - (mass1 - mass2)*(mass1 - mass2)))/(2*M);
  std::random_device rnd;
  std::mt19937 mtcostheta(rnd());
  std::mt19937 mtphi(rnd());
  std::uniform_real_distribution<> randcostheta(-1.,1.);
  std::uniform_real_distribution<> randphi(-std::acos(-1.),std::acos(-1.));
  TH1D* hp1 = new TH1D("hp1","",1000,0.,300.);
  TH1D* hp2 = new TH1D("hp2","",1000,0.,200.);
  TH1D* heta1 = new TH1D("heta1","",1000,0.,5.);
  for(int i = 0;i < 100000;i++){
    double pcostheta = randcostheta(mtcostheta);
    double phi = randphi(mtphi);
    TVector3 pstatic1;
    pstatic1.SetMagThetaPhi(pstatic,std::acos(pcostheta),phi);
    TVector3 pstatic2 = -pstatic1;
    TLorentzVector vec1,vec2;
    vec1.SetVectM(pstatic1,mass1);
    vec2.SetVectM(pstatic2,mass2);
    vec1.Boost(boost);
    vec2.Boost(boost);
    hp1->Fill(vec1.P());
    heta1->Fill(vec1.Eta());
    hp2->Fill(vec2.P());
  }
  TCanvas* c1 = new TCanvas("c1","");
  hp1->Draw("hist");
  //  hp2->Draw("hist");
  heta1->Draw("hist");
  app.Run();
  delete c1;
  delete hp1;
}
    
  
