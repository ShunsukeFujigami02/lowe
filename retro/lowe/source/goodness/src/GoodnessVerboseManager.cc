#include "GoodnessVerboseManager.hh"

GoodnessVerboseManager::GoodnessVerboseManager(const char* infiledata,const char* infilegoodness)
  :ProcessManager()
{
  dfile = new TFile(infiledata);
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  gfile = new TFile(infilegoodness,"update");
  goodnessT = (TTree*)gfile->Get("goodnessT");
  reconstructdata = new TReconstructdata();
  goodnessT->SetBranchAddress("reconstructdata",&reconstructdata);
  reconstructdataverbose = new TReconstructdata();
  branch = goodnessT->Branch("reconstructdataverbose",&reconstructdataverbose);
  reconstructdataverbose->Setdata(*reconstructdata);
  Nevents = goodnessT->GetEntries();
  std::cout << "inputfile data is below" << std::endl;
  dfile->Print();
  gfile->Print();
  std::cout << Nevents << "event exist" << std::endl;
}

GoodnessVerboseManager::~GoodnessVerboseManager()
{
  if(dfile)
    delete dfile;
  if(wcsimrootevent)
    delete wcsimrootevent;
  if(wcsimrootgeom)
    delete wcsimrootgeom;
  if(gfile)
    delete gfile;
  if(reconstructdata)
    delete reconstructdata;
  if(reconstructdataverbose)
    delete reconstructdataverbose;
}

void GoodnessVerboseManager::ProcessOneEvent(int i)
{
  wcsimT->GetEntry(i);
  goodnessT->GetEntry(i);
  reconstructdataverbose->Setdata(*reconstructdata);
  double x = reconstructdata->Get4Vector().X();
  double y = reconstructdata->Get4Vector().Y();
  double z = reconstructdata->Get4Vector().Z();
  double t = reconstructdata->Get4Vector().T();
  CLHEP::HepLorentzVector fitted4vector;
  fitted4vector.set(x,y,z,t);
  currentprocess->Setfitted4Vector(fitted4vector);
  nextmanager->ProcessOne(currentprocess);
  std::cout << "number of hit is " << reconstructdataverbose->Getvhit().size() << std::endl;
  branch->Fill();
  goodnessT->Write("",TObject::kOverwrite);
}

