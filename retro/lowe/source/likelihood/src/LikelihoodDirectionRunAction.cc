#include <iostream>
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRunAction.hh"

LikelihoodDirectionRunAction::LikelihoodDirectionRunAction(const char* outfile_in)
  :outfile(outfile_in)
{
}


void LikelihoodDirectionRunAction::BeginOfAction(std::shared_ptr<Process>)
{
  file = new TFile(outfile,"recreate","Likelihood ROOT File");
  likelihoodtree = new TTree("likelihoodT","LikelihoodData Tree");
  data = new TReconstructdata();
  likelihoodtree->Branch("reconstructdatalikelihood",&data);
}
void LikelihoodDirectionRunAction::EndOfAction(std::shared_ptr<Process>)
{
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  file->Write();
  file->Close();
  delete data;
}

