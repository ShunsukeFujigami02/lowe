#include "MinimizeRunAction.hh"

MinimizeRunAction::MinimizeRunAction(const char* outfile_in,const char* outtree_in):outfile(outfile_in),outtree(outtree_in)
{
}

void MinimizeRunAction::BeginOfAction(std::shared_ptr<Process>)
{
  file = new TFile(outfile,"recreate","Minimize ROOT File");
  minimizetree = new TTree(outtree,"Minimize Data Tree");
  data = new TReconstructdata_minimize();
  minimizetree->Branch("reconstructdataminimize",&data);
}

void MinimizeRunAction::EndOfAction(std::shared_ptr<Process>)
{
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  file->Write();
  file->Close();
  delete data;
}

