// c++ STL
#include <iostream>
#include <memory>
#include <cstring>
#include <cmath>
#include <stdexcept>
// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <Math/MinimizerOptions.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"
#include "runoption.hh"
#include "likelihood_direction_data.hh"
#include "likelihood_direction_grid_search.hh"
#include "numberofhit.hh"
#include "WCGoodness_calculate.hh"
#include "goodness_data.hh"
#include "constants.hh"
#include "wrapped_function.hh"
int main()
{
  try{
    Config_likelihood_direction_grid_search config;
    TFile* file = new TFile(config.infile_data);
    TTree* wcsimT =(TTree*)file->Get("wcsimT");
    WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
    wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
    wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
    TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
    WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
    wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
    wcsimGeoT->GetEntry(0);
    std::string s_voption = config.voption;
    double max_x_in;
    double max_y_in;
    double max_z_in;
    double max_t_in;
    int ncherenkovdigihits;
    TFile* f_g = new TFile(config.infile_goodness);
    std::cout << "0" << std::endl;
    TTree* t_g = (TTree*)f_g->Get(config.intree);
    std::cout << "1" << std::endl;
    int N;
    if(s_voption == "true"){
      max_x_in = config.truex;
      max_y_in = config.truey;
      max_z_in = config.truez;
      N = wcsimT->GetEntries();
    }
    else{
      t_g->SetBranchAddress("max_x",&max_x_in);
      t_g->SetBranchAddress("max_y",&max_y_in);
      t_g->SetBranchAddress("max_z",&max_z_in);
      t_g->SetBranchAddress("max_t",&max_t_in);
      N = t_g->GetEntries();
    }
    t_g->SetBranchAddress("ncherenkovdigihits",&ncherenkovdigihits);
    TFile *fout = new TFile(config.outfile,"RECREATE");
    TTree *tree = new TTree(config.outtree,"title");
    double max_likelihood;
    double max_likelihood_noretro;
    double max_likelihood_onretro;
    double nhit_noretro;
    double nhit_onretro;
    double max_x;
    double max_y;
    double max_z;
    double max_t;
    double max_costheta;
    double max_phi;
    double max_angle;
    double minimized_x;
    double minimized_y;
    double minimized_z;
    double minimized_t;
    double minimized_costheta;
    double minimized_phi;
    double minimized_angle;
    double minimized_likelihood;
    int status;
    int ncalls;
    int nIterations;
    tree->Branch("max_likelihood",&max_likelihood);
    tree->Branch("max_likelihood_noretro",&max_likelihood_noretro);
    tree->Branch("max_likelihood_onretro",&max_likelihood_onretro);
    tree->Branch("nhit_noretro",&nhit_noretro);
    tree->Branch("nhit_onretro",&nhit_onretro);
    tree->Branch("max_x",&max_x);
    tree->Branch("max_y",&max_y);
    tree->Branch("max_z",&max_z);
    tree->Branch("max_t",&max_t);
    tree->Branch("max_costheta",&max_costheta);
    tree->Branch("max_phi",&max_phi);
    tree->Branch("max_angle",&max_angle);
    tree->Branch("minimized_x",&minimized_x);
    tree->Branch("minimized_y",&minimized_y);
    tree->Branch("minimized_z",&minimized_z);
    tree->Branch("minimized_t",&minimized_t);
    tree->Branch("minimized_costheta",&minimized_costheta);
    tree->Branch("minimized_phi",&minimized_phi);
    tree->Branch("minimized_angle",&minimized_angle);
    tree->Branch("minimized_likelihood",&minimized_likelihood);
    tree->Branch("status",&status);
    tree->Branch("ncalls",&ncalls);
    tree->Branch("nIterations",&nIterations);
    tree->Branch("ncherenkovdigihits",&ncherenkovdigihits);
    const int nvar = 6;
    for(int i = 0;i < N; i++){
      if(s_voption != "true"){
	t_g->GetEntry(i);
      }
      wcsimT->GetEntry(i);
      TLorentzVector fitted4Vector(max_x_in,max_y_in,max_z_in,max_t_in);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      std::shared_ptr<runoption> option { new runoption(wcsimrootgeom,wcsimroottrigger)};
      if(s_voption == "true"){
	//	std::string s_gfuncname = config.gfuncname;
	//	option->gfunc = (option->gfuncmap).at(s_gfuncname);
	option->SetVariable("gfunc",config.gfuncname);
	//	std::string s_ogfuncname = config.ogfuncname;
	//	option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
	option->SetVariable("ogfunc",config.ogfuncname);
	option->sigma = config.sigma;
	goodness_data data = WCGoodness_calculate(config.range,option);
	max_t_in = data.GetT();
	fitted4Vector.SetT(max_t_in);
      }
      //      std::string s_lfuncname = config.lfuncname;
      //      option->lfunc = (option->lfuncmap).at(s_lfuncname);
      option->SetVariable("lfunc",config.lfuncname);
      //      std::string s_f_dirfunc_noretroname = config.f_dirfunc_noretroname;
      //      option->f_dirfunc_noretro = (option->f_dirfuncmap).at(s_f_dirfunc_noretroname);
      option->SetVariable("f_dirfunc_noretro",config.f_dirfunc_noretroname);
      //      std::string s_f_dirfunc_onretroname = config.f_dirfunc_onretroname;
      //      option->f_dirfunc_onretro = (option->f_dirfuncmap).at(s_f_dirfunc_onretroname);
      option->SetVariable("f_dirfunc_onretro",config.f_dirfunc_onretroname);
      //      std::string s_afuncname = config.afuncname;
      //      option->afunc = (option->afuncmap).at(s_afuncname);
      option->SetVariable("afunc",config.afuncname);
      //      std::string s_gffuncname = config.gffuncname;
      //      option->gffunc = (option->gffuncmap).at(s_gffuncname);
      option->SetVariable("gffunc",config.gffuncname);
      if(i == 0){
	option->Print();
      }
      l_dir_data data = likelihood_direction_grid_search(fitted4Vector,config.costheta_width,config.phi_width,option);
      max_costheta = data.GetCosTheta();
      max_phi = data.GetPhi();
      max_x = max_x_in;
      max_y = max_y_in;
      max_z = max_z_in;
      max_t = max_t_in;
      TVector3 truevector3;
      TVector3 fittedvector3;
      truevector3.SetMagThetaPhi(1.,config.trueTheta,config.truePhi);
      fittedvector3.SetMagThetaPhi(1.,std::acos(max_costheta),max_phi);
      max_angle = truevector3.Angle(fittedvector3);
      max_likelihood = data.GetL();
      max_likelihood_noretro = ((option->lfuncmap).at("no_retro"))(fitted4Vector,max_costheta,max_phi,option);
      max_likelihood_onretro = ((option->lfuncmap).at("on_retro"))(fitted4Vector,max_costheta,max_phi,option);
      nhit_noretro = numberofhit_noretro(fitted4Vector,option);
      nhit_onretro = numberofhit_onretro(fitted4Vector,option);
      std::cout << "event" << i << std::endl;
      std::cout << "costheta : " << max_costheta << " , phi : " << max_phi << " , likelihood : " << max_likelihood << std::endl;
      std::cout << "x : " << fitted4Vector.X() << "y : " << fitted4Vector.Y() << "z : " << fitted4Vector.Z() << std::endl;
      wrapped_function func(option);
      ROOT::Math::Minimizer* min = 
	ROOT::Math::Factory::CreateMinimizer();
      min->SetMaxFunctionCalls(1000000);
      min->SetMaxIterations(100000);
      min->SetTolerance(0.001);
      
      ROOT::Math::Functor f(&func,&wrapped_function::goodness_x_f_direction_minus,nvar);
      double step[nvar] = {10.,10.,10.,1.,0.1,0.1};
      double variable[nvar] = {max_x_in,max_y_in,max_z_in,max_t_in,max_costheta,max_phi};
      double lower[nvar] = {-3000.,-3000.,-3000,-300.,-1.,0.};
      double upper[nvar] = {3000.,3000.,3000.,0.,1.,2*PI};
      min->SetFunction(f);
      min->SetLimitedVariable(0,"x",variable[0],step[0],lower[0],upper[0]);
      min->SetLimitedVariable(1,"y",variable[1],step[1],lower[1],upper[1]);
      min->SetLimitedVariable(2,"z",variable[2],step[2],lower[2],upper[2]);
      min->SetLimitedVariable(3,"t",variable[3],step[3],lower[3],upper[3]);
      min->SetLimitedVariable(4,"costheta",variable[4],step[4],lower[4],upper[4]);
      min->SetLimitedVariable(5,"phi",variable[5],step[5],lower[5],upper[5]);
      
      min->Minimize();
      
      status = min->Status();
      ncalls = min->NCalls();
      nIterations = min->NIterations();
      const double* variable_out = min->X();
      minimized_x = variable_out[0];
      minimized_y = variable_out[1];
      minimized_z = variable_out[2];
      minimized_t = variable_out[3];
      minimized_costheta = variable_out[4];
      minimized_phi = variable_out[5];
      TVector3 minimizedvector3;
      minimizedvector3.SetMagThetaPhi(1.,std::acos(minimized_costheta),minimized_phi);
      minimized_angle = minimizedvector3.Angle(truevector3);
      minimized_likelihood = -f(variable_out);
      tree->Fill();
    }
    fout->Write();
    fout->Close();
  }
  catch(const char* str){
    std::cout << "Error in " << str << std::endl;
  }
  catch(std::out_of_range&){
    std::cout << "exception std::out_of_range" << std::endl;
  }
  return 0;
}
