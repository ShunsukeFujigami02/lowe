#include <iostream>

#include "OneRunLikelihoodAnalizeManager.hh"

ClassImp(OneRunLikelihoodAnalizeManager)

OneRunLikelihoodAnalizeManager::OneRunLikelihoodAnalizeManager()
{
}

OneRunLikelihoodAnalizeManager::OneRunLikelihoodAnalizeManager(const char* likelihoodfile)
{
  Setlikelihoodfile(likelihoodfile);
}

void OneRunLikelihoodAnalizeManager::Setlikelihoodfile(const char* likelihoodfile)
{
  if(lfile)
    {
      std::cout << "likelihood file is already exist!" << std::endl;
      throw "OneRunLikelihoodAnalizeManager::Setlikelihoodfile(const char* likelihoodfile)";
    }
  lfile = new TFile(likelihoodfile);
  likelihoodT = (TTree*)lfile->Get("likelihoodT");
  loptionT = (TTree*)lfile->Get("loptionT");
  data = new TReconstructdata();
  range = new AngleRange();
  likelihoodT->SetBranchAddress("reconstructdatalikelihood",&data);
  loptionT->SetBranchAddress("anglerange",&range);
  loptionT->GetEntry(0);
  neventlikelihood = likelihoodT->GetEntries();
  std::string sfilename = likelihoodfile;
  onelikelihoodparameters = new OneLikelihoodParameters();
  onelikelihoodparameters->Setpair(sfilename);
  onelikelihoodparameters->SetValue();
}

OneRunLikelihoodAnalizeManager::~OneRunLikelihoodAnalizeManager()
{
  if(data)
    delete data;
  if(range)
    delete range;
  if(lfile)
    delete lfile;
  if(onelikelihoodparameters)
    delete onelikelihoodparameters;
}

void OneRunLikelihoodAnalizeManager::GetEntry(int i)
{
  likelihoodT->GetEntry(i);
}

