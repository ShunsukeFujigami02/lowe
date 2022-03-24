#include <iostream>

#include "OneRunGoodnessMinimizeAnalizeManager.hh"

ClassImp(OneRunGoodnessMinimizeAnalizeManager)

OneRunGoodnessMinimizeAnalizeManager::OneRunGoodnessMinimizeAnalizeManager()
{
}

OneRunGoodnessMinimizeAnalizeManager::OneRunGoodnessMinimizeAnalizeManager(const char* goodnessminimizefile)
{
  Setgoodnessminimizefile(goodnessminimizefile);
}

void OneRunGoodnessMinimizeAnalizeManager::Setgoodnessminimizefile(const char* goodnessminimizefile)
{
  if(gfile)
    {
      std::cout << "goodnessminimize file is already exist!" << std::endl;
      throw "OneRunGoodnessMinimizeAnalizeManager::Setgoodnessminimize(const char* goodnessminimizefile)";
    }
  gfile = new TFile(goodnessminimizefile);
  goodnessminimizeT = (TTree*)gfile->Get("goodnessminimizeT");
  gmoptionT = (TTree*)gfile->Get("gmoptionT");
  data = new TReconstructdata_minimize();
  option = new TOption_minimize();
  goodnessminimizeT->SetBranchAddress("reconstructdataminimize",&data);
  gmoptionT->SetBranchAddress("option_minimize",&option);
  neventgoodnessminimize = goodnessminimizeT->GetEntries();
  std::string sfilename = goodnessminimizefile;
  onegoodnessminimizeparameters = new OneGoodnessMinimizeParameters();
  onegoodnessminimizeparameters->Setpair(sfilename);
  onegoodnessminimizeparameters->SetValue();
}

OneRunGoodnessMinimizeAnalizeManager::~OneRunGoodnessMinimizeAnalizeManager()
{
  if(data)
    delete data;
  if(option)
    delete option;
  if(gfile)
    delete gfile;
  if(onegoodnessminimizeparameters)
    delete onegoodnessminimizeparameters;
}


void OneRunGoodnessMinimizeAnalizeManager::GetEntry(int i)
{
  goodnessminimizeT->GetEntry(i);
}

