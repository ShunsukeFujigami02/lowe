#include "GoodnessMinimizeRunAction.hh"

GoodnessMinimizeRunAction::GoodnessMinimizeRunAction(const char* outfile_in,const char* infilelikelihood_in)
  :outfile(outfile_in),cinfilelikelihood(infilelikelihood_in)
{
}


void GoodnessMinimizeRunAction::BeginOfAction(std::shared_ptr<Process>)
{
  TFile* flikelihood = new TFile(cinfilelikelihood);
  MyString* infiledataname = (MyString*)flikelihood->Get("infiledataname");
  MyString* infilegoodnessname = (MyString*)flikelihood->Get("infilegoodnessname");
  std::string sinfiledata = infiledataname->Getstring();
  std::string sinfilegoodness = infilegoodnessname->Getstring();
  delete flikelihood;
  file = new TFile(outfile,"recreate","Goodness Minimize ROOT File");
  infiledata = new MyString();
  infilegoodness = new MyString();
  infilelikelihood = new MyString();
  std::string sinfilelikelihood = cinfilelikelihood;
  infiledata->Setstring(sinfiledata);
  infiledata->SetName("infiledataname_bygoodnessminimize");
  infilegoodness->Setstring(sinfilegoodness);
  infilegoodness->SetName("infilegoodnessname_bygoodnessminimize");
  infilelikelihood->Setstring(sinfilelikelihood);
  infilelikelihood->SetName("infilelikelihoodname_bygoodnessminimize");
  goodnessminimizetree = new TTree("goodnessminimizeT","Goodness Minimize Data Tree");
  optiontree = new TTree("gmoptionT","GoodnessMinimizeOption Tree");
  data = new TReconstructdata_minimize();
  goodnessminimizetree->Branch("reconstructdataminimize",&data);
  option = new TOption_minimize();
  optiontree->Branch("option_minimize",&option);
  option->SetOption(optionin);
  optiontree->Fill();
}

void GoodnessMinimizeRunAction::EndOfAction(std::shared_ptr<Process>)
{
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  infiledata->Write();
  infilegoodness->Write();
  infilelikelihood->Write();
  file->Write();
  file->Close();
  delete data;
  delete option;
}

