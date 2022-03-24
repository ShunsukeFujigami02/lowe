#include <iostream>

#include "OneRunGoodnessAnalizeManager.hh"

ClassImp(OneRunGoodnessAnalizeManager)

OneRunGoodnessAnalizeManager::OneRunGoodnessAnalizeManager()
{
}

OneRunGoodnessAnalizeManager::OneRunGoodnessAnalizeManager(const char* goodnessfile)
{
  Setgoodnessfile(goodnessfile);
}

void OneRunGoodnessAnalizeManager::Setgoodnessfile(const char* goodnessfile)
{
  if(gfile)
    {
      std::cout << "goodness file is already exist!" << std::endl;
      throw "OneRunGoodnessAnalizeManager::Setgoodnessfile(TFile* goodnessfile)";
    }
  gfile = new TFile(goodnessfile);
  goodnessT = (TTree*)gfile->Get("goodnessT");
  optionT = (TTree*)gfile->Get("optionT");
  //  data = new TReconstructdata();
  //  range = new CSearch_range();
  goodnessT->SetBranchAddress("reconstructdata",&data);
  optionT->SetBranchAddress("csearchrange",&range);
  optionT->GetEntry(0);
  neventgoodness = goodnessT->GetEntries();
  std::string sfilename = goodnessfile;
  onegoodnessparameters = new OneGoodnessParameters();
  onegoodnessparameters->Setpair(sfilename);
  onegoodnessparameters->SetValue();
}

OneRunGoodnessAnalizeManager::~OneRunGoodnessAnalizeManager()
{
  if(data)
    delete data;
  if(range)
    delete range;
  if(gfile)
    delete gfile;
  if(onegoodnessparameters)
    delete onegoodnessparameters;
  
}

void OneRunGoodnessAnalizeManager::GetEntry(int i)
{
  goodnessT->GetEntry(i);
}

