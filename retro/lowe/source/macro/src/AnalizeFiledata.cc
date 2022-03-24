#include "AnalizeFiledata.hh"
#include <iostream>

int AnalizeFiledata::number = 0;

AnalizeFiledata::AnalizeFiledata(AnalizeFile file){
  if(number != 0){
    std::cout << "AnalizeFiledata is already exist!" << std::endl;
    throw "AnalizeFiledata::AnalizeFiledata(AnalizeFile file)";
  }
  number = 1;
  Construct(file);
}

void AnalizeFiledata::Construct(AnalizeFile file){
  if(file.fileroot.find("wcsim") != std::string::npos){
    if(!fwcsim)
      fwcsim = new TFile(file.fileroot.c_str());
    else{
      std::cout << "fwcsim is already exist." << std::endl;
      throw "void AnalizeFiledata::Construct(AnalizeFile file)";
    }
    wcsimT = (TTree*)fwcsim->Get("wcsimT");
    wcsimrootevent = new WCSimRootEvent();
    wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
    wcsimGeoT = (TTree*)fwcsim->Get("wcsimGeoT");
    wcsimrootgeom = new WCSimRootGeom();
    wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
    wcsimGeoT->GetEntry(0);
  }
  if(file.fileroot.find("Goodness") != std::string::npos){
    if(!fgoodness)
      fgoodness = new TFile(file.fileroot.c_str());
    else{
      std::cout << "fgoodness is already exist." << std::endl;
      throw "void AnalizeFiledata::Construct(AnalizeFile file)";
    }
    goodnessT = (TTree*)fgoodness->Get("goodnessT");
    reconstructdata = new TReconstructdata();
    goodnessT->SetBranchAddress("reconstructdata",&reconstructdata);
  }
  if(file.fileroot.find("Likelihood") != std::string::npos){
    if(!flikelihood)
      flikelihood = new TFile(file.fileroot.c_str());
    else{
      std::cout << "flikelihood is already exist." << std::endl;
      throw "void AnalizeFiledata::Construct(AnalizeFile file)";
    }
    likelihoodT = (TTree*)flikelihood->Get("likelihoodT");
    reconstructdatalikelihood = new TReconstructdata();
    likelihoodT->SetBranchAddress("reconstructdatalikelihood",&reconstructdatalikelihood);
  }
  if(file.fileroot.find("Minimize") != std::string::npos){
    if(!fminimize)
      fminimize = new TFile(file.fileroot.c_str());
    else{
      std::cout << "fminimize is already exist." << std::endl;
      throw "void AnalizeFiledata::Construct(AnalizeFile file)";
    }
    minimizeT = (TTree*)fminimize->Get("minimizeT");
    reconstructdataminimize = new TReconstructdata_minimize();
    minimizeT->SetBranchAddress("reconstructdataminimize",&reconstructdataminimize);
  }
  if(file.fileroot.find("Energy") != std::string::npos){
    if(!feffN)
      feffN = new TFile(file.fileroot.c_str());
    else{
      std::cout << "feffN is already exist," << std::endl;
      throw "void AnalizeFiledata::Construct(AnalizeFile file)";
    }
    effNT = (TTree*)feffN->Get("effNT");
    effNT->SetBranchAddress("effNdir",&effNdirect);
    effNT->SetBranchAddress("effNref",&effNreflect);
  }
  if(wcsimrootevent){
    if(!fNearPMT){
      fNearPMT = new TFile("/rhome/fujigami/retro/lowe/NearPMT.root");
      tNearPMT = (TTree*)fNearPMT->Get("NearPMT");
      tNearPMT->SetBranchAddress("iNearPMT",&iNearPMT,&biNearPMT);
      int tubenum = wcsimrootgeom->GetWCNumPMT();
      for(int i = 0;i < tubenum;i++){
	tNearPMT->GetEntry(i);
	vecNearPMT.push_back(*iNearPMT);
      }
    }
  }
  for(auto iter = file.originfiles.begin();iter != file.originfiles.end();iter++)
    {
      Construct((*iter));
    }
}

AnalizeFiledata::~AnalizeFiledata(){
  if(fwcsim)
    fwcsim->Close();
 if(wcsimrootevent)
    delete wcsimrootevent;
  if(wcsimrootgeom)
    delete wcsimrootgeom;
  if(fgoodness)
    fgoodness->Close();
  if(reconstructdata)
    delete reconstructdata;
  if(flikelihood)
    flikelihood->Close();
  if(reconstructdatalikelihood)
    delete reconstructdatalikelihood;
  if(fminimize)
    fminimize->Close();
  if(reconstructdataminimize)
    delete reconstructdataminimize;
  if(feffN)
    feffN->Close();
  if(fNearPMT){
    fNearPMT->Close();
    vecNearPMT.shrink_to_fit();
  }
  number = 0;
}

int AnalizeFiledata::GetEntriesMin(){
  if(feffN){
    return effNT->GetEntries();
  }
  if(fminimize){
    return minimizeT->GetEntries();
  }
  if(flikelihood){
    return likelihoodT->GetEntries();
  }
  if(fgoodness){
    return goodnessT->GetEntries();
  }
  if(fwcsim){
    return wcsimT->GetEntries();
  }
  return 0;
}

void AnalizeFiledata::GetEntry(int ievent){
  if(fwcsim)
    wcsimT->GetEntry(ievent);
  if(fgoodness)
    goodnessT->GetEntry(ievent);
  if(flikelihood)
    likelihoodT->GetEntry(ievent);
  if(fminimize)
    minimizeT->GetEntry(ievent);
  if(feffN)
    effNT->GetEntry(ievent);
  allhitinfo.clear();
  int ncherenkovdigihits = wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  for(int i = 0;i < ncherenkovdigihits;i++){
    WCSimRootCherenkovDigiHit* h = (WCSimRootCherenkovDigiHit*)wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(i);
    hitinfo info;
    info.Sethit(h,wcsimrootgeom);
    allhitinfo.emplace_back(info);
  }
}
