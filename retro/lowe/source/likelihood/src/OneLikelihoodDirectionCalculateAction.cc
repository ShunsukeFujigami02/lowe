#include "OneLikelihoodDirectionCalculateAction.hh"

void OneLikelihoodDirectionCalculateAction::EndOfEventAction(std::shared_ptr<Process> process)
{
  if(
  likelihooddirectioneventaction->onelikelihoodnoretro
