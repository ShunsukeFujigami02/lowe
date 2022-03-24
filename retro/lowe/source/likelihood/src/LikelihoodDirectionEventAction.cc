#include <cmath>

#include "LikelihoodDirectionEventAction.hh"
#include "TReconstructdata.hh"
#include <TVector3.h>
#include <CLHEP/Vector/ThreeVector.h>

void LikelihoodDirectionEventAction::BeginOfAction(std::shared_ptr<Process>)
{
}

void LikelihoodDirectionEventAction::EndOfAction(std::shared_ptr<Process> process)
{
  TReconstructdata data;
  data.Setlikelihood(process->GetMaxlikelihood());
  CLHEP::Hep3Vector vector = process->GetMax3Direction();
  double costheta = vector.cosTheta();
  double theta = std::acos(costheta);
  double phi = vector.phi();
  TVector3 vector3;
  vector3.SetMagThetaPhi(1.,theta,phi);
  data.Setdirection(vector3);
  data.Getvhit() = std::vector<TReconstructhit>(process->Getncherenkovdigihits());
  for(int i = 0;i < process->Getncherenkovdigihits(); i++)
    {
      data.Gethit(i).Setonelikelihoodnoretro(process->maxonelikelihoodnoretro.at(i));
      data.Gethit(i).Setonelikelihoodonretro(process->maxonelikelihoodonretro.at(i));
    }
  TReconstructdata* datain = likelihooddirectionrunaction->GetLikelihoodDirectiondata();
  datain->Setdata(data);
  TTree* tree = likelihooddirectionrunaction->GetTTree();
  tree->Fill();
}

