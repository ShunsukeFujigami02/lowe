// c++ STL
#include <cstring>
#include <memory>
// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "runoption.hh"
#include "config.hh"
#include "wrapped_function.hh"

int main(){
  Config_goodness_minimize config;
  TFile* fin_g = new TFile(config.infile_goodness);
  TTree* tin = (TTree*)fin_g->Get(config.intree_goodness);
  double ncherenkovdigihits_in;
  double max_goodness_in;
  double max_x_in;
  double max_y_in;
  double max_z_in;
  double max_t_in;
  tin->SetBranchAddress("ncherenkovdigihits",&ncherenkovdigihits_in);
  tin->SetBranchAddress("max_goodness",&max_goodness_in);
  tin->SetBranchAddress("max_x",&max_x_in);
  tin->SetBranchAddress("max_y",&max_y_in);
  tin->SetBranchAddress("max_z",&max_z_in);
  tin->SetBranchAddress("max_t",&max_t_in);
  TFile* fin_d = new TFile(config.infile_data);
  TTree* wcsimT = (TTree*)fin_d->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree* wcsimGeoT = (TTree*)fin_d->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile* fout = new TFile(config.outfile,"RECREATE");
  TTree* tree = new TTree(config.outtree,"title");
  TH1D* hxminus = new TH1D("hxminus","minus goodness x changed;x(cm);goodness",config.xbin,config.xmin-config.xwidth/2,config.xmax+config.xwidth/2);
  TH1D* ht = new TH1D("ht","minus goodness t changed;t(ns);goodness",config.tbin,config.tmin+config.twidth/2,config.tmax+config.twidth/2);
  TH1D* hxplus = new TH1D("hxplus","goodness x changed;x(cm);goodness",config.xbin,config.xmin-config.xwidth/2,config.xmax+config.xwidth/2);
  double ncherenkovdigihits_out;
  double max_goodness_out;
  double max_x_out;
  double max_y_out;
  double max_z_out;
  double max_t_out;
  int status;
  unsigned int ncalls;
  unsigned int nIterations;
  tree->Branch("ncherenkovdigihits",&ncherenkovdigihits_out);
  tree->Branch("max_goodness_grid",&max_goodness_in);
  tree->Branch("max_goodness_minimized",&max_goodness_out);
  tree->Branch("max_x_grid",&max_x_in);
  tree->Branch("max_y_grid",&max_y_in);
  tree->Branch("max_z_grid",&max_z_in);
  tree->Branch("max_t_grid",&max_t_in);
  tree->Branch("max_x_minimized",&max_x_out);
  tree->Branch("max_y_minimized",&max_y_out);
  tree->Branch("max_z_minimized",&max_z_out);
  tree->Branch("max_t_minimized",&max_t_out);
  tree->Branch("status",&status);
  tree->Branch("ncalls",&ncalls);
  tree->Branch("nIterations",&nIterations);
  int N = tin->GetEntries();
  const int nvar = 4;
  for(int i = 0;i < N; i++){
    tin->GetEntry(i);
    wcsimT->GetEntry(i);
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    std::shared_ptr<runoption> option {new runoption(wcsimrootgeom,wcsimroottrigger)};
    std::string s_ogfuncname = config.ogfuncname;
    option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
    option->sigma = config.sigma;
    wrapped_function func(option);
    ROOT::Math::Minimizer* min = 
      ROOT::Math::Factory::CreateMinimizer();

    std::cout << ROOT::Math::MinimizerOptions::DefaultMinimizerType() << std::endl;

    min->SetMaxFunctionCalls(1000000);
    min->SetMaxIterations(100000);
    min->SetTolerance(0.001);

    ROOT::Math::Functor f(&func,&wrapped_function::goodness_minus,nvar); 
    double step[nvar] = {10.,10.,10.,1.};
    double variable[nvar] = {max_x_in,max_y_in,max_z_in,max_t_in};
    double lower[nvar] = {-3000.,-3000.,-3000.,-300.};
    double upper[nvar] = {3000.,3000.,3000.,0.};
    min->SetFunction(f);
    min->SetLimitedVariable(0,"x",variable[0],step[0],lower[0],upper[0]);
    min->SetLimitedVariable(1,"y",variable[1],step[1],lower[1],upper[1]);
    min->SetLimitedVariable(2,"z",variable[2],step[2],lower[2],upper[2]);
    min->SetLimitedVariable(3,"t",variable[3],step[3],lower[3],upper[3]);

    min->Minimize();

    min->PrintResults();
    status = min->Status();
    ncalls = min->NCalls();
    nIterations = min->NIterations();
    const double* variable_out = min->X();
    ncherenkovdigihits_out = ncherenkovdigihits_in;
    max_x_out = variable_out[0];
    max_y_out = variable_out[1];
    max_z_out = variable_out[2];
    max_t_out = variable_out[3];
    max_goodness_out = f(variable_out);
    tree->Fill();
    if(i == config.nevent){
      for(double x = config.xmin;x <= config.xmax;x+= config.xwidth){
	const double variable_changex[4] = {x,max_y_out,max_z_out,max_t_out};
	hxminus->Fill(x,f(variable_changex));
	hxplus->Fill(x,-f(variable_changex));
      }
      for(double t = config.tmin;t <= config.tmax;t+= config.twidth){
	const double variable_changet[4] = {max_x_out,max_y_out,max_z_out,t};
	ht->Fill(t,f(variable_changet));
      }
    }
  }
  fout->Write();
  fout->Close();
}
