// STL
#include <string>
#include <iostream>
#include <vector>
// ROOT
#include <TH2D.h>
#include <TFile.h>
// self
#include "MinimizedFunction.hh"
#include "fmath.hpp"
#include "rotation3D.hh"

MinimizedFunction::MinimizedFunction(const char* funcname,AnalizeFile file,AnalizeFiledata* data,int paranumber)
{
  (*this).file = file;
  (*this).data = data;
  (*this).paranum = paranumber;
  (*this).funcname = funcname;
  double darkrate;
  file.GetTagdouble("DarkRate",darkrate);
  double NPMT = data->wcsimrootgeom->GetWCNumPMT();
  double triggerprewindow;
  double triggerpostwindow;
  file.GetTagdouble("TriggerPreWindow",triggerprewindow);
  file.GetTagdouble("TriggerPostWindow",triggerpostwindow);
  expecteddarkhit = darkrate*(triggerpostwindow - triggerprewindow)*NPMT/1000000.;
  double reflectivity = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  conretro = 0.74265 + 2.64586* reflectivity - 1.01048 * reflectivity * reflectivity;
}

double MinimizedFunction::returnvalue(const double* a)
{
  std::vector<double> avec;
  for(int i = 0;i < paranum;i++){
    avec.emplace_back(a[i]);
  }
  return returnvaluecontents(avec);
}

double MinimizedFunction::returnvaluecontents(std::vector<double> a){
  double x = a[0];
  double y = a[1];
  double z = a[2];
  double t = a[3];
  double costheta = a[4];
  double phi = a[5];
  double k = 0.;
  if(paranum = 7)
    k = a[6];
  if(funcname == "minimizedfuncnoretroadddarkratenumaddacceptancever2")
    return minimizedfuncnoretroadddarkratenumaddacceptancever2(x,y,z,t,costheta,phi,k);
  if(funcname == "minimizedfunconretroadddarkratenumaddacceptance")
    return minimizedfunconretroadddarkratenumaddacceptance(x,y,z,t,costheta,phi,k);
  if(funcname == "minimizedfunconretroadddarkratenumaddacceptancereflectpart")
    return minimizedfunconretroadddarkratenumaddacceptancereflectpart(x,y,z,t,costheta,phi,k);
  if(funcname == "goodnessnoretro")
    return goodnessnoretro(x,y,z,t);
  if(funcname == "goodnesscomparenodigitalver2")
    return goodnesscomparenodigitalver2(x,y,z,t);
  if(funcname == "goodnesscomparenodigitalver2retroonly")
    return goodnesscomparenodigitalver2(x,y,z,t,"retroonly");
  if(funcname == "goodnesscomparenodigitalver2directonly")
    return goodnesscomparenodigitalver2(x,y,z,t,"directonly");
  if(funcname == "goodnesscomparenodigitalver2retroonlytrueretrolike")
    return goodnesscomparenodigitalver2(x,y,z,t,"retroonlytrueretrolike");
  if(funcname == "goodnesscomparenodigitalver2retroonlytruedirectlike")
    return goodnesscomparenodigitalver2(x,y,z,t,"retroonlytruedirectlike");
  if(funcname == "goodnesscomparenodigitalver2directonlytrueretrolike")
    return goodnesscomparenodigitalver2(x,y,z,t,"directonlytrueretrolike");
  if(funcname == "goodnesscomparenodigitalver2directonlytruedirectlike")
    return goodnesscomparenodigitalver2(x,y,z,t,"directonlytruedirectlike");
  if(funcname == "goodnesscomparenodigitalver2truedirectlike")
    return goodnesscomparenodigitalver2(x,y,z,t,"truedirectlike");
  if(funcname == "goodnesscomparenodigitalver2trueretrolike")
    return goodnesscomparenodigitalver2(x,y,z,t,"trueretrolike");
  if(funcname == "likelihooddirectionsum")
    return likelihooddirectionsum(x,y,z,t,costheta,phi);
  if(funcname == "likelihooddirectionsumminus")
    return -likelihooddirectionsum(x,y,z,t,costheta,phi);
  if(funcname == "likelihooddirectionsumdirectonly")
    return likelihooddirectionsum(x,y,z,t,costheta,phi,"directonly");
  if(funcname == "likelihooddirectionsumdirectonlyminus")
    return -likelihooddirectionsum(x,y,z,t,costheta,phi,"directonly");
  if(funcname == "likelihooddirectionsumretroonly")
    return likelihooddirectionsum(x,y,z,t,costheta,phi,"retroonly");
  if(funcname == "likelihooddirectionsumretroonlyminus")
    return -likelihooddirectionsum(x,y,z,t,costheta,phi,"retroonly");
  if(funcname == "effectiveReflectivity")
    return effectiveReflectivity(x,y,z,costheta,phi);
  if(funcname == "effectiveReflectivityBroad")
    return effectiveReflectivityBroad(x,y,z,costheta,phi);
  if(funcname == "effectiveReflectivityConsiderCoverage")
    return effectiveReflectivityConsiderCoverage(x,y,z,costheta,phi);
  std::cout << "funcname " << funcname << " is not valid." << std::endl;
  throw "double MinimizedFunction::returnvalue(const double* a)";
}

double MinimizedFunction::returnvaluecontentshit(std::vector<double> a,int ihit){
  double x = a[0];
  double y = a[1];
  double z = a[2];
  double t = a[3];
  double costheta = a[4];
  double phi = a[5];
  double k = 0.;
  if(paranum = 7)
    k = a[6];
  if(funcname == "pdir"){
    return pdir(x,y,z,t,costheta,phi,k,ihit);
  }
  if(funcname == "pref"){
    return pref(x,y,z,t,costheta,phi,k,ihit);
  }
  if(funcname == "pdark"){
    return pdark(k);
  }
  if(funcname == "pdirtime"){
    return pdirtime(x,y,z,t,k,ihit);
  }
  if(funcname == "preftime"){
    return preftime(x,y,z,t,k,ihit);
  }
  if(funcname == "ReflectCoverage"){
    return ReflectCoverage(x,y,z,ihit);
  }
  std::cout << "funcname " << funcname << " is not valid." << std::endl;
  throw "double MinimizedFunction::returnvaluecontentsevent(std::vector<double> a,int ievent)";
}
std::vector<double> MinimizedFunction::Getfirstvalue(){
  std::vector<double> firstvalue;
  if(data->reconstructdata){
    firstvalue.emplace_back(data->reconstructdata->Get4Vector().X());
    firstvalue.emplace_back(data->reconstructdata->Get4Vector().Y());
    firstvalue.emplace_back(data->reconstructdata->Get4Vector().Z());
    firstvalue.emplace_back(data->reconstructdata->Get4Vector().T());
  }
  else{
    firstvalue.emplace_back(0.);
    firstvalue.emplace_back(0.);
    firstvalue.emplace_back(0.);
    firstvalue.emplace_back(0.);
  }
  if(paranum > 4){
    if(data->reconstructdatalikelihood){
      firstvalue.emplace_back(data->reconstructdatalikelihood->Getdirection().CosTheta());
      firstvalue.emplace_back(data->reconstructdatalikelihood->Getdirection().Phi());
    }
    else{
      firstvalue.emplace_back(0.);
      firstvalue.emplace_back(0.);
    }
  }
  if(paranum == 7)
    firstvalue.emplace_back(expecteddarkhit);
  return firstvalue;
}

void MinimizedFunction::SetEventNumber(int n)
{
  data->GetEntry(n);
  allhitinfo = data->allhitinfo;
}

double MinimizedFunction::GetTruevalue(int parnumin){
  if(parnumin < 3){
    return data->wcsimrootevent->GetTrigger(0)->GetVtx(parnumin);
  }
  if(parnumin == 3){
    return -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
  }
  if(parnumin == 4){
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    CLHEP::Hep3Vector direction(track->GetPdir(0),track->GetPdir(1),track->GetPdir(2));
    return direction.cosTheta();
  }
  if(parnumin == 5){
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    CLHEP::Hep3Vector direction(track->GetPdir(0),track->GetPdir(1),track->GetPdir(2));
    return direction.phi();
  }
  if(parnumin == 6){
    return expecteddarkhit;
  }
  return 0;
}

double MinimizedFunction::goodnessnoretro(double x,double y,double z,double t){
  double sigma = 5.;
  file.GetTagdouble("GoodnessSigma",sigma);
  double g = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    double distance = distancefunction(info,x,y,z,"distance_position_pmt");
    CLHEP::Hep3Vector threevec(x,y,z);
    double tofvalue = info.HitTime() - offset - (distance - doffset)/v_light_in_water;
    double toferror = tofvalue - t;
    g += fmath::expd(-0.5*(toferror/sigma)*(toferror/sigma));
  }
  return g;
}

double MinimizedFunction::goodnesscomparenodigitalver2(double x,double y,double z,double t,std::string cut){
  double sigma = 5.;
  file.GetTagdouble("GoodnessSigma",sigma);
  double g = 0.;
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    CLHEP::Hep3Vector vectrue;
    vectrue.setRThetaPhi(1.,std::acos(GetTruevalue(4)),GetTruevalue(5));
    CLHEP::Hep3Vector vechit = info.Get3Position() - CLHEP::Hep3Vector(GetTruevalue(0),GetTruevalue(1),GetTruevalue(2));
    double anglecos = vectrue.cosTheta(vechit);
    if((cut == "retroonlytrueretrolike") || (cut == "trueretrolike") || (cut == "directonlytrueretrolike")){
      if(anglecos > 0.)
	continue;
    }
    double distancenoretro = distancefunction(info,x,y,z,"distance_position_pmt");
    double tofvaluenoretro = info.HitTime() - offset - (distancenoretro - doffset)/v_light_in_water;
    double toferrornoretro = tofvaluenoretro - t;
    double gnoretro = 4.05643*fmath::expd(-0.5*(toferrornoretro/sigma)*(toferrornoretro/sigma));
    double distanceonretro = distancefunction(info,x,y,z,"distance_fly_retro");
    double tofvalueonretro = info.HitTime() - offset - (distanceonretro - doffset)/v_light_in_water;
    double toferroronretro = tofvalueonretro - t;
    double gonretro = conretro* fmath::expd(-0.5*(toferroronretro/sigma)*(toferroronretro/sigma));
    if((cut == "retroonlytrueretrolike") || (cut == "trueretrolike") || (cut == "directonlytrueretrolike")){
      if(anglecos > 0.)
	continue;
      if(std::abs(toferroronretro) > 20.)
	continue;
    }
    if((cut == "retroonlytruedirectlike") || (cut == "truedirectlike") || (cut == "directonlytruedirectlike")){
      if(anglecos < 0.)
	continue;
      if(std::abs(toferrornoretro) > 20.)
	continue;
    }
    if(gnoretro > gonretro)
      {
	if((cut == "retroonly") || (cut == "retroonlytrueretrolike") || (cut == "retroonlytruedirectlike")){}
	else{
	  g += gnoretro;
	}
      }
    else
      {
	if((cut == "directonly") || (cut == "directonlytrueretrolike") || (cut == "directonlytruedirectlike")){}
	else{
	  g += gonretro;
	}
      }
  }
  return g;
}

double MinimizedFunction::likelihooddirectionsum(double x,double y,double z,double t,double costheta,double phi,std::string cut)
{
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double l = 0.;
  for(int i = 0;i < ncherenkovdigihits;i++)
    {
     hitinfo info = allhitinfo[i];
     double costhetapmt = pmtcostheta(info,x,y,z);
     if(costhetapmt < 0.){
       costhetapmt = 0.;
     }
     double distancenoretro = distancefunction(info,x,y,z,"distance_position_pmt");
     double tofvaluenoretro = info.HitTime() - offset - (distancenoretro - doffset)/v_light_in_water;
     double toferrornoretro = tofvaluenoretro - t;
     if((std::abs(toferrornoretro) < 10.) && ((cut == "default") || (cut == "directonly")))
       {
	 l += std::log(cherenkovanglefunc(info,x,y,z,costheta,phi,"likelihoodfdirectionnoretro"))*costhetapmt;
       }
     double distanceonretro = distancefunction(info,x,y,z,"distance_fly_retro");
     double tofvalueonretro = info.HitTime() - offset - (distanceonretro - doffset)/v_light_in_water;
     double toferroronretro = tofvalueonretro - t;
     if((std::abs(toferroronretro) < 10.) && ((cut == "default") || (cut == "retroonly")))
       {
	 l += std::log(cherenkovanglefunc(info,x,y,z,costheta,phi,"likelihoodfdirectiononretro"))*costhetapmt;
       }
    }
  return l;
}
double MinimizedFunction::minimizedfuncnoretroadddarkratenumaddacceptancever2(double x,double y,double z,double t,double costheta,double phi,double k)
{
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double l = 0.;
  double costhetafixed = costheta;
  double phifixed = phi;
  if((costheta > 1.) && (costheta < 3.)){
    costhetafixed = 2 - costheta;
    phifixed = phi + PI;
  }
  else if((costheta < -1.) && (costheta > -3.)){
    costhetafixed = -2 - costheta;
    phifixed = phi + PI;
  }
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    double costhetapmt = pmtcostheta(info,x,y,z);
    if(costhetapmt < 0.){
      costhetapmt = 0.;
    }
    l += std::log(hitnumexpected* toferrorfunc(info,x,y,z,t,"nodarkratever2","distance_position_pmt") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkratever2") * costhetapmt + k * 3.3229e-8/2.);
  }
  if(ncherenkovdigihits != 0){
    double lgamma = 1.;
    lgamma = std::lgamma(k+1);
    l += (-expecteddarkhit + k*std::log(expecteddarkhit) - lgamma);
  }
  return -l;
}

double MinimizedFunction::minimizedfunconretroadddarkratenumaddacceptance(double x,double y,double z,double t,double costheta,double phi,double k)
{
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  double l = 0.;
  double costhetafixed = costheta;
  double phifixed = phi;
  if((costheta > 1.) && (costheta < 3.)){
    costhetafixed = 2 - costheta;
    phifixed = phi + PI;
  }
  else if((costheta < -1.) && (costheta > -3.)){
    costhetafixed = -2 - costheta;
    phifixed = phi + PI;
  }
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    double costhetapmt = pmtcostheta(info,x,y,z);
    if(costhetapmt < 0.){
      costhetapmt = 0.;
    }
    l += std::log(hitnumexpected* (toferrorfunc(info,x,y,z,t,"nodarkrateOnretroDir","distance_position_pmt") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroDir") + toferrorfunc(info,x,y,z,t,"nodarkrateOnretroRef","distance_fly_retro") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroRef"))* costhetapmt + k * 3.3229e-8/2.);
  }
  if(ncherenkovdigihits != 0){
    double lgamma = 1.;
    lgamma = std::lgamma(k+1);
    l += (-expecteddarkhit + k*std::log(expecteddarkhit) - lgamma);
  }
  return -l;
}

double MinimizedFunction::pdir(double x,double y,double z,double t,double costheta,double phi,double k,int ihit){
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  double costhetafixed = costheta;
  double phifixed = phi;
  if((costheta > 1.) && (costheta < 3.)){
    costhetafixed = 2 - costheta;
    phifixed = phi + PI;
  }
  else if((costheta < -1.) && (costheta > -3.)){
    costhetafixed = -2 - costheta;
    phifixed = phi + PI;
  }
  hitinfo info = allhitinfo[ihit];
  double costhetapmt = pmtcostheta(info,x,y,z);
  if(costhetapmt < 0.){
    costhetapmt = 0.;
  }
  return hitnumexpected*toferrorfunc(info,x,y,z,t,"nodarkrateOnretroDir","distance_position_pmt") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroDir")*costhetapmt;
}

double MinimizedFunction::pref(double x,double y,double z,double t,double costheta,double phi,double k,int ihit){
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  double costhetafixed = costheta;
  double phifixed = phi;
  if((costheta > 1.) && (costheta < 3.)){
    costhetafixed = 2 - costheta;
    phifixed = phi + PI;
  }
  else if((costheta < -1.) && (costheta > -3.)){
    costhetafixed = -2 - costheta;
    phifixed = phi + PI;
  }
  hitinfo info = allhitinfo[ihit];
  double costhetapmt = pmtcostheta(info,x,y,z);
  if(costhetapmt < 0.){
    costhetapmt = 0.;
  }
  return hitnumexpected*toferrorfunc(info,x,y,z,t,"nodarkrateOnretroRef","distance_fly_retro") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroRef")*costhetapmt;
}

double MinimizedFunction::pdark(double k){
  return k * 3.3229e-8/2.;
}

double MinimizedFunction::pdirtime(double x,double y,double z,double t,double k,int ihit){
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  hitinfo info = allhitinfo[ihit];
  double tof = hitnumexpected*toferrorfunc(info,x,y,z,t,"nodarkrateOnretroDirsingle","distance_position_pmt");
  return tof;
}

double MinimizedFunction::preftime(double x,double y,double z,double t,double k,int ihit){
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  hitinfo info = allhitinfo[ihit];
  double tof = hitnumexpected*toferrorfunc(info,x,y,z,t,"nodarkrateOnretroRefsingle","distance_fly_retro");
  return tof;
}

double MinimizedFunction::minimizedfunconretroadddarkratenumaddacceptancereflectpart(double x,double y,double z,double t,double costheta,double phi,double k)
{
  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
  double reflectivity = 0.;
  if(!file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity)){
    std::cout << "Tag ReflectivityFactorTrapezoidReflectivity is not exist." << std::endl;
  }
  retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312;
  double l = 0.;
  double costhetafixed = costheta;
  double phifixed = phi;
  if((costheta > 1.) && (costheta < 3.)){
    costhetafixed = 2 - costheta;
    phifixed = phi + PI;
  }
  else if((costheta < -1.) && (costheta > -3.)){
    costhetafixed = -2 - costheta;
    phifixed = phi + PI;
  }
  double hitnumexpected = ncherenkovdigihits - k;
  if(hitnumexpected < 1.){
    hitnumexpected = 1.;
  }
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    double costhetapmt = pmtcostheta(info,x,y,z);
    if(costhetapmt < 0.){
      costhetapmt = 0.;
    }
    l += std::log(hitnumexpected* (toferrorfunc(info,x,y,z,t,"nodarkrateOnretroDir","distance_position_pmt") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroDir") + toferrorfunc(info,x,y,z,t,"nodarkrateOnretroRef","distance_fly_retro") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroRef"))* costhetapmt + k * 3.3229e-8/2.);

  }
  if(ncherenkovdigihits != 0){
    double lgamma = 1.;
    lgamma = std::lgamma(k+1);
    l += (-expecteddarkhit + k*std::log(expecteddarkhit) - lgamma);
  }
  for(int i = 0;i < ncherenkovdigihits;i++){
    hitinfo info = allhitinfo[i];
    double costhetapmt = pmtcostheta(info,x,y,z);
    if(costhetapmt < 0.){
      costhetapmt = 0.;
    }
    l -= std::log(hitnumexpected* (toferrorfunc(info,x,y,z,t,"nodarkrateOnretroDir","distance_position_pmt") * cherenkovanglefunc(info,x,y,z,costhetafixed,phifixed,"nodarkrateOnretroDir"))* costhetapmt + k * 3.3229e-8/2.);
  }
  if(ncherenkovdigihits != 0){
      double lgamma = 1.;
      lgamma = std::lgamma(k+1);
      l -= (-expecteddarkhit + k*std::log(expecteddarkhit) - lgamma);
  }
  return l;
}

double MinimizedFunction::toferrorfunc(hitinfo info,double x,double y,double z,double t,std::string toferrorfuncname,std::string distancefuncname){
  double distance = distancefunction(info,x,y,z,distancefuncname);
  double tofvalue = info.HitTime() - offset - (distance - doffset)/v_light_in_water;
  double toferror = tofvalue - t;
  if(toferrorfuncname == "nodarkratever2"){
    if(toferror < -10.){
      return fmath::expd(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 - 1.84068658236999205e+01);
    }
    else if(toferror < 10.){
      double s = (toferror - 2.35177e-01)/1.24789e+01;
      return fmath::expd(1.12652e+01* fmath::expd(-s*s/2.) -1.84068658236999205e+01);
    }
    else if(toferror < 70.){
      return fmath::expd(fmath::expd(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - fmath::expd(-4.34364e-02 * (10. - 1.80667e+01)) - 1.84068658236999205e+01);
    }
    else if(toferror < 150.){
      return fmath::expd(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. - 1.84068658236999205e+01);
    }
    else{
      return fmath::expd(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 - 1.84068658236999205e+01);
    }
  }
  else if(toferrorfuncname == "nodarkrateOnretroDir"){
    double I = 9.34201880158831715e+05;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double sfactor = std::log((1/I)*std::sqrt((1-retroratio)/NPMT));
    if(toferror < -10.){
      return fmath::expd(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor);
    }
    else if(toferror < 10.){
      double s = (toferror - 2.35177e-01)/1.24789e+01;
      return fmath::expd(1.12652e+01* fmath::expd(-s*s/2.) + sfactor);
    }
    else if(toferror < 70.){
      return fmath::expd(fmath::expd(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - fmath::expd(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor);
    }
    else if(toferror < 150.){
      return fmath::expd(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor);
    }
    else{
      return fmath::expd(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor);
    }
  }
  else if(toferrorfuncname == "nodarkrateOnretroDirsingle"){
    double I = 9.34201880158831715e+05;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double sfactor = std::log((1/I)*(1-retroratio)/NPMT);
    if(toferror < -10.){
      return fmath::expd(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor);
    }
    else if(toferror < 10.){
      double s = (toferror - 2.35177e-01)/1.24789e+01;
      return fmath::expd(1.12652e+01* fmath::expd(-s*s/2.) + sfactor);
    }
    else if(toferror < 70.){
      return fmath::expd(fmath::expd(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - fmath::expd(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor);
    }
    else if(toferror < 150.){
      return fmath::expd(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor);
    }
    else{
      return fmath::expd(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor);
    }
  }
  else if(toferrorfuncname == "nodarkrateOnretroRef"){
    double I = 9.34201880158831715e+05;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double sfactor = std::log((1/I)*std::sqrt((retroratio)/NPMT));
    if(toferror < -10.){
      return fmath::expd(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor);
    }
    else if(toferror < 10.){
      double s = (toferror - 2.35177e-01)/1.24789e+01;
      return fmath::expd(1.12652e+01* fmath::exp(-s*s/2.) + sfactor);
    }
    else if(toferror < 70.){
      return fmath::expd(fmath::expd(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - fmath::expd(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor);
    }
    else if(toferror < 150.){
      return fmath::expd(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor);
    }
    else{
      return fmath::expd(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor);
    }
  }
  else if(toferrorfuncname == "nodarkrateOnretroRefsingle"){
    double I = 9.34201880158831715e+05;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double sfactor = std::log((1/I)*(retroratio)/NPMT);
    if(toferror < -10.){
      return fmath::expd(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor);
    }
    else if(toferror < 10.){
      double s = (toferror - 2.35177e-01)/1.24789e+01;
      return fmath::expd(1.12652e+01* fmath::exp(-s*s/2.) + sfactor);
    }
    else if(toferror < 70.){
      return fmath::expd(fmath::expd(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - fmath::expd(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor);
    }
    else if(toferror < 150.){
      return fmath::expd(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor);
    }
    else{
      return fmath::expd(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor);
    }
  }
  std::cout << "invalid toferrorfuncname " << toferrorfuncname << std::endl;
  throw "double MinimizedFunction::toferrorfunc(hitinfo info,double x,double y,double z,double t,std::string toferrorfuncname,std::string distancefuncname)";
}

double MinimizedFunction::distancefunction(hitinfo info,double xin,double yin,double zin,std::string distancefuncname){
  if(distancefuncname == "distance_position_pmt"){
    CLHEP::Hep3Vector pmtposition = info.Get3Position();
    CLHEP::Hep3Vector position (xin,yin,zin);
    CLHEP::Hep3Vector p_p = pmtposition - position;
    return p_p.mag();
  }
  if(distancefuncname == "distance_position_retro"){
    double pmtX = info.Get3Position().x();
    double pmtY = info.Get3Position().y();
    double pmtZ = info.Get3Position().z();
    double WCradius = info.GetWCradius();
    double WClength = info.GetWClength();
    double half_WClength = WClength/2.;
    double a = (pmtX-xin)*(pmtX-xin)+(pmtY-yin)*(pmtY-yin);
    double b = xin*(xin-pmtX)+yin*(yin-pmtY);
    double c = xin*xin+yin*yin-WCradius*WCradius;
    double t;
    if(a != 0){
      t = (b-sqrt(b*b-a*c))/a;
    }
    else{
      t = -c/(2*b);
    }
    double z = zin + (pmtZ - zin)*t;
    if(-half_WClength < z && half_WClength > z){
      
    }
    else if(z > half_WClength){
      t = (half_WClength - zin)/(pmtZ-zin);
      z = half_WClength;
    }
    else{
      t = (-half_WClength - zin)/(pmtZ-zin);
      z = - half_WClength;
    }
    double x = xin + (pmtX-xin)*t;
    double y = yin + (pmtY-yin)*t;
    double d2 = std::sqrt((xin-x)*(xin-x)+(yin-y)*(yin-y)+(zin-z)*(zin-z));
    return d2;
  }
  if(distancefuncname == "distance_fly_retro"){
    double d_p_p = distancefunction(info,xin,yin,zin,"distance_position_pmt");
    double d_p_r = distancefunction(info,xin,yin,zin,"distance_position_retro");
    return (d_p_p + 2*d_p_r);
  }
  std::cout << "invaild distancefunctionname " << distancefuncname << std::endl;
  throw "double MinimizedFunction::distancefunction(hitinfo info,double x,double y,double z,std::string distancefuncname)";
}

double MinimizedFunction::NormalizedCherenkovAngleDis(double costhetahit){
  double I = 1.33729337950334557e+04;
  double afactor = 1./I;
  double sfactor = std::log(afactor);
  if(costhetahit < 0.2){
    return fmath::expd(7.83420e+00 + 2.21102e+00 * costhetahit + sfactor) + 5.03361039235597582e+03*afactor - fmath::expd(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor);
  }
  else if(costhetahit < 0.734){
    return fmath::expd(6.90684e+00 + 3.90134e+00 * costhetahit + sfactor) + 2.03617333293911543e+04*afactor - fmath::expd(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor);
  }
  else if(costhetahit < 0.7594){
    double s = (costhetahit - 7.46966e-01)/9.45515e-03;
    return 5.21370e+04*afactor * fmath::expd(-s*s/2.);
  }
  else{
    return -4.67671e+04*afactor * (costhetahit - 0.7594) + 2.19586218087540583e+04*afactor;
  }
}

double MinimizedFunction::cherenkovanglefunc(hitinfo info,double x,double y,double z,double costheta,double phi,std::string cherenkovanglefuncname){
  CLHEP::Hep3Vector vect;
  vect.setRThetaPhi(1.,std::acos(costheta),phi);
  CLHEP::Hep3Vector hitvec = info.Get3Position() - CLHEP::Hep3Vector(x,y,z);
  double costhetahit = hitvec.cosTheta(vect);
  if(cherenkovanglefuncname == "nodarkratever2"){
    if(costhetahit < 0.2){
      return fmath::expd(-6.326106061e+00 + 2.21102e+00 * costhetahit) + 3.56527787154126445e-03 - fmath::expd(-6.326106061e+00 + 2.21102e+00 * 0.2);
    }
    else if(costhetahit < 0.734){
      return fmath::expd(-7.25356606128095915e+00 + 3.90134e+00 * costhetahit) + 1.44221009587363787e-02 - fmath::expd(-7.25356606128095915e+00 + 3.90134e+00 * 0.734);
    }
    else if(costhetahit < 0.7594){
      double s = (costhetahit - 7.46966e-01)/9.45515e-03;
      return 3.69283432565277667e-02 * fmath::expd(-s*s/2.);
    }
    else{
      return -3.31248733512162150e-02 * (costhetahit - 0.7594) + 1.55531680686258611e-02;
    }
  }
  else if(cherenkovanglefuncname == "nodarkrateOnretroDir"){
    double I = 1.33729337950334557e+04;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double afactor = (1/I)*std::sqrt((1-retroratio)/NPMT);
    double sfactor = std::log(afactor);
    if(costhetahit < 0.2){
      return fmath::expd(7.83420e+00 + 2.21102e+00 * costhetahit + sfactor) + 5.03361039235597582e+03*afactor - fmath::expd(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor);
    }
    else if(costhetahit < 0.734){
      return fmath::expd(6.90684e+00 + 3.90134e+00 * costhetahit + sfactor) + 2.03617333293911543e+04*afactor - fmath::expd(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor);
    }
    else if(costhetahit < 0.7594){
      double s = (costhetahit - 7.46966e-01)/9.45515e-03;
      return 5.21370e+04*afactor * fmath::expd(-s*s/2.);
    }
    else{
      return -4.67671e+04*afactor * (costhetahit - 0.7594) + 2.19586218087540583e+04*afactor;
    }
  }
  else if(cherenkovanglefuncname == "nodarkrateOnretroRef"){
    costhetahit = -costhetahit;
    double I = 1.33729337950334557e+04;
    int NPMT = data->wcsimrootgeom->GetWCNumPMT();
    double afactor = (1/I)*std::sqrt((retroratio)/NPMT);
    double sfactor = std::log(afactor);
    if(costhetahit < 0.2){
      return fmath::expd(7.83420e+00 + 2.21102e+00 * costhetahit + sfactor) + 5.03361039235597582e+03*afactor - fmath::expd(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor);
    }
    else if(costhetahit < 0.734){
      return fmath::expd(6.90684e+00 + 3.90134e+00 * costhetahit + sfactor) + 2.03617333293911543e+04*afactor - fmath::expd(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor);
    }
    else if(costhetahit < 0.7594){
      double s = (costhetahit - 7.46966e-01)/9.45515e-03;
      return 5.21370e+04*afactor * fmath::expd(-s*s/2.);
    }
    else{
      return -4.67671e+04*afactor * (costhetahit - 0.7594) + 2.19586218087540583e+04*afactor;
    }
  }
  else if(cherenkovanglefuncname == "likelihoodfdirectionnoretro")
    {
      double bydatanoretroa0 = 0.97648;
      double bydatanoretrob0 = 3.51958;
      double bydatanoretroa1 = 0.88353;
      double bydatanoretrob1 = -3.52407;
      if(costhetahit < 0.75){
	return (1 + bydatanoretroa0 * (fmath::expd(bydatanoretrob0 * (costhetahit -0.75 )) -1));
      }
      else{
	return(1 + bydatanoretroa1 * (fmath::expd(bydatanoretrob1 * (costhetahit - 0.75 )) - 1));
      }
    }
  else if(cherenkovanglefuncname == "likelihoodfdirectiononretro")
    {
      double bydataonretroa0 = 1.55324;
      double bydataonretrob0 = 1.53637;
      double bydataonretroa1 = 0.75423;
      double bydataonretrob1 = -2.31295;
      if(costhetahit < -0.75){
	return (1 + bydataonretroa0 * (fmath::expd(bydataonretrob0 * (costhetahit +0.75 )) -1));
      }
      else{
	return(1 + bydataonretroa1 * (fmath::expd(bydataonretrob1 * (costhetahit + 0.75 )) - 1));
      }
    }
  std::cout << "invalid cherenkovanglefuncname " << cherenkovanglefuncname << std::endl;
  throw "double MinimizedFunction::cherenkovanglefunc(hitinfo info,double x,double y,double z,double costheta,double phi,std::string cherenkovanglefuncname);";
}

double MinimizedFunction::effectiveReflectivity(double x,double y,double z,double costheta,double phi){
  double reflectivity = 0.;
  double refalpha = 0.71;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  reflectivity *= refalpha;
  double anglemin = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAnglemin",anglemin);
  double anglemax = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAngleMax",anglemax);
  CLHEP::Hep3Vector dir;
  dir.setRThetaPhi(1.,std::acos(costheta),phi);
  TMatrixD mtrue = rotation3D(dir);
  TMatrixD mtrueInvert = rotation3D(dir).Invert();
  int number = 1000;
  double phitruevec = 0.;
  double costhetatruevec = 0.75;
  double deltaphi = 2*std::acos(-1.)/number;
  if(allhitinfo.size() == 0)
    return 1.;
  double WCradius = allhitinfo[0].GetWCradius();
  double WClength = allhitinfo[0].GetWClength();
  double half_WClength = WClength/2.;
  double reff = 0.;
  for(int i = 0;i < number;i++){
    phitruevec = i*deltaphi;
    CLHEP::Hep3Vector directiontruevec;
    directiontruevec.setRThetaPhi(1.,std::acos(costhetatruevec),phitruevec);
    CLHEP::Hep3Vector direction = cross(mtrueInvert,directiontruevec);
    double xdirection = direction.x();
    double ydirection = direction.y();
    double zdirection = direction.z();
    double a = xdirection*xdirection + ydirection*ydirection;
    double b = xdirection*x+ydirection*y;
    double c = x*x+y*y-WCradius*WCradius;
    double t;
    if(a != 0.){
      t = (-b+std::sqrt(b*b-a*c))/a;
    }
    else{
      t = -c/(2*b);
    }
    double zplus = z + zdirection*t;
    double angle = 0.;
    if(zplus < -half_WClength){
      CLHEP::Hep3Vector walldir(0.,0.,-1.);
      angle = walldir.theta(direction);
    }
    else if(zplus > half_WClength){
      CLHEP::Hep3Vector walldir(0.,0.,1.);
      angle = walldir.theta(direction);
    }
    else if(-half_WClength < zplus && half_WClength > zplus){
      double xplus = x + xdirection*t;
      double yplus = y + ydirection*t;
      CLHEP::Hep3Vector walldir(xplus,yplus,0.);
      angle = walldir.theta(direction);
    }
    angle = (angle*180./std::acos(-1.));
    double refphi = 0.;
    if(std::abs(angle) > anglemax){
      refphi = 0.;
    }
    else if(std::abs(angle) > anglemin){
      refphi = (-reflectivity/(anglemax - anglemin))*(angle - anglemax);
    }
    else{
      refphi = reflectivity;
    }
    reff += (refphi*deltaphi/(2*std::acos(-1.)));
  }
  return reff;
}

double MinimizedFunction::effectiveReflectivityBroad(double x,double y,double z,double costheta,double phi){
  double reflectivity = 0.;
  double refalpha = 0.71;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  reflectivity = reflectivity*refalpha;
  double anglemin = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAnglemin",anglemin);
  double anglemax = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAngleMax",anglemax);
  CLHEP::Hep3Vector dir;
  dir.setRThetaPhi(1.,std::acos(costheta),phi);
  TMatrixD mtrue = rotation3D(dir);
  TMatrixD mtrueInvert = rotation3D(dir).Invert();
  int numberphi = 100;
  int numbercostheta1 = 100;
  int numbercostheta2 = 100;
  int numbercostheta3 = 100;
  double costheta1 = 0.734;
  double costheta2 = 0.7594;
  double phitruevec = 0.;
  double costhetatruevec = 0.;
  double deltaphi = 2*std::acos(-1.)/numberphi;
  double deltacostheta1 = (costheta1 + 1.)/numbercostheta1;
  double deltacostheta2 = (costheta2 - costheta1)/numbercostheta2;
  double deltacostheta3 = (1. - costheta2)/numbercostheta3;
  if(allhitinfo.size() == 0)
    return 1.;
  double WCradius = allhitinfo[0].GetWCradius();
  double WClength = allhitinfo[0].GetWClength();
  double half_WClength = WClength/2.;
  double reff = 0.;
  double deltacostheta = 0.;
  for(int j = 0;j < (numbercostheta1+numbercostheta2+numbercostheta3);j++){
    if(j < numbercostheta1){
      costhetatruevec = -1. + j*deltacostheta1;
      deltacostheta = deltacostheta1;
    }
    else if(j < (numbercostheta1 + numbercostheta2)){
      costhetatruevec = costheta1 + (j - numbercostheta1)*deltacostheta2;
      deltacostheta = deltacostheta2;
    }
    else{
      costhetatruevec = costheta2 + (j - numbercostheta1 - numbercostheta2)*deltacostheta3;
      deltacostheta = deltacostheta3;
    }
    double pangle = NormalizedCherenkovAngleDis(costhetatruevec);
    for(int i = 0;i < numberphi;i++){
      phitruevec = i*deltaphi;
      CLHEP::Hep3Vector directiontruevec;
      directiontruevec.setRThetaPhi(1.,std::acos(costhetatruevec),phitruevec);
      CLHEP::Hep3Vector direction = cross(mtrueInvert,directiontruevec);
      double xdirection = direction.x();
      double ydirection = direction.y();
      double zdirection = direction.z();
      double a = xdirection*xdirection + ydirection*ydirection;
      double b = xdirection*x+ydirection*y;
      double c = x*x+y*y-WCradius*WCradius;
      double t;
      if(a != 0.){
	t = (-b+std::sqrt(b*b-a*c))/a;
      }
      else{
	t = -c/(2*b);
      }
      double zplus = z + zdirection*t;
      double angle = 0.;
      if(zplus < -half_WClength){
	CLHEP::Hep3Vector walldir(0.,0.,-1.);
	angle = walldir.theta(direction);
      }
      else if(zplus > half_WClength){
	CLHEP::Hep3Vector walldir(0.,0.,1.);
	angle = walldir.theta(direction);
      }
      else if(-half_WClength < zplus && half_WClength > zplus){
	double xplus = x + xdirection*t;
	double yplus = y + ydirection*t;
	CLHEP::Hep3Vector walldir(xplus,yplus,0.);
	angle = walldir.theta(direction);
      }
      angle = (angle*180./std::acos(-1.));
      double refphi = 0.;
      if(std::abs(angle) > anglemax){
	refphi = 0.;
      }
      else if(std::abs(angle) > anglemin){
	refphi = (-reflectivity/(anglemax - anglemin))*(angle - anglemax);
      }
      else{
	refphi = reflectivity;
      }
      reff += (refphi*pangle*deltaphi*deltacostheta/(2*std::acos(-1.)));
    }
  }
  return reff;
}

double MinimizedFunction::effectiveReflectivityConsiderCoverage(double x,double y,double z,double costheta,double phi){
  double reflectivity = 0.;
  double refalpha = 0.71;
  file.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
  reflectivity *= refalpha;
  double anglemin = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAnglemin",anglemin);
  double anglemax = 0.;
  file.GetTagdouble("ReflectivityFactorTrapezoidAngleMax",anglemax);
  CLHEP::Hep3Vector dir;
  dir.setRThetaPhi(1.,std::acos(costheta),phi);
  TMatrixD mtrue = rotation3D(dir);
  TMatrixD mtrueInvert = rotation3D(dir).Invert();
  int number = 1000;
  double phitruevec = 0.;
  double costhetatruevec = 0.75;
  double deltaphi = 2*std::acos(-1.)/number;
  if(allhitinfo.size() == 0)
    return 1.;
  double WCradius = allhitinfo[0].GetWCradius();
  double WClength = allhitinfo[0].GetWClength();
  double half_WClength = WClength/2.;
  double reff = 0.;
  for(int i = 0;i < number;i++){
    phitruevec = i*deltaphi;
    CLHEP::Hep3Vector directiontruevec;
    directiontruevec.setRThetaPhi(1.,std::acos(costhetatruevec),phitruevec);
    CLHEP::Hep3Vector direction = cross(mtrueInvert,directiontruevec);
    double xdirection = direction.x();
    double ydirection = direction.y();
    double zdirection = direction.z();
    double a = xdirection*xdirection + ydirection*ydirection;
    double b = xdirection*x+ydirection*y;
    double c = x*x+y*y-WCradius*WCradius;
    double t;
    if(a != 0.){
      t = (-b+std::sqrt(b*b-a*c))/a;
    }
    else{
      t = -c/(2*b);
    }
    double zplus = z + zdirection*t;
    double angle = 0.;
    double phi_ref = 0.;
    if(zplus < -half_WClength){
      CLHEP::Hep3Vector walldir(0.,0.,-1.);
      angle = walldir.theta(direction);
      phi_ref = (-direction).phi();
    }
    else if(zplus > half_WClength){
      CLHEP::Hep3Vector walldir(0.,0.,1.);
      angle = walldir.theta(direction);
      phi_ref = (-direction).phi();
    }
    else if(-half_WClength < zplus && half_WClength > zplus){
      double xplus = x + xdirection*t;
      double yplus = y + ydirection*t;
      CLHEP::Hep3Vector walldir(xplus,yplus,0.);
      angle = walldir.theta(direction);
      CLHEP::Hep3Vector rotationaxis(0.,0.,1.);
      CLHEP::Hep3Vector rotatedhitdirection = direction.rotate(rotationaxis,-std::atan2(-xplus,-yplus));
      phi_ref = std::atan(rotatedhitdirection.y()/rotatedhitdirection.z());
    }
    double pi = std::acos(-1.);
    if(phi_ref < 0.)
      {
	phi_ref = phi_ref + pi;
      }
    if(phi_ref > pi/2.)
      {
	phi_ref = phi_ref - pi/2.;
      }
    double coverage = 0.;
    int bintheta = hPhotoCoverage->GetXaxis()->FindBin(angle*180./pi);
    int binphi = hPhotoCoverage->GetYaxis()->FindBin(phi_ref*180./pi);
    if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
      {
	std::cout << "warning: coverage cannot be calculated!" << std::endl;
	std::cout << "theta_i = " << angle << std::endl;
	std::cout << "phi_i = " << phi_ref << std::endl;
	coverage = 1.;
      }
    else
      {
	coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
      }
    angle = (angle*180./pi);
    double refphi = 0.;
    if(std::abs(angle) > anglemax){
      refphi = 0.;
    }
    else if(std::abs(angle) > anglemin){
      refphi = (-reflectivity/(anglemax - anglemin))*(angle - anglemax);
    }
    else{
      refphi = reflectivity;
    }
    reff += (1-coverage)*(refphi*deltaphi/(2*std::acos(-1.)));
  }
  return reff;
}

double MinimizedFunction::ReflectCoverage(double x,double y,double z,int ihit){
  double WCradius = allhitinfo[0].GetWCradius();
  double WClength = allhitinfo[0].GetWClength();
  double half_WClength = WClength/2.;
  hitinfo info = allhitinfo[ihit];
  CLHEP::Hep3Vector direction = info.Get3Position() - CLHEP::Hep3Vector(x,y,z);
  double xdirection = direction.x();
  double ydirection = direction.y();
  double zdirection = direction.z();
  double a = xdirection*xdirection + ydirection*ydirection;
  double b = xdirection*x+ydirection*y;
  double c = x*x+y*y-WCradius*WCradius;
  double t;
  if(a != 0.){
    t = (-b-std::sqrt(b*b-a*c))/a;
  }
  else{
    t = -c/(2*b);
  }
  double zplus = z + zdirection*t;
  double angle = 0.;
  double phi_ref = 0.;
  if(zplus < -half_WClength){
    CLHEP::Hep3Vector walldir(0.,0.,-1.);
    angle = walldir.theta(-direction);
    phi_ref = direction.phi();
  }
  else if(zplus > half_WClength){
    CLHEP::Hep3Vector walldir(0.,0.,1.);
    angle = walldir.theta(-direction);
    phi_ref = direction.phi();
  }
  else if(-half_WClength < zplus && half_WClength > zplus){
    double xplus = x + xdirection*t;
    double yplus = y + ydirection*t;
    CLHEP::Hep3Vector walldir(xplus,yplus,0.);
    angle = walldir.theta(-direction);
    CLHEP::Hep3Vector rotationaxis(0.,0.,1.);
    CLHEP::Hep3Vector rotatedhitdirection = (-direction).rotate(rotationaxis,-std::atan2(-xplus,-yplus));
    phi_ref = std::atan(rotatedhitdirection.y()/rotatedhitdirection.z());
  }
  double pi = std::acos(-1.);
  if(phi_ref < 0.)
    {
      phi_ref = phi_ref + pi;
    }
  if(phi_ref > pi/2.)
    {
      phi_ref = phi_ref - pi/2.;
    }
  double coverage = 0.;
  int bintheta = hPhotoCoverage->GetXaxis()->FindBin(angle*180./pi);
  int binphi = hPhotoCoverage->GetYaxis()->FindBin(phi_ref*180./pi);
  if((bintheta == 0) || (bintheta == hPhotoCoverage->GetXaxis()->GetNbins() + 1) || (binphi == 0) || (binphi == hPhotoCoverage->GetYaxis()->GetNbins() + 1))
    {
      std::cout << "warning: coverage cannot be calculated!" << std::endl;
      std::cout << "theta = " << angle << std::endl;
      std::cout << "phi = " << phi_ref << std::endl;
      coverage = 1.;
    }
  else
    {
      coverage = hPhotoCoverage->GetBinContent(bintheta,binphi);
    }
  return (1-coverage);
}


double MinimizedFunction::pmtcostheta(hitinfo info,double x,double y,double z){
  CLHEP::Hep3Vector vec = CLHEP::Hep3Vector(x,y,z) - info.Get3Position();
  double costheta = info.Get3Orientation().cosTheta(vec);
  return costheta;
}
