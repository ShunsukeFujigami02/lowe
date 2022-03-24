// c++ STL
#include <iostream>
// ROOT library
#include <TFile.h>
// self-introduced library
#include "GoodnessRunAction.hh"
#include "CSearch_range.hh"
#include "GoodnessManager.hh"

GoodnessRunAction::GoodnessRunAction(const char* outfile_in)
  :outfile(outfile_in)
{
}

  

void GoodnessRunAction::BeginOfRunAction(){
  file = new TFile(outfile,"recreate","Goodness ROOT File");
  goodnesstree = new TTree("goodnessT","GoodnessData Tree");
  data = new TReconstructdata();
  goodnesstree->Branch("reconstructdata",&data);
}

void GoodnessRunAction::EndOfRunAction(){
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  file->Write();
  file->Close();
  delete data;
}
