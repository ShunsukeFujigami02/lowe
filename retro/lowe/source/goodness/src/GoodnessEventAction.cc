// ROOT library
#include <TTree.h>
#include <TLorentzVector.h>
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
// self-introduced library
#include "GoodnessEventAction.hh"
#include "GoodnessRunAction.hh"
#include "GoodnessEvent.hh"
#include "Reconstructdata.hh"
#include "AnalizedData.hh"

GoodnessEventAction::GoodnessEventAction(GoodnessRunAction* goodnessrunaction_in)
  :goodnessrunaction(goodnessrunaction_in)
{}

void GoodnessEventAction::BeginOfEventAction()
{
}


void GoodnessEventAction::EndOfEventAction(const GoodnessEvent* goodnessevent)
{
  TReconstructdata data;
  data.Setgoodness(goodnessevent->Getgoodness());
  CLHEP::HepLorentzVector vector = goodnessevent->Get4Vector();
  double x = vector.x();
  double y = vector.y();
  double z = vector.z();
  double t = vector.t();
  TLorentzVector vec(x,y,z,t);
  data.Set4Vector(vec);
  TReconstructdata* datain = GetRunAction()->GetReconstructdata();
  datain->Setdata(data);
  TTree* tree = GetRunAction()->GetTTree();
  tree->Fill();
}
