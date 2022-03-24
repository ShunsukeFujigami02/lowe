#ifndef ANALIZEFILEDATA_HH
#define ANALIZEFILEDATA_HH

#include <string>
#include <TFile.h>
#include <TTree.h>
#include <vector>
#include "hitinfo.hh"
#include "AnalizeFile.hh"
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "TReconstructdata.hh"


class AnalizeFiledata
{
public:
  AnalizeFiledata(){};
  AnalizeFiledata(AnalizeFile file);
  void Construct(AnalizeFile file);
  virtual ~AnalizeFiledata();
  AnalizeFiledata(const AnalizeFiledata& data) = delete;
  AnalizeFiledata(AnalizeFiledata&& data) = delete;
  AnalizeFiledata& operator=(const AnalizeFiledata& data) = delete;
  AnalizeFiledata& operator=(AnalizeFiledata&& data) = delete;
  int GetEntriesMin();
  void GetEntry(int ievent);
  static int number;
  TFile* fwcsim = nullptr;
  TTree* wcsimT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  TTree* goodnessT = nullptr;
  TFile* fgoodness = nullptr;
  TReconstructdata* reconstructdata = nullptr;
  TFile* flikelihood = nullptr;
  TTree* likelihoodT = nullptr;
  TReconstructdata* reconstructdatalikelihood = nullptr;
  TFile* fminimize = nullptr;
  TTree* minimizeT = nullptr;
  TReconstructdata_minimize* reconstructdataminimize = nullptr;
  TFile* fNearPMT = nullptr;
  TTree* tNearPMT = nullptr;
  std::vector<int>* iNearPMT = nullptr;
  TBranch* biNearPMT = nullptr;
  std::vector<std::vector<int>> vecNearPMT;
  TFile* feffN = nullptr;
  TTree* effNT = nullptr;
  double effNdirect;
  double effNreflect;
  std::vector<hitinfo> allhitinfo;
};

#endif
