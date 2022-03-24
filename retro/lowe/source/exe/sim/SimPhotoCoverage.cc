#include "GeometryforPhotoCoverage.hh"


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

int main(int argc,char** argv)
{
}
void ProcessOneRun(double theta,double phi,TTree* tree)
{
  auto runManager = new G4RunManager;

  runManager->SetUserInitialization( new GeometryforPhotoCoverage );

  runManager->SetUserInitialization( new FTFP_BERT );

  runManager->SetUserInitialization( new UserActionInitialization);
  PhotoCoverageRunAction* myRunAction = new PhotoCoverageRunAction(tree);
  runManager->SetUserAction(myRunAction);
  runManager->Initialize();

  G4UImanager* UI = G$UImanager::GetUIpointer();
  double x = std::sin(theta)*std::cos(phi);
  double y = std::sin(theta)*std::sin(phi);
  double zminus = -std::cos(theta);
  UI->ApplyCommand("/gps/particle geantino");
  UI->ApplyCommand("/gps/energy 1.0 MeV");
  UI->ApplyCommand("/gps/pos/type Plane");
  UI->ApplyCommand("/gps/pos/shape Circle");
  UI->ApplyCommand("/gps/pos/centre 0 0 0 cm");
  UI->ApplyCommand("/gps/pos/radius 50 m");
  
  UI->ApplyCommand("/run/beamOn 10000");
  delete runManager;
}


  
