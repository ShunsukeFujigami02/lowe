// c++ STL
#include <iostream>

// self-introduced library
#include "GoodnessManager.hh"

GoodnessManager* GoodnessManager::fgoodnessmanager = 0;

GoodnessManager::GoodnessManager(const char* infile){
  if(fgoodnessmanager){
    std::cout << "Error ! GoodnessManager constructed twice." << std::endl;
    throw "GoodnessManager::GoodnessManager";
  }
  fgoodnessmanager = this;
  file = new TFile(infile);
  wcsimT = (TTree*)file->Get("wcsimT");
  wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  nevent = wcsimT->GetEntries();
  goodnessrun = new GoodnessRun();
  goodnessrun->SetnumberOfEvent(nevent);
  std::cout << "input file data is below" << std::endl;
  file->Print();
  std::cout << nevent << "event exist" << std::endl;
}
GoodnessManager* GoodnessManager::GetGoodnessManager(){
  return fgoodnessmanager;
}

GoodnessManager::~GoodnessManager(){
  if(file){
    delete file;
  }
  if(wcsimrootevent){
    delete wcsimrootevent;
  }
  if(wcsimrootgeom){
    delete wcsimrootgeom;
  }
  if(goodnessrunaction)
    {
      delete goodnessrunaction;
    }
  if(goodnessrun)
    {
      delete goodnessrun;
    }
}

void GoodnessManager::Run(int Nevent){
  std::cout << Nevent << " event run start" << std::endl;
  goodnessrunaction->BeginOfRunAction(); 
  for(int i_event = 0;i_event < Nevent;i_event++){
    std::cout << "event" << i_event << " start" << std::endl;
    ProcessOneEvent(i_event);
    std::cout << "event" << i_event << " end" << std::endl;
  }
  goodnessrunaction->EndOfRunAction();
}

void GoodnessManager::SetParameters()
{
  goodnesseventmanager.SetParameters();
}


void GoodnessManager::ProcessOneEvent(int i_event){
  wcsimT->GetEntry(i_event);
  currentevent = new GoodnessEvent(i_event);
  goodnesseventmanager.ProcessOneEvent(currentevent);
  delete currentevent;
}

void GoodnessManager::SetGoodnessEventAction(GoodnessEventAction* goodnesseventaction_in)
{
  goodnesseventaction = goodnesseventaction_in;
  goodnesseventmanager.SetGoodnessEventAction(goodnesseventaction_in);
}

