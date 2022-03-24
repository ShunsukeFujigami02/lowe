#include "MinimizeEventAction.hh"

void MinimizeEventAction::BeginOfAction(std::shared_ptr<Process>)
{
}


void MinimizeEventAction::EndOfAction(std::shared_ptr<Process> process)
{
  TReconstructdata_minimize data;
  data.SetNParameters(npar);
  data.SetParameters(process->GetMinimizer()->X());
  data.Setstatus(process->GetMinimizer()->Status());
  data.Setncalls(process->GetMinimizer()->NCalls());
  data.SetnIterations(process->GetMinimizer()->NIterations());
  TReconstructdata_minimize* datain = minimizerunaction->GetTReconstructdata_minimize();
  datain->Setdata(data);
  TTree* tree = minimizerunaction->GetTTree();
  tree->Fill();  
}
