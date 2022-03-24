#include "GoodnessMinimizeEventAction.hh"

void GoodnessMinimizeEventAction::BeginOfAction(std::shared_ptr<Process>)
{
}

void GoodnessMinimizeEventAction::EndOfAction(std::shared_ptr<Process> process)
{
  TReconstructdata_minimize data;
  TLorentzVector vec(process->Getfitted4Vector().x(),process->Getfitted4Vector().y(),process->Getfitted4Vector().z(),process->Getfitted4Vector().t());
  data.Set4Vector(vec);
  TVector3 dir(process->GetCurrent3Direction().x(),process->GetCurrent3Direction().y(),process->GetCurrent3Direction().z());
  data.Setdirection(dir);
  data.Setstatus(process->Getminimizestatus());
  data.Setncalls(process->Getminimizencalls());
  data.SetnIterations(process->GetminimizenIterations());
  TReconstructdata_minimize* datain = goodnessminimizerunaction->GetTReconstructdata_minimize();
  datain->Setdata(data);
  TTree* tree = goodnessminimizerunaction->GetTTree();
  tree->Fill();
}

