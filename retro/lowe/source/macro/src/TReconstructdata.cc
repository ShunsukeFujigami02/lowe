#include "TReconstructdata.hh"

ClassImp(TReconstructdata)

ClassImp(TReconstructdata_minimize)

ClassImp(TReconstructhit)

TReconstructdata::TReconstructdata()
{
}

TReconstructdata::~TReconstructdata()
{
  fhit.clear();
  fhit.shrink_to_fit();
}

void TReconstructdata::addhit(int hittype)
{
  TReconstructhit hit(hittype);
  fhit.push_back(hit);
}

TReconstructhit& TReconstructdata::Gethit(int i)
{
  return fhit[i];
}

void TReconstructdata::Setdata(TReconstructdata data)
{
  vector = data.Get4Vector();
  direction = data.Getdirection();
  energy = data.Getenergy();
  goodness = data.Getgoodness();
  likelihood = data.Getlikelihood();
  likelihoodonretro = data.Getlikelihoodonretro();
  likelihoodnoretro = data.Getlikelihoodnoretro();
  fhit = data.Getvhit();
}

void TReconstructdata_minimize::Setdata(TReconstructdata_minimize data)
{
  nparameter = data.GetNParameters();
  parameters = data.parameters;
  ncalls = data.Getncalls();
  nIterations = data.GetnIterations();
  status = data.Getstatus();
}

