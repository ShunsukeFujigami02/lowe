// STL
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <regex>
#include <memory>
// ROOT
#include <TPython.h>
#include <TH1D.h>
#include <TVector3.h>
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
// self
#include "AnalizeManager.hh"
#include "constants.hh"
#include "rotation3D.hh"
#include "MinimizedFunction.hh"
#include "Energy.hh"
#include "distance_function.hh"
#include "tof.hh"

ClassImp(AnalizeManager)
AnalizeManager::AnalizeManager()
{
}


void AnalizeManager::cpFileList(FileManager* manager,std::string filelistname)
{
  //  (*this).filelistname.push_back(filelistname);
  listoffilelist.insert(std::make_pair(filelistname,manager->selectedfilemap));
}


bool AnalizeManager::GetValuehit(std::string valueload,double& value,AnalizeFile file,AnalizeFiledata* data,int ievent,int hitnum)
{
  if(valueload == "number")
    {
      value = 1.;
      return true;
    }
  hitinfo info = data->allhitinfo[hitnum];
  if(valueload == "emittimeerrortrue")
    {
      double distance = 0.;
      GetValuehit("distance_positiontrue_pmt",distance,file,data,ievent,hitnum);
      double tofvalue = info.HitTime() - offset - (distance - doffset)/v_light_in_water;
      double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      double toferror = tofvalue - t;
      value = toferror;
      return true;
    }
  if(valueload == "emittimeerrorretrotrue")
    {
      double distance = 0.;
      GetValuehit("distance_fly_retro_true",distance,file,data,ievent,hitnum);
      double tofvalue = info.HitTime() - offset - (distance - doffset)/v_light_in_water;
      double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      double toferror = tofvalue - t;
      value = toferror;
      return true;
    }
  if(valueload == "distance_positiontrue_pmt")
    {
      CLHEP::Hep3Vector pmtposition = info.Get3Position();
      double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector position (x,y,z);
      CLHEP::Hep3Vector p_p = pmtposition - position;
      value = p_p.mag();
      return true;
    }
  if(valueload == "distance_positiontrue_retro")
    {
      double xin = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double yin = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double zin = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
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
      value = d2;
      return true;
    }
  if(valueload == "distance_fly_retro_true"){
    double d_p_p = 0.;
    GetValuehit("distance_positiontrue_pmt",d_p_p,file,data,ievent,hitnum);
    double d_p_r = 0.;
    GetValuehit("distance_positiontrue_retro",d_p_r,file,data,ievent,hitnum);
    value = (d_p_p + 2* d_p_r);
    return true;
  }
  if(valueload == "distance_retro_pmt_true"){
    double d_p_p = 0.;
    GetValuehit("distance_positiontrue_pmt",d_p_p,file,data,ievent,hitnum);
    double d_p_r = 0.;
    GetValuehit("distance_positiontrue_retro",d_p_r,file,data,ievent,hitnum);
    value = (d_p_p + d_p_r);
    return true;
  }
  if(valueload == "openingangle")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      CLHEP::Hep3Vector pmtposition = info.Get3Position();
      double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector position (x,y,z);
      CLHEP::Hep3Vector p_p = pmtposition - position;
      value = dir.cosTheta(p_p);
      return true;
    }
  if(valueload == "CylLoc")
    {
      
      value = info.GetCylLoc();
      return true;
    }
  return false;
}

bool AnalizeManager::GetValueRun(AnalizeFile file,AnalizeFiledata* data,std::string valueload,double &value)
{
  if(valueload == "number")
    {
      value = 1.;
      return true;
    }
  if(valueload == "triggerefficiency")
    {
      int nevent = data->GetEntriesMin();
      int sum = 0;
      for(int ievent = 0;ievent != nevent;ievent++)
	{
	  data->GetEntry(ievent);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    sum += 1;
	  }
	}
      value = (double)sum/(double)nevent;
      return true;
    }
  if(valueload == "NPMT")
    {
      value = (double)data->wcsimrootgeom->GetWCNumPMT();
      return true;
    }
  if(valueload == "meanofncherenkovdigihits")
    {
      int nevent = data->GetEntriesMin();
      int sum = 0;
      int npasstrigger = 0;
      for(int ievent = 0;ievent != nevent;ievent++)
	{
	  data->GetEntry(ievent);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    sum += ncherenkovdigihits;
	    npasstrigger++;
	  }
	}
      double average = (double)sum/(double)npasstrigger;
      value = average;
      return true;
    }
  if(valueload == "distancebyonesigmagoodness")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> distancevec;
      double onesigma = 0.682689492;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double distance = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"distance_true_reconstructedbygoodness",distance);
	  distancevec.push_back(distance);
	}
      }
      std::sort(distancevec.begin(),distancevec.end());
      int onesigmavalue = (int)((onesigma*(double)distancevec.size()) - 0.5);
      value = (distancevec[onesigmavalue] + distancevec[onesigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "distancebyonesigmaminimize")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> distancevec;
      double onesigma = 0.682689492;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double distance = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"distance_true_reconstructedbyminimize",distance);
	  distancevec.push_back(distance);
	}
      }
      std::sort(distancevec.begin(),distancevec.end());
      int onesigmavalue = (int)((onesigma*(double)distancevec.size()) - 0.5);
      value = (distancevec[onesigmavalue] + distancevec[onesigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "distancebytwosigmagoodness")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> distancevec;
      double twosigma = 0.954499736;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double distance = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"distance_true_reconstructedbygoodness",distance);
	  distancevec.push_back(distance);
	}
      }
      std::sort(distancevec.begin(),distancevec.end());
      int twosigmavalue = (int)((twosigma*(double)distancevec.size()) - 0.5);
      value = (distancevec[twosigmavalue] + distancevec[twosigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "distancebytwosigmaminimize")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> distancevec;
      double twosigma = 0.954499736;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double distance = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"distance_true_reconstructedbyminimize",distance);
	  distancevec.push_back(distance);
	}
      }
      std::sort(distancevec.begin(),distancevec.end());
      int twosigmavalue = (int)((twosigma*(double)distancevec.size()) - 0.5);
      value = (distancevec[twosigmavalue] + distancevec[twosigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "deltaanglebyonesigmalikelihood")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> deltaanglevec;
      double onesigma = 0.682689492;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double deltaangle = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"deltaanglebylikelihood",deltaangle);
	  deltaanglevec.push_back(deltaangle);
	}
      }
      std::sort(deltaanglevec.begin(),deltaanglevec.end());
      int onesigmavalue = (int)((onesigma*(double)deltaanglevec.size()) - 0.5);
      value = (deltaanglevec[onesigmavalue] + deltaanglevec[onesigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "deltaanglebyonesigmaminimize")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> deltaanglevec;
      double onesigma = 0.682689492;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double deltaangle = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"deltaanglebyminimize",deltaangle);
	  deltaanglevec.push_back(deltaangle);
	}
      }
      std::sort(deltaanglevec.begin(),deltaanglevec.end());
      int onesigmavalue = (int)((onesigma*(double)deltaanglevec.size()) - 0.5);
      value = (deltaanglevec[onesigmavalue] + deltaanglevec[onesigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "deltaanglebytwosigmalikelihood")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> deltaanglevec;
      double twosigma = 0.954499736;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double deltaangle = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"deltaanglebylikelihood",deltaangle);
	  deltaanglevec.push_back(deltaangle);
	}
      }
      std::sort(deltaanglevec.begin(),deltaanglevec.end());
      int twosigmavalue = (int)((twosigma*(double)deltaanglevec.size()) - 0.5);
      value = (deltaanglevec[twosigmavalue] + deltaanglevec[twosigmavalue + 1])/2.;
      return true;
    }
  if(valueload == "deltaanglebytwosigmaminimize")
    {
      int nevent = data->GetEntriesMin();
      std::vector<double> deltaanglevec;
      double twosigma = 0.954499736;
      for(int ievent;ievent < nevent;ievent++){
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	double deltaangle = 0.;
	if(ncherenkovdigihits != 0){
	  GetValue(file,data,"deltaanglebyminimize",deltaangle);
	  deltaanglevec.push_back(deltaangle);
	}
      }
      std::sort(deltaanglevec.begin(),deltaanglevec.end());
      int twosigmavalue = (int)((twosigma*(double)deltaanglevec.size()) - 0.5);
      value = (deltaanglevec[twosigmavalue] + deltaanglevec[twosigmavalue + 1])/2.;
      return true;
    }
  return false;
}

bool AnalizeManager::GetValue(AnalizeFile manager,AnalizeFiledata* data,std::string valueload,double& value,int ievent)
{
  if(valueload == "number")
    {
      value = 1.;
      return true;
    }
  if(valueload == "distance_true_reconstructedbygoodness")
    {
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      TVector3 reconstructvec = data->reconstructdata->Get3Position();
      CLHEP::Hep3Vector reconstructvec2(reconstructvec.X(),reconstructvec.Y(),reconstructvec.Z());
      value = (truevec - reconstructvec2).mag();
      return true;
    }
  if(valueload == "distance_true_reconstructedbyminimize")
    {
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdataminimize->GetParameter(0);
      double reconstructy = data->reconstructdataminimize->GetParameter(1);
      double reconstructz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      value = (truevec - reconstructvec).mag();
      return true;
    }
  
  if(valueload == "truecostheta")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      value = dir.cosTheta();
      return true;
    }
  if(valueload == "truephi")
    {
            WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      value = dir.phi();
      return true;
    }
  if(valueload == "minimizedcostheta")
    {
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	}
      value = minimizecostheta;
      return true;
    }
  if(valueload == "minimizedphi")
    {
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector minimizedirection = CLHEP::Hep3Vector();
      minimizedirection.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      value = minimizedirection.phi();
      return true;
    }
  
  if(valueload == "deltaanglebylikelihood")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double likelihooddirx = data->reconstructdatalikelihood->Getdirection().X();
      double likelihooddiry = data->reconstructdatalikelihood->Getdirection().Y();
      double likelihooddirz = data->reconstructdatalikelihood->Getdirection().Z();
      CLHEP::Hep3Vector ldir(likelihooddirx,likelihooddiry,likelihooddirz);
      value = dir.angle(ldir);
      return true;
    }
  if(valueload == "deltaanglebyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      value = dir.angle(mdir);
      return true;
    }
  if(valueload == "rvalueminimizeminusgoodness")
    {
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      TVector3 reconstructvec = data->reconstructdata->Get3Position();
      CLHEP::Hep3Vector reconstructvec2(reconstructvec.X(),reconstructvec.Y(),reconstructvec.Z());
      double tminusrabs = (truevec - reconstructvec2).mag();
      double minimizedx = data->reconstructdataminimize->GetParameter(0);
      double minimizedy = data->reconstructdataminimize->GetParameter(1);
      double minimizedz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector minimizedvec(minimizedx,minimizedy,minimizedz);
      double tminusmabs = (truevec - minimizedvec).mag();
      value = tminusmabs - tminusrabs;
      return true;
    }
  if(valueload == "reconstructedcherenkovhitnum")
    {
      int digihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
      double darkhits = data->reconstructdataminimize->GetParameter(6);
      value = (double)digihits - darkhits;
      return true;
    }
  if(valueload == "trueTriggerTimeminus")
    {
      value = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      value = -value;
      return true;
    }
  if(valueload == "longitudinalpositionerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdataminimize->GetParameter(0);
      double reconstructy = data->reconstructdataminimize->GetParameter(1);
      double reconstructz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.z();
      return true;
    }
  if(valueload == "transversepositionxerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdataminimize->GetParameter(0);
      double reconstructy = data->reconstructdataminimize->GetParameter(1);
      double reconstructz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.x();
      return true;
    }
  if(valueload == "transversepositionyerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdataminimize->GetParameter(0);
      double reconstructy = data->reconstructdataminimize->GetParameter(1);
      double reconstructz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.y();
      return true;
    }
  if(valueload == "transversepositiondistanceerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdataminimize->GetParameter(0);
      double reconstructy = data->reconstructdataminimize->GetParameter(1);
      double reconstructz = data->reconstructdataminimize->GetParameter(2);
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = std::sqrt(errorvecnewaxis.x()*errorvecnewaxis.x() + errorvecnewaxis.y() * errorvecnewaxis.y());
      return true;
    }
  
  if(valueload == "directionxerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.x();
      return true;
    }
  if(valueload == "directionyerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.y();
      return true;
    }
  if(valueload == "directionzerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.z();
      return true;
    }
    if(valueload == "directioncosthetatrueaxisbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.cosTheta();
      return true;
    }
      if(valueload == "directionphitrueaxisbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.phi();
      return true;
    }
    if(valueload == "transversedirectiondistanceerrorbyminimize")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdataminimize->GetParameter(4);
      double minimizephi = data->reconstructdataminimize->GetParameter(5);
      if(minimizecostheta > 1.)
	{
	  minimizecostheta = 2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      else if(minimizecostheta < -1.)
	{
	  minimizecostheta = -2 - minimizecostheta;
	  minimizephi = minimizephi + PI;
	}
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = std::sqrt(newmdir.x() * newmdir.x() +newmdir.y()* newmdir.y());
      return true;
    }
  if(valueload == "treconstructbyminimizeminusttrue")
    {
      double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      ttrueminus = -ttrueminus;
      double treconstruct = data->reconstructdataminimize->GetParameter(3);
      value = treconstruct - ttrueminus;
      return true;
    }
    if(valueload == "treconstructbygoodnessminusttrue")
    {
      double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      ttrueminus = -ttrueminus;
      double treconstruct = data->reconstructdata->Get4Vector().T();
      value = treconstruct - ttrueminus;
      return true;
    }
    if(valueload == "longitudinalpositionerrorbygoodness")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdata->Get3Position().X();
      double reconstructy = data->reconstructdata->Get3Position().Y();
      double reconstructz = data->reconstructdata->Get3Position().Z();
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.z();
      return true;
    }
  if(valueload == "transversepositionxerrorbygoodness")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdata->Get3Position().X();
      double reconstructy = data->reconstructdata->Get3Position().Y();
      double reconstructz = data->reconstructdata->Get3Position().Z();
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.x();
      return true;
    }
  if(valueload == "transversepositionyerrorbygoodness")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdata->Get3Position().X();
      double reconstructy = data->reconstructdata->Get3Position().Y();
      double reconstructz = data->reconstructdata->Get3Position().Z();
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = errorvecnewaxis.y();
      return true;
    }
  if(valueload == "transversepositiondistanceerrorbygoodness")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
      double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
      double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
      CLHEP::Hep3Vector truevec(truex,truey,truez);
      double reconstructx = data->reconstructdata->Get3Position().X();
      double reconstructy = data->reconstructdata->Get3Position().Y();
      double reconstructz = data->reconstructdata->Get3Position().Z();
      CLHEP::Hep3Vector reconstructvec(reconstructx,reconstructy,reconstructz);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector errorvecnewaxis = cross(mtrue,reconstructvec - truevec);
      value = std::sqrt(errorvecnewaxis.x()*errorvecnewaxis.x() + errorvecnewaxis.y() * errorvecnewaxis.y());
      return true;
    }
  
  if(valueload == "directionxerrorbylikelihood")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdatalikelihood->Getdirection().CosTheta();
      double minimizephi = data->reconstructdatalikelihood->Getdirection().Phi();
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.x();
      return true;
    }
  if(valueload == "directionyerrorbylikelihood")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdatalikelihood->Getdirection().CosTheta();
      double minimizephi = data->reconstructdatalikelihood->Getdirection().Phi();
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.y();
      return true;
    }
  if(valueload == "directionzerrorbylikelihood")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdatalikelihood->Getdirection().CosTheta();
      double minimizephi = data->reconstructdatalikelihood->Getdirection().Phi();
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = newmdir.z();
      return true;
    }
    if(valueload == "transversedirectiondistanceerrorbylikelihood")
    {
      WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
      double truedirx = track->GetPdir(0);
      double truediry = track->GetPdir(1);
      double truedirz = track->GetPdir(2);
      CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
      double minimizecostheta = data->reconstructdatalikelihood->Getdirection().CosTheta();
      double minimizephi = data->reconstructdatalikelihood->Getdirection().Phi();
      CLHEP::Hep3Vector mdir;
      mdir.setRThetaPhi(1.,std::acos(minimizecostheta),minimizephi);
      TMatrixD mtrue = rotation3D(dir);
      CLHEP::Hep3Vector newmdir = cross(mtrue,mdir);
      value = std::sqrt(newmdir.x() * newmdir.x() +newmdir.y()* newmdir.y());
      return true;
    }
  if(valueload == "treconstructbygoodnessminusttrue")
    {
      double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
      ttrueminus = -ttrueminus;
      double treconstruct = data->reconstructdata->Get4Vector().T();
      value = treconstruct - ttrueminus;
      return true;
    }
  if(valueload == "ncherenkovdigihits"){
    value = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    return true;
  }
  if(valueload == "distancetoDetector"){
    double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    double barrel = 1686. - std::sqrt(truex*truex+truey*truey);
    double upcap = 1810. - truez;
    double bottomcap = truez + 1810.;
    if((barrel < upcap) && (barrel < bottomcap)){
      value = barrel;
    }
    else if(upcap < bottomcap){
      value = upcap;
    }
    else{
      value = bottomcap;
    }
    return true;
  }
  if(valueload == "efficienthitsdirect"){
    value = data->effNdirect;
    return true;
  }
  if(valueload == "efficienthitsreflect"){
    value = data->effNreflect;
    return true;
  }
  if(valueload == "EnergyNoRetro"){
    double effNdirect = data->effNdirect;
    double E = (effNdirect +3.37513)/6.75277;
    value = E;
    return true;
  }
  if(valueload == "EnergyOnRetrobydirecthits"){
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0 = AnalizeManager::EnergyToMeanOnRetrodirectp0(reflectivity);
    double p1 = AnalizeManager::EnergyToMeanOnRetrodirectp1(reflectivity);
    double effNdirect = data->effNdirect;
    double E = (effNdirect - p0)/p1;
    value = E;
    return true;
  }
  if(valueload == "EnergyOnRetrobyreflecthits"){
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0 = AnalizeManager::EnergyToMeanOnRetroreflectp0(reflectivity);
    double p1 = AnalizeManager::EnergyToMeanOnRetroreflectp1(reflectivity);
    double effNreflect = data->effNreflect;
    double E = (effNreflect - p0)/p1;
    value = E;
    return true;
  }
  if(valueload == "ReconstructEnergyOnRetro"){
    double effNdirect = data->effNdirect;
    double effNreflect = data->effNreflect;
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0dir = AnalizeManager::EnergyToMeanOnRetrodirectp0(reflectivity);
    double p1dir = AnalizeManager::EnergyToMeanOnRetrodirectp1(reflectivity);
    double Edirect = (effNdirect - p0dir)/p1dir;
    double p0ref = AnalizeManager::EnergyToMeanOnRetroreflectp0(reflectivity);
    double p1ref = AnalizeManager::EnergyToMeanOnRetroreflectp1(reflectivity);
    double Ereflect = (effNreflect - p0ref)/p1ref;
    double E_sigma_direct = 0.265206 + 0.162252*Edirect - 0.00354251*Edirect*Edirect;
    double p0r = AnalizeManager::EnergyToSigmaOnRetrop0(reflectivity);
    double p1r = AnalizeManager::EnergyToSigmaOnRetrop1(reflectivity);
    double p2r = AnalizeManager::EnergyToSigmaOnRetrop2(reflectivity);
    double E_sigma_reflect = p0r + p1r*Edirect + p2r*Edirect*Edirect;
    double E = (Edirect/(E_sigma_direct*E_sigma_direct) + Ereflect/(E_sigma_reflect*E_sigma_reflect))/(1./(E_sigma_direct*E_sigma_direct) + 1./(E_sigma_reflect*E_sigma_reflect));
    value = E;
    return true;
  }
  if(valueload == "Esigmadirect"){
    double effNdirect = data->effNdirect;
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0dir = AnalizeManager::EnergyToMeanOnRetrodirectp0(reflectivity);
    double p1dir = AnalizeManager::EnergyToMeanOnRetrodirectp1(reflectivity);
    double Edirect = (effNdirect - p0dir)/p1dir;
    value = 0.265206 + 0.162252*Edirect - 0.00354251*Edirect*Edirect;
    return true;
  }
  if(valueload == "Esigmareflect"){
    double effNdirect = data->effNdirect;
    double effNreflect = data->effNreflect;
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0dir = AnalizeManager::EnergyToMeanOnRetrodirectp0(reflectivity);
    double p1dir = AnalizeManager::EnergyToMeanOnRetrodirectp1(reflectivity);
    double Edirect = (effNdirect - p0dir)/p1dir;
    double p0r = AnalizeManager::EnergyToSigmaOnRetrop0(reflectivity);
    double p1r = AnalizeManager::EnergyToSigmaOnRetrop1(reflectivity);
    double p2r = AnalizeManager::EnergyToSigmaOnRetrop2(reflectivity);
    value = p0r + p1r*Edirect + p2r*Edirect*Edirect;
    return true;
  }
  if(valueload == "ReconstructEnergyOnRetrodouble"){
    double effNdirect = data->effNdirect;
    double effNreflect = data->effNreflect;
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    double p0dir = AnalizeManager::EnergyToMeanOnRetrodirectp0(reflectivity);
    double p1dir = AnalizeManager::EnergyToMeanOnRetrodirectp1(reflectivity);
    double Edirect = (effNdirect - p0dir)/p1dir;
    double p0ref = AnalizeManager::EnergyToMeanOnRetroreflectp0(reflectivity);
    double p1ref = AnalizeManager::EnergyToMeanOnRetroreflectp1(reflectivity);
    double Ereflect = (effNreflect - p0ref)/p1ref;
    double E_sigma_direct = 0.265206 + 0.162252*Edirect - 0.00354251*Edirect*Edirect;
    double p0r = AnalizeManager::EnergyToSigmaOnRetrop0(reflectivity);
    double p1r = AnalizeManager::EnergyToSigmaOnRetrop1(reflectivity);
    double p2r = AnalizeManager::EnergyToSigmaOnRetrop2(reflectivity);
    double E_sigma_reflect = p0r + p1r*Edirect + p2r*Edirect*Edirect;
    double E = (Edirect/(E_sigma_direct*E_sigma_direct) + Ereflect/(E_sigma_reflect*E_sigma_reflect))/(1./(E_sigma_direct*E_sigma_direct) + 1./(E_sigma_reflect*E_sigma_reflect));
    E_sigma_direct = 0.265206 + 0.162252*E - 0.00354251*E*E;
    E_sigma_reflect = p0r + p1r*E + p2r*E*E;
    E = (Edirect/(E_sigma_direct*E_sigma_direct) + Ereflect/(E_sigma_reflect*E_sigma_reflect))/(1./(E_sigma_direct*E_sigma_direct) + 1./(E_sigma_reflect*E_sigma_reflect));
    value = E;
    return true;
  }
  if(valueload == "N50direff"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->reconstructdataminimize->GetParameter(0);
    minimizedvalue.emplace_back(x);
    double y = data->reconstructdataminimize->GetParameter(1);
    minimizedvalue.emplace_back(y);
    double z = data->reconstructdataminimize->GetParameter(2);
    minimizedvalue.emplace_back(z);
    double t = data->reconstructdataminimize->GetParameter(3);
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    double costheta = data->reconstructdataminimize->GetParameter(4);
    minimizedvalue.emplace_back(costheta);
    double phi = data->reconstructdataminimize->GetParameter(5);
    minimizedvalue.emplace_back(phi);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,6);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,6);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime);
      double nref = preftime/(pdirtime + preftime);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  value = N50direff;
  return true;
  }
  if(valueload == "N50refeff"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->reconstructdataminimize->GetParameter(0);
    minimizedvalue.emplace_back(x);
    double y = data->reconstructdataminimize->GetParameter(1);
    minimizedvalue.emplace_back(y);
    double z = data->reconstructdataminimize->GetParameter(2);
    minimizedvalue.emplace_back(z);
    double t = data->reconstructdataminimize->GetParameter(3);
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    double costheta = data->reconstructdataminimize->GetParameter(4);
    minimizedvalue.emplace_back(costheta);
    double phi = data->reconstructdataminimize->GetParameter(5);
    minimizedvalue.emplace_back(phi);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,6);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,6);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime);
      double nref = preftime/(pdirtime + preftime);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  value = N50refeff;
  return true;
  }
  if(valueload == "N50refeffTrue"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int N50ref = 0;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    minimizedvalue.emplace_back(x);
    double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    minimizedvalue.emplace_back(y);
    double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    minimizedvalue.emplace_back(z);
    double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double costheta = dir.cosTheta();
    minimizedvalue.emplace_back(costheta);
    double phi = dir.phi();
    double darknumexpected = 63.198;
    minimizedvalue.emplace_back(darknumexpected);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,7);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,7);
    MinimizedFunction* funcpdark = new MinimizedFunction("pdark",manager,data,7);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
    funcpdark->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime + pdark);
      double nref = preftime/(pdirtime + preftime + pdark);
      double ndark = pdark/(pdirtime + preftime + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50ref++;
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  std::cout << "N50ref = " << N50ref <<std::endl;
  value = N50refeff;
  return true;
  }
  if(valueload == "N50refTrue"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int N50ref = 0;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    minimizedvalue.emplace_back(x);
    double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    minimizedvalue.emplace_back(y);
    double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    minimizedvalue.emplace_back(z);
    double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double costheta = dir.cosTheta();
    minimizedvalue.emplace_back(costheta);
    double phi = dir.phi();
    double darknumexpected = 63.198;
    minimizedvalue.emplace_back(darknumexpected);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,7);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,7);
    MinimizedFunction* funcpdark = new MinimizedFunction("pdark",manager,data,7);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
    funcpdark->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime + pdark);
      double nref = preftime/(pdirtime + preftime + pdark);
      double ndark = pdark/(pdirtime + preftime + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    std::cout << "toferrornoretro = " << toferrornoretro << std::endl;
	    N50ref++;
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    std::cout << "toferrornoretro = " << toferrornoretro << std::endl;
	    N50ref++;
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  std::cout << "N50ref = " << N50ref <<std::endl;
  value = N50ref;
  return true;
  }
  if(valueload == "N100direffTrue"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    minimizedvalue.emplace_back(x);
    double y = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    minimizedvalue.emplace_back(y);
    double z = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    minimizedvalue.emplace_back(z);
    double t = -data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double costheta = dir.cosTheta();
    minimizedvalue.emplace_back(costheta);
    double phi = dir.phi();
    minimizedvalue.emplace_back(phi);
    double darknumexpected = 63.198;
    minimizedvalue.emplace_back(darknumexpected);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,7);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,7);
    MinimizedFunction* funcpdark = new MinimizedFunction("pdark",manager,data,7);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
    funcpdark->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double pdark = funcpdark->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime + pdark);
      double nref = preftime/(pdirtime + preftime + pdark);
      double ndark = pdark/(pdirtime + preftime + pdark);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  value = N100direff;
  return true;
  }
  if(valueload == "N100refeff"){
    double N50direff = 0.;
    double N50refeff = 0.;
    double N100direff = 0.;
    double N100refeff = 0.;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    std::vector<double> minimizedvalue;
    double x = data->reconstructdataminimize->GetParameter(0);
    minimizedvalue.emplace_back(x);
    double y = data->reconstructdataminimize->GetParameter(1);
    minimizedvalue.emplace_back(y);
    double z = data->reconstructdataminimize->GetParameter(2);
    minimizedvalue.emplace_back(z);
    double t = data->reconstructdataminimize->GetParameter(3);
    minimizedvalue.emplace_back(t);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    double costheta = data->reconstructdataminimize->GetParameter(4);
    minimizedvalue.emplace_back(costheta);
    double phi = data->reconstructdataminimize->GetParameter(5);
    minimizedvalue.emplace_back(phi);
    double reflectivity = 0.;
    manager.GetTagdouble("ReflectivityFactorTrapezoidReflectivity",reflectivity);
    MinimizedFunction* funcpdir = new MinimizedFunction("pdirtime",manager,data,6);
    MinimizedFunction* funcpref = new MinimizedFunction("preftime",manager,data,6);
    funcpdir->SetEventNumber(ievent);
    funcpref->SetEventNumber(ievent);
  for(int k = 0;k < ncherenkovdigihits;k++)
    {
      WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(data->wcsimrootevent->GetTrigger(0)->GetCherenkovDigiHits()->At(k));
      std::shared_ptr<distance_position_pmt> d_p_p = std::make_shared<distance_position_pmt>();
      std::shared_ptr<tof> ftof = std::make_shared<tof>();
      ftof->Setdistancefunction(d_p_p);
      ftof->SetHitInfo(data->allhitinfo[k]);
      ftof->SetReconstructdata(rdata);
      double toferrornoretro = ftof->returnvalue() - rdata.Get4Vector().t();
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      double pdirtime = funcpdir->returnvaluecontentshit(minimizedvalue,k);
      double preftime = funcpref->returnvaluecontentshit(minimizedvalue,k);
      double ndir = pdirtime/(pdirtime + preftime);
      double nref = preftime/(pdirtime + preftime);
      if(std::abs(toferrornoretro) < 25.)
	{
	  N50direff += ndir;
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      else
	{
	  if(std::abs(toferroronretro) < 25.){
	    N50refeff += nref;
	  }
	  else{
	  }
	}
      if(std::abs(toferrornoretro) < 50.)
	{
	  N100direff += ndir;
	}
      if(std::abs(toferroronretro) < 50.)
	{
	  N100refeff += nref;
	}
    }
  value = N100refeff;
  return true;
  }
  if(valueload == "ReconstructedEnergyNoRetro"){
    double effN = data->effNdirect;
    value = (2.7841 + effN)/7.01148;
    return true;
  }
  /*if(valueload == "ReconstructedEnergyOnRetro"){
    double effN = data->effN;
    value = (3.438 + effN)/9.28536;
    return true;
  }
  if(valueload == "ReconstructedEnergyOnRetroaddretrotail"){
    double effN = data->effN;
    value = (3.02223 + effN)/9.65313;
    return true;
    }*/
  if(valueload == "effectiveReflectivitybytrue"){
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    MinimizedFunction* func = new MinimizedFunction("effectiveReflectivity",manager,data,6);
    func->SetEventNumber(ievent);
    std::vector<double> invalue;
    invalue.push_back(truex);
    invalue.push_back(truey);
    invalue.push_back(truez);
    invalue.push_back(0.);
    invalue.push_back(dir.cosTheta());
    invalue.push_back(dir.phi());
    value = func->returnvaluecontents(invalue);
    return true;
  }
  if(valueload == "effectiveReflectivityBroadbytrue"){
   WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    MinimizedFunction* func = new MinimizedFunction("effectiveReflectivityBroad",manager,data,6);
    func->SetEventNumber(ievent);
    std::vector<double> invalue;
    invalue.push_back(truex);
    invalue.push_back(truey);
    invalue.push_back(truez);
    invalue.push_back(0.);
    invalue.push_back(dir.cosTheta());
    invalue.push_back(dir.phi());
    value = func->returnvaluecontents(invalue);
    delete func;
    return true;
  } 
  if(valueload == "effectiveReflectivityConsiderCoveragebytrue"){
    WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
    double truedirx = track->GetPdir(0);
    double truediry = track->GetPdir(1);
    double truedirz = track->GetPdir(2);
    CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
    double truex = data->wcsimrootevent->GetTrigger(0)->GetVtx(0);
    double truey = data->wcsimrootevent->GetTrigger(0)->GetVtx(1);
    double truez = data->wcsimrootevent->GetTrigger(0)->GetVtx(2);
    MinimizedFunction* func = new MinimizedFunction("effectiveReflectivityConsiderCoverage",manager,data,6);
    func->SetEventNumber(ievent);
    std::vector<double> invalue;
    invalue.push_back(truex);
    invalue.push_back(truey);
    invalue.push_back(truez);
    invalue.push_back(0.);
    invalue.push_back(dir.cosTheta());
    invalue.push_back(dir.phi());
    value = func->returnvaluecontents(invalue);
    return true;
  }
  if(valueload == "N50onretrominimized"){
    int N50onretro = 0;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    double x = data->reconstructdataminimize->GetParameter(0);
    double y = data->reconstructdataminimize->GetParameter(1);
    double z = data->reconstructdataminimize->GetParameter(2);
    double t = data->reconstructdataminimize->GetParameter(3);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    for(int k = 0;k < ncherenkovdigihits;k++){
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      if(std::abs(toferroronretro) < 25.){
	N50onretro++;
      }
    }
    value = (double)N50onretro;
    return true;
  }
  if(valueload == "N100minusN50onretrominimized"){
    int N100minusN50onretro = 0;
    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
    Reconstructdata rdata;
    double x = data->reconstructdataminimize->GetParameter(0);
    double y = data->reconstructdataminimize->GetParameter(1);
    double z = data->reconstructdataminimize->GetParameter(2);
    double t = data->reconstructdataminimize->GetParameter(3);
    rdata.Set4Vector(CLHEP::HepLorentzVector(x,y,z,t));
    for(int k = 0;k < ncherenkovdigihits;k++){
      std::shared_ptr<distance_fly_retro> d_f_r = std::make_shared<distance_fly_retro>();
      std::shared_ptr<tof> ftofonretro = std::make_shared<tof>();
      ftofonretro->Setdistancefunction(d_f_r);
      ftofonretro->SetHitInfo(data->allhitinfo[k]);
      ftofonretro->SetReconstructdata(rdata);
      double toferroronretro = ftofonretro->returnvalue() - rdata.Get4Vector().t();
      if((std::abs(toferroronretro) > 25.) && (std::abs(toferroronretro) < 50.)){
	N100minusN50onretro++;
      }
    }
    value = (double)N100minusN50onretro;
    return true;
  }
  if(valueload == "GetDirectPartMinimized")
    {
      
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
      for(int i = 0; i < parnum;i++)
	{
	  double val = 0;
	  val = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvec.push_back(val);
	}
      std::string acomma;
      for(int i = 0; i < parnum;i++)
	{
	  acomma.append(std::to_string(valvec.at(i)));
	  if(i != (parnum - 1))
	    acomma.append(",");
	}
      TPython::Exec(("input = [" + acomma + "]").c_str());
      value = TPython::Eval("mfunc.GetDirectPart(input)");
      return true;
    }
  if(valueload == "GetReflectPartMinimized")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
      for(int i = 0; i < parnum;i++)
	{
	  double val = 0;
	  val = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvec.push_back(val);
	}
      std::string acomma;
      for(int i = 0; i < parnum;i++)
	{
	  acomma.append(std::to_string(valvec.at(i)));
	  if(i != (parnum - 1))
	    acomma.append(",");
	}
      TPython::Exec(("input = [" + acomma + "]").c_str());
      value = TPython::Eval("mfunc.GetReflectPart(input)");
      return true;
    }
  if(valueload == "GetDarkPartMinimized")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
      for(int i = 0; i < parnum;i++)
	{
	  double val = 0;
	  val = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvec.push_back(val);
	}
      std::string acomma;
      for(int i = 0; i < parnum;i++)
	{
	  acomma.append(std::to_string(valvec.at(i)));
	  if(i != (parnum - 1))
	    acomma.append(",");
	}
      TPython::Exec(("input = [" + acomma + "]").c_str());
      value = TPython::Eval("mfunc.GetDarkPart(input)");
      return true;
    }
  if(valueload == "GetDirectPartFirst")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
      for(int i = 0; i < parnum;i++)
	{
	  double val = 0;
	  val = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvec.push_back(val);
	}
      std::string acomma;
      for(int i = 0; i < parnum;i++)
	{
	  acomma.append(std::to_string(valvec.at(i)));
	  if(i != (parnum - 1))
	    acomma.append(",");
	}
      TPython::Exec(("input = [" + acomma + "]").c_str());
      value = TPython::Eval("mfunc.GetDirectPart(input)");
      return true;
    }
  if(valueload == "GetReflectPartFirst")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
      for(int i = 0; i < parnum;i++)
	{
	  double val = 0;
	  val = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvec.push_back(val);
	}
      std::string acomma;
      for(int i = 0; i < parnum;i++)
	{
	  acomma.append(std::to_string(valvec.at(i)));
	  if(i != (parnum - 1))
	    acomma.append(",");
	}
      TPython::Exec(("input = [" + acomma + "]").c_str());
      value = TPython::Eval("mfunc.GetReflectPart(input)");
      return true;
    }
  if(valueload == "GetDarkPartFirst")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvec;
	  for(int i = 0; i < parnum;i++)
	    {
	      double val = 0;
	      val = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	      valvec.push_back(val);
	    }
	  std::string acomma;
	  for(int i = 0; i < parnum;i++)
	    {
	      acomma.append(std::to_string(valvec.at(i)));
	      if(i != (parnum - 1))
		acomma.append(",");
	    }
	  TPython::Exec(("input = [" + acomma + "]").c_str());
	  value = TPython::Eval("mfunc.GetDarkPart(input)");
	  return true;
    }
  if(valueload == "GetDirectPartFirstminusMinimized")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvecfirst;
      for(int i = 0; i < parnum;i++)
	{
	  double valfirst = 0;
	  valfirst = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecfirst.push_back(valfirst);
	}
      std::string acommafirst;
      for(int i = 0; i < parnum;i++)
	{
	  acommafirst.append(std::to_string(valvecfirst.at(i)));
	  if(i != (parnum - 1))
	    acommafirst.append(",");
	}
      TPython::Exec(("inputfirst = [" + acommafirst + "]").c_str());
      std::vector<double> valvecminimized;
      for(int i = 0; i < parnum;i++)
	{
	  double valminimized = 0;
	  valminimized = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecminimized.push_back(valminimized);
	}
      std::string acommaminimized;
      for(int i = 0; i < parnum;i++)
	{
	  acommaminimized.append(std::to_string(valvecminimized.at(i)));
	  if(i != (parnum - 1))
	    acommaminimized.append(",");
	}
      TPython::Exec(("inputminimized = [" + acommaminimized + "]").c_str());
      value = TPython::Eval("mfunc.GetDirectPart(inputfirst) - mfunc.GetDirectPart(inputminimized)");
      return true;
    }
    if(valueload == "GetReflectPartFirstminusMinimized")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvecfirst;
      for(int i = 0; i < parnum;i++)
	{
	  double valfirst = 0;
	  valfirst = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecfirst.push_back(valfirst);
	}
      std::string acommafirst;
      for(int i = 0; i < parnum;i++)
	{
	  acommafirst.append(std::to_string(valvecfirst.at(i)));
	  if(i != (parnum - 1))
	    acommafirst.append(",");
	}
      TPython::Exec(("inputfirst = [" + acommafirst + "]").c_str());
      std::vector<double> valvecminimized;
      for(int i = 0; i < parnum;i++)
	{
	  double valminimized = 0;
	  valminimized = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecminimized.push_back(valminimized);
	}
      std::string acommaminimized;
      for(int i = 0; i < parnum;i++)
	{
	  acommaminimized.append(std::to_string(valvecminimized.at(i)));
	  if(i != (parnum - 1))
	    acommaminimized.append(",");
	}
      TPython::Exec(("inputminimized = [" + acommaminimized + "]").c_str());
      value = TPython::Eval("mfunc.GetReflectPart(inputfirst) - mfunc.GetReflectPart(inputminimized)");
      return true;
    }
    if(valueload == "GetDarkPartFirstminusMinimized")
    {
      std::string funcname;
      manager.GetTagstring("MinimizeFunctionName",funcname);
      TPython::Exec(("mfunc = func." + funcname + "(f)").c_str());
      TPython::Exec(("mfunc.SetAllhitinfo(" + std::to_string(ievent) + ")").c_str());
      int parnum = TPython::Eval("mfunc.parnum");
      std::vector<double> valvecfirst;
      for(int i = 0; i < parnum;i++)
	{
	  double valfirst = 0;
	  valfirst = TPython::Eval(("mfunc.Getfirstvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecfirst.push_back(valfirst);
	}
      std::string acommafirst;
      for(int i = 0; i < parnum;i++)
	{
	  acommafirst.append(std::to_string(valvecfirst.at(i)));
	  if(i != (parnum - 1))
	    acommafirst.append(",");
	}
      TPython::Exec(("inputfirst = [" + acommafirst + "]").c_str());
      std::vector<double> valvecminimized;
      for(int i = 0; i < parnum;i++)
	{
	  double valminimized = 0;
	  valminimized = TPython::Eval(("mfunc.GetMinimizedvalue(" + std::to_string(i) + "," + std::to_string(ievent) + ")").c_str());
	  valvecminimized.push_back(valminimized);
	}
      std::string acommaminimized;
      for(int i = 0; i < parnum;i++)
	{
	  acommaminimized.append(std::to_string(valvecminimized.at(i)));
	  if(i != (parnum - 1))
	    acommaminimized.append(",");
	}
      TPython::Exec(("inputminimized = [" + acommaminimized + "]").c_str());
      value = TPython::Eval("mfunc.GetDarkPart(inputfirst) - mfunc.GetDarkPart(inputminimized)");
      return true;
    }
    int valueint = 0;
    if(manager.GetTagint(valueload,valueint))
      {
	value = (double)valueint;
	return true;
      }
    if(manager.GetTagdouble(valueload,value))
      {
	return true;
      }
    return false;
}

bool AnalizeManager::GetValue(std::string flistname,AnalizeFile manager,AnalizeFiledata*data,std::string valueload,double& value)
{
  if(valueload == "number")
    {
      value = 1.;
      return true;
    }
  int valueint = 0;
  std::string bvalue = "init";
  if(manager.GetTagint(valueload,valueint))
    {
      value = (double)valueint;
      return true;
    }
  if(manager.GetTagdouble(valueload,value))
    {
      return true;
    }
  return false;
}

bool AnalizeManager::isselectedevent(std::string cut,AnalizeFile file,AnalizeFiledata* data,int ievent)
{
  if(cut == "no")
    return true;
  std::string cutreplaced = std::regex_replace(cut,std::regex("ievent"),std::to_string(ievent));
  std::vector<std::string> v;
  std::stringstream sscut{cutreplaced};
  std::string buf;
  while(std::getline(sscut,buf,' '))
    {
      v.push_back(buf);
    }
  std::string cutchanged = "";
  for(auto iter = v.begin();iter != v.end();iter++)
    {
      if(((*iter) == "<") || ((*iter) == ">") || ((*iter) == "==") || ((*iter) == "and") || ((*iter) == "or") || ((*iter) == "(") || ((*iter) == ")"))
	{
	  cutchanged += (*iter);
	  cutchanged += " ";
	  continue;
	}
      double value = 0.;
      bool b = GetValue(file,data,(*iter),value,ievent);
      if(b == true)
	{
	  (*iter) = std::to_string(value);
	  cutchanged += (*iter);
	  cutchanged += " ";
	  continue;
	}
      cutchanged += (*iter);
      cutchanged += " ";
    }
  const char* b = TPython::Eval(("str(" + cutchanged + ")").c_str());
  std::string sb = b;
  if(sb == "True")
    return true;
  else if(sb == "False")
    return false;
  else
    {
      std::cout << "invalid str converge" << std::endl;
      throw "bool AnalizeManager::isselectedevent(std::string cutfront,std::string cutback,int ievent)";
    }
  return false;
}

bool AnalizeManager::isselectedhit(std::string cut,AnalizeFile file,AnalizeFiledata* data,int ievent,int hitnum)
{
  if(cut == "no")
    return true;
  std::string cutreplaced1 = std::regex_replace(cut,std::regex("ievent"),std::to_string(ievent));
  std::string cutreplaced2 = std::regex_replace(cutreplaced1,std::regex("hitnum"),std::to_string(hitnum));
  std::vector<std::string> v;
  std::stringstream sscut{cutreplaced2};
  std::string buf;
  while(std::getline(sscut,buf,' '))
    {
      v.push_back(buf);
    }
  std::string cutchanged = "";
  for(auto iter = v.begin();iter != v.end();iter++)
    {
      if(((*iter) == "<") || ((*iter) == ">") || ((*iter) == "==") || ((*iter) == "and") || ((*iter) == "or") || ((*iter) == "(") || ((*iter) == ")"))
	{
	  cutchanged += (*iter);
	  cutchanged += " ";
	  continue;
	}
      double value = 0.;
      bool b = GetValuehit((*iter),value,file,data,ievent,hitnum);
      if(b == true)
	{
	  (*iter) = std::to_string(value);
	  cutchanged += (*iter);
	  cutchanged += " ";
	  continue;
	}
      cutchanged += (*iter);
      cutchanged += " ";
    }
  const char* b = TPython::Eval(("str(" + cutchanged + ")").c_str());
  std::string sb = b;
  if(sb == "True")
    return true;
  else if(sb == "False")
    return false;
  else
    {
      std::cout << "invalid str converge" << std::endl;
      throw "bool AnalizeManager::isselectedhit(std::string cutfront,std::string cutback,int ievent,int hitnum)";
    }
  return false;
}
void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ievent)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      //      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	double x = 0.;
	double value = 0.;
	if(!GetValue((*iterin).second,data,xaxis,x,ievent))
	  {
	    std::cout << "invalid x input!" << std::endl;
	    throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	  }
	if(!GetValue((*iterin).second,data,valueaxis,value,ievent))
	  {
	    std::cout << "invalid value input!" << std::endl;
	    throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	  }
	h1->Fill(x,value);
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)
{
 auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      //      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	double x = 0.;
	double value = 0.;
	if(!GetValue(flistname,(*iterin).second,data,xaxis,x))
	  {
	    std::cout << "invalid x input!" << std::endl;
	    throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	  }
	if(!GetValue(flistname,(*iterin).second,data,valueaxis,value))
	    {
	      std::cout << "invalid value input!" << std::endl;
	      throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	    }
	std::cout << "x = " << x << " value = " << value << std::endl;
	h1->Fill(x,value);
      }
      catch(std::string s)
	{
	  delete data;
	  throw;
	}
      delete data;
    }
}

void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut,bool printeventnumber)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	SetTH1DEvent(h1,xaxis,valueaxis,flistname,(*iterin).second,data,cut,printeventnumber);
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
  
}

AnalizeFile AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ifile,std::string cut,bool printeventnumber)
{
  auto iter = listoffilelist.at(flistname);
  auto iterin = iter.begin();
  for(int i = 0;i < ifile;i++){
    iterin++;
  }
  AnalizeFiledata* data = new AnalizeFiledata();
  try{
    data->Construct((*iterin).second);
    SetTH1DEvent(h1,xaxis,valueaxis,flistname,(*iterin).second,data,cut,printeventnumber);
  }
  catch(std::string s){
    delete data;
    throw;
  }
  delete data;
  return (*iterin).second;
}

void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,AnalizeFile file,AnalizeFiledata* data,std::string cut,bool printeventnumber)
{
  //  TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + file.fileroot + "']").c_str());
  int nevent = data->GetEntriesMin();
  for(int ievent = 0;ievent != nevent;ievent++)
    {
      //      TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
      //      int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
      data->GetEntry(ievent);
      int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
      //      const char* bncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[1]");
      if(ncherenkovdigihits != 0)
	{
	  double x = 0.;
	  double value = 0.;
	  if(!GetValue(file,data,xaxis,x,ievent))
	    {
	      std::cout << "invalid x input!" << std::endl;
	      throw "void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
	    }
	  if(!GetValue(file,data,valueaxis,value,ievent))
	    {
	      std::cout << "invalid value input!" << std::endl;
	      throw "void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
	    }
	  if(isselectedevent(cut,file,data,ievent))
	    {
	      if(printeventnumber)
		std::cout << "eventnumber = " << ievent << std::endl;
	      h1->Fill(x,value);
	    }
	}
    }
}

void AnalizeManager::SetTH1DEvent(std::vector<TH1D*> hvec,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut,bool printeventnumber)
{
  if(hvec.size() != listoffilelist[flistname].size())
    {
      std::cout << "invalid histogram number!" << std::endl;
      return;
    }
  auto iter = listoffilelist.at(flistname);
  auto iterhist = hvec.begin();
  for(auto iterin = iter.begin();iterin != iter.end();iterin++,iterhist++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	SetTH1DEvent((*iterhist),xaxis,valueaxis,flistname,(*iterin).second,data,cut,printeventnumber);
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string yaxis,std::string valueaxis,std::string flistname,std::string cut,bool printeventnumber)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      //      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
      //      int nevent = TPython::Eval("f.GetNeventmax()");
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	int nevent = data->GetEntriesMin();
	for(int ievent = 0;ievent != nevent;ievent++)
	  {
	    //	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	    //	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	    data->GetEntry(ievent);
	    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	    if(ncherenkovdigihits != 0)
	      {
		double x = 0.;
		double y = 0.;
		double value = 0.;
		if(!GetValue((*iterin).second,data,xaxis,x,ievent))
		  {
		    std::cout << "invalid x input!" << std::endl;
		    throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		  }
		if(!GetValue((*iterin).second,data,yaxis,y,ievent))
		  {
		    std::cout << "invalid y input!" << std::endl;
		    throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		  }
		
		if(!GetValue((*iterin).second,data,valueaxis,value,ievent))
		  {
		    std::cout << "invalid value input!" << std::endl;
		    throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		  }
		if(isselectedevent(cut,(*iterin).second,data,ievent))
		  { 
		    if(printeventnumber)
		      std::cout << "eventnumber = " << ievent << std::endl;
		    h->Fill(x,y,value);
		  }
	      }
	  }
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,std::string cut)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	//      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
	//      int nevent = TPython::Eval("f.GetNeventmax()");
	int nevent = data->GetEntriesMin();
	for(int ievent = 0;ievent != nevent;ievent++)
	  {
	    //	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	    //	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	    data->GetEntry(ievent);
	    int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	    for(int k = 0;k != ncherenkovdigihits;k++)
	      {
		double x = 0.;
		double value = 0.;
		if(!GetValuehit(xaxis,x,(*iterin).second,data,ievent,k))
		  {
		    std::cout << "invalid x input!" << std::endl;
		    throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		  }
		if(!GetValuehit(valueaxis,value,(*iterin).second,data,ievent,k))
		  {
		    std::cout << "invalid value input!" << std::endl;
		    throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		  }
		if(isselectedhit(cut,(*iterin).second,data,ievent,k))
		  h1->Fill(x,value);
	      }
	  }
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

AnalizeFile AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname,int ifile,std::string cut)
{
  auto iter = listoffilelist.at(flistname);
  auto iterin = iter.begin();
  for(int i = 0;i < ifile;i++){
    iterin++;
  }
  AnalizeFiledata* data = new AnalizeFiledata();
  try{
    data->Construct((*iterin).second);
    //      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
    //      int nevent = TPython::Eval("f.GetNeventmax()");
    int nevent = data->GetEntriesMin();
    for(int ievent = 0;ievent != nevent;ievent++)
      {
	//	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	//	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	data->GetEntry(ievent);
	int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	for(int k = 0;k != ncherenkovdigihits;k++)
	  {
	    double x = 0.;
	    double value = 0.;
	    if(!GetValuehit(xaxis,x,(*iterin).second,data,ievent,k))
	      {
		std::cout << "invalid x input!" << std::endl;
		throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
	      }
	    if(!GetValuehit(valueaxis,value,(*iterin).second,data,ievent,k))
	      {
		std::cout << "invalid value input!" << std::endl;
		throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		  }
	    if(isselectedhit(cut,(*iterin).second,data,ievent,k))
	      h1->Fill(x,value);
	  }
      }
  }
  catch(std::string s){
    delete data;
    throw;
  }
  delete data;
  return (*iterin).second;
}

AnalizeFile AnalizeManager::SetdoubleRun(double& value,std::string valueaxis,std::string flistname,int ifile)
{
  auto iter = listoffilelist.at(flistname);
  auto iterin = iter.begin();
  for(int i = 0;i < ifile;i++){
    iterin++;
  }
  AnalizeFiledata* data = new AnalizeFiledata();
  try{
    data->Construct((*iterin).second);
    int nevent = data->GetEntriesMin();
    if(!GetValueRun((*iterin).second,data,valueaxis,value)){
      std::cout << "invalid value input!" << std::endl;
      throw "AnalizeFile AnalizeManager::SetdoubleRun(double value,std::string valueaxis,std::string flistname,int ifile,std::string cut);";
     }
  }
  catch(std::string s){
    delete data;
    throw;
  }
  delete data;
  return (*iterin).second;
}

void AnalizeManager::SetTH2DAllHit(TH2D* h1,std::string xaxis,std::string yaxis,std::string valueaxis,std::string flistname,std::string cut)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	//      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
	//      int nevent = TPython::Eval("f.GetNeventmax()");
	int nevent = data->GetEntriesMin();
	for(int ievent = 0;ievent != nevent;ievent++)
	  {
	    //	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	    //	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	    data->GetEntry(ievent);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  for(int k = 0;k != ncherenkovdigihits;k++)
	    {
	      double x = 0.;
	      double y = 0.;
	      double value = 0.;
	      if(!GetValuehit(xaxis,x,(*iterin).second,data,ievent,k))
		{
		  std::cout << "invalid x input!" << std::endl;
		  throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		}
	      if(!GetValuehit(yaxis,y,(*iterin).second,data,ievent,k))
		{
		  std::cout << "invalid y input!" << std::endl;
		  throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		}
	      if(!GetValuehit(valueaxis,value,(*iterin).second,data,ievent,k))
		{
		  std::cout << "invalid value input!" << std::endl;
		  throw "void AnalizeManager::SetTH1DAllHit(TH1D* h1,std::string xaxis,std::string valueaxis,std::string flistname)";
		}
	      if(((ievent % 100) == 0) && (k == 0))
		{
		  std::cout << "event " << ievent << std::endl;
		  std::cout << "x = " << x << std::endl;
		  std::cout << "y = " << y << std::endl;
		  std::cout << "value = " << value << std::endl;
		}
	      if(isselectedhit(cut,(*iterin).second,data,ievent,k))
		h1->Fill(x,y,value);
	    }
	}
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

std::vector<double> AnalizeManager::SetTH1DFunctionDis(TH1D* h1,std::string funcname,int parnum,int variablenumber,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname)
{
  double truevalue = 0.;
  double beforeminimizevalue = 0.;
  double minimizedvalue = 0.;
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	if(minimizedfuncname == "default")
	  (*iterin).second.GetTagstring("MinimizeFunctionName",minimizedfuncname);
	MinimizedFunction* func = new MinimizedFunction(minimizedfuncname.c_str(),(*iterin).second,data,parnum);
	func->SetEventNumber(ievent);
	std::vector<double> valvectrue;
	std::vector<double> valvecbeforeminimize;
	std::vector<double> valvecminimized;
	for(int i = 0; i < parnum;i++)
	  {
	    double valtrue = 0.;
	    double valbeforeminimize = 0.;
	    double valminimized = 0.;
	    valtrue = func->GetTruevalue(i);
	    std::cout << "i = " << i << " : true value = " << valtrue << std::endl;
	    valbeforeminimize = func->Getfirstvalue()[i];
	    std::cout << "i = " << i << " : before minimize value = " << valbeforeminimize << std::endl;
	    if(data->reconstructdataminimize){
	      valminimized = data->reconstructdataminimize->GetParameter(i);
	      std::cout << "i = " << i << " : minimized value = " << valminimized << std::endl;
	    }
	    else{
	      valminimized = 0.;
	    }
	    valvectrue.push_back(valtrue);
	    valvecbeforeminimize.push_back(valbeforeminimize);
	    valvecminimized.push_back(valminimized);
	  }
	truevalue = valvectrue[variablenumber];
	beforeminimizevalue = valvecbeforeminimize[variablenumber];
	minimizedvalue = valvecminimized[variablenumber];
	std::vector<double> valvec;
	if(mode == "true")
	  valvec = valvectrue;
	else if(mode == "beforeminimize")
	  valvec = valvecbeforeminimize;
	else if(mode == "minimized")
	  valvec = valvecminimized;
	int binN = h1->GetXaxis()->GetNbins();
	for(int i = 1;i < binN + 1 ;i++)
	  {
	    double val = h1->GetXaxis()->GetBinCenter(i);
	    valvec.at(variablenumber) = val;
	    double value = 0.;
	    if(funcname == "returnvalue"){
	      value = func->returnvaluecontents(valvec);
	    }
	    h1->Fill(val,value);
	  }
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
  std::vector<double> returnvaluevec;
  returnvaluevec.push_back(truevalue);
  returnvaluevec.push_back(beforeminimizevalue);
  returnvaluevec.push_back(minimizedvalue);
  return returnvaluevec;
}

std::vector<double> AnalizeManager::SetTH2DFunctionDis(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname)
{
  double minimizedvaluex = 0.;
  double minimizedvaluey = 0.;
  double beforeminimizevaluex = 0.;
  double beforeminimizevaluey = 0.;
  double truevaluex = 0.;
  double truevaluey = 0.;
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	if(minimizedfuncname == "default")
	  (*iterin).second.GetTagstring("MinimizeFunctionName",minimizedfuncname);
	MinimizedFunction* func = new MinimizedFunction(minimizedfuncname.c_str(),(*iterin).second,data,parnum);
	func->SetEventNumber(ievent);
	std::vector<double> valvecfixedminimized;
	std::vector<double> valvecfixedbeforeminimize;
	std::vector<double> valvecfixedtrue;
	for(int i = 0; i < parnum;i++)
	  {
	    double valminimized = 0.;
	    double valbeforeminimize = 0.;
	    double valtrue = 0.;
	    valtrue = func->GetTruevalue(i);
	    std::cout << "i = " << i << " : true value = " << valtrue << std::endl;
	    valbeforeminimize = func->Getfirstvalue()[i];
	    std::cout << "i = " << i << " : before minimize value = " << valbeforeminimize << std::endl;
	    if(data->reconstructdataminimize){
	      valminimized = data->reconstructdataminimize->GetParameter(i);
	      std::cout << "i = " << i << " : minimized value = " << valminimized << std::endl;
	    }
	    valvecfixedminimized.push_back(valminimized);
	    valvecfixedbeforeminimize.push_back(valbeforeminimize);
	    valvecfixedtrue.push_back(valtrue);
	  }
	minimizedvaluex = valvecfixedminimized.at(variablenumberx);
	minimizedvaluey = valvecfixedminimized.at(variablenumbery);
	beforeminimizevaluex = valvecfixedbeforeminimize.at(variablenumberx);
	beforeminimizevaluey = valvecfixedbeforeminimize.at(variablenumbery);
	truevaluex = valvecfixedtrue.at(variablenumberx);
	truevaluey = valvecfixedtrue.at(variablenumbery);
	std::vector<double> valvecchanged;
	if(mode == "minimized")
	  valvecchanged = valvecfixedminimized;
	if(mode == "beforeminimize")
	  valvecchanged = valvecfixedbeforeminimize;
	if(mode == "true")
	  valvecchanged = valvecfixedtrue;
	int binxN = h1->GetXaxis()->GetNbins();
	int binyN = h1->GetYaxis()->GetNbins();
	for(int i = 1;i < binxN + 1 ;i++)
	  {
	    for(int j = 1;j < binyN + 1 ;j++)
	      {
		double xval = h1->GetXaxis()->GetBinCenter(i);
		double yval = h1->GetYaxis()->GetBinCenter(j);
		valvecchanged.at(variablenumberx) = xval;
		valvecchanged.at(variablenumbery) = yval;
		double value = 0.;
		if(funcname == "returnvalue"){
		  value = func->returnvaluecontents(valvecchanged);
		}
		h1->Fill(xval,yval,value);
	      }
	  }
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
  std::vector<double> returnval;
  returnval.push_back(minimizedvaluex);
  returnval.push_back(minimizedvaluey);
  returnval.push_back(beforeminimizevaluex);
  returnval.push_back(beforeminimizevaluey);
  returnval.push_back(truevaluex);
  returnval.push_back(truevaluey);
  return returnval;
}

std::vector<double> AnalizeManager::SetTH2DFunctionDisTrueaxis(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int ievent,std::string flistname,std::string minimizedfuncname)
{
  double minimizedvaluex = 0.;
  double minimizedvaluey = 0.;
  double beforeminimizevaluex = 0.;
  double beforeminimizevaluey = 0.;
  double truevaluex = 0.;
  double truevaluey = 0.;
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	if(minimizedfuncname == "default")
	  (*iterin).second.GetTagstring("MinimizeFunctionName",minimizedfuncname);
	MinimizedFunction* func = new MinimizedFunction(minimizedfuncname.c_str(),(*iterin).second,data,parnum);
	func->SetEventNumber(ievent);
	std::vector<double> valvecfixedtrue;
	std::vector<double> valvecfixedbeforeminimize;
	std::vector<double> valvecfixedminimized;
	for(int i = 0; i < parnum;i++)
	  {
	    double valtrue = 0;
	    double valbeforeminimize = 0.;
	    double valminimized = 0.;
	    valtrue = func->GetTruevalue(i);
	    std::cout << "i = " << i << " : true value = " << valtrue << std::endl;
	    valbeforeminimize = func->Getfirstvalue()[i];
	    std::cout << "i = " << i << " : before minimize value = " << valbeforeminimize << std::endl;
	    if(data->reconstructdataminimize){
	      valminimized = data->reconstructdataminimize->GetParameter(i);
	      std::cout << "i = " << i << " : minimized value = " << valminimized << std::endl;
	    }
	    valvecfixedtrue.push_back(valtrue);
	    valvecfixedbeforeminimize.push_back(valbeforeminimize);
	    valvecfixedminimized.push_back(valminimized);
	  }
	WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
	double truedirx = track->GetPdir(0);
	double truediry = track->GetPdir(1);
	double truedirz = track->GetPdir(2);
	CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
	CLHEP::Hep3Vector truepos(data->wcsimrootevent->GetTrigger(0)->GetVtx(0),data->wcsimrootevent->GetTrigger(0)->GetVtx(1),data->wcsimrootevent->GetTrigger(0)->GetVtx(2));
	TMatrixD mtrue = rotation3D(dir);
	TMatrixD mtrueInvert = rotation3D(dir).Invert();
	CLHEP::Hep3Vector positionminimized(valvecfixedminimized.at(0),valvecfixedminimized.at(1),valvecfixedminimized.at(2));
	CLHEP::Hep3Vector newpositionminimized = cross(mtrue,positionminimized - truepos);
	double costhetaminimized = valvecfixedminimized.at(4);
	double phiminimized = valvecfixedminimized.at(5);
	if(costhetaminimized > 1.)
	  {
	    costhetaminimized = 2 - costhetaminimized;
	    phiminimized = phiminimized + PI;
	  }
	else if(costhetaminimized < -1.)
	  {
	    costhetaminimized = -2 - costhetaminimized;
	    phiminimized = phiminimized + PI;
	  }
	CLHEP::Hep3Vector directionminimized;
	directionminimized.setRThetaPhi(1.,std::acos(costhetaminimized),phiminimized);
	CLHEP::Hep3Vector newdirectionminimized = cross(mtrue,directionminimized);
	double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
	ttrueminus = -ttrueminus;
	std::vector<double> newvalvecfixedminimized;
	newvalvecfixedminimized.push_back(newpositionminimized.x());
	newvalvecfixedminimized.push_back(newpositionminimized.y());
	newvalvecfixedminimized.push_back(newpositionminimized.z());
	newvalvecfixedminimized.push_back(valvecfixedminimized.at(3) - ttrueminus);
	newvalvecfixedminimized.push_back(newdirectionminimized.cosTheta());
	newvalvecfixedminimized.push_back(newdirectionminimized.phi());
	if(parnum == 7)
	  newvalvecfixedminimized.push_back(valvecfixedminimized.at(6));
	minimizedvaluex = newvalvecfixedminimized.at(variablenumberx);
	minimizedvaluey = newvalvecfixedminimized.at(variablenumbery);
	CLHEP::Hep3Vector positionbeforeminimize(valvecfixedbeforeminimize.at(0),valvecfixedbeforeminimize.at(1),valvecfixedbeforeminimize.at(2));
	CLHEP::Hep3Vector newpositionbeforeminimize = cross(mtrue,positionbeforeminimize - truepos);
	double costhetabeforeminimize = valvecfixedbeforeminimize.at(4);
	double phibeforeminimize = valvecfixedbeforeminimize.at(5);
	CLHEP::Hep3Vector directionbeforeminimize;
	directionbeforeminimize.setRThetaPhi(1.,std::acos(costhetabeforeminimize),phibeforeminimize);
	CLHEP::Hep3Vector newdirectionbeforeminimize = cross(mtrue,directionbeforeminimize);
	std::vector<double> newvalvecfixedbeforeminimize;
	newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.x());
	newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.y());
	newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.z());
	newvalvecfixedbeforeminimize.push_back(valvecfixedbeforeminimize.at(3) - ttrueminus);
	newvalvecfixedbeforeminimize.push_back(newdirectionbeforeminimize.cosTheta());
	newvalvecfixedbeforeminimize.push_back(newdirectionbeforeminimize.phi());
	if(parnum == 7)
	  newvalvecfixedbeforeminimize.push_back(valvecfixedbeforeminimize.at(6));
	beforeminimizevaluex = newvalvecfixedbeforeminimize.at(variablenumberx);
	beforeminimizevaluey = newvalvecfixedbeforeminimize.at(variablenumbery);
	CLHEP::Hep3Vector positiontrue(valvecfixedtrue.at(0),valvecfixedtrue.at(1),valvecfixedtrue.at(2));
	CLHEP::Hep3Vector newpositiontrue = cross(mtrue,positiontrue - truepos);
	double costhetatrue = valvecfixedtrue.at(4);
	double phitrue = valvecfixedtrue.at(5);
	CLHEP::Hep3Vector directiontrue;
	directiontrue.setRThetaPhi(1.,std::acos(costhetatrue),phitrue);
	CLHEP::Hep3Vector newdirectiontrue = cross(mtrue,directiontrue);
	std::vector<double> newvalvecfixedtrue;
	newvalvecfixedtrue.push_back(newpositiontrue.x());
	newvalvecfixedtrue.push_back(newpositiontrue.y());
	newvalvecfixedtrue.push_back(newpositiontrue.z());
	newvalvecfixedtrue.push_back(valvecfixedtrue.at(3) - ttrueminus);
	newvalvecfixedtrue.push_back(newdirectiontrue.cosTheta());
	newvalvecfixedtrue.push_back(newdirectiontrue.phi());
	if(parnum == 7)
	  newvalvecfixedtrue.push_back(valvecfixedtrue.at(6));
	truevaluex = newvalvecfixedtrue.at(variablenumberx);
	truevaluey = newvalvecfixedtrue.at(variablenumbery);
	std::vector<double> newvalvecchanged;
	if(mode == "true")
	  newvalvecchanged = newvalvecfixedtrue;
	if(mode == "beforeminimize")
	  newvalvecchanged = newvalvecfixedbeforeminimize;
	if(mode == "minimized")
	  newvalvecchanged = newvalvecfixedminimized;
	int binxN = h1->GetXaxis()->GetNbins();
	int binyN = h1->GetYaxis()->GetNbins();
	for(int i = 1;i < binxN + 1 ;i++)
	  {
	    for(int j = 1;j < binyN + 1 ;j++)
	      {
		double xval = h1->GetXaxis()->GetBinCenter(i);
		double yval = h1->GetYaxis()->GetBinCenter(j);
		newvalvecchanged.at(variablenumberx) = xval;
		newvalvecchanged.at(variablenumbery) = yval;
		CLHEP::Hep3Vector newpositionchanged(newvalvecchanged.at(0),newvalvecchanged.at(1),newvalvecchanged.at(2));
		CLHEP::Hep3Vector positionchanged = cross(mtrueInvert,newpositionchanged) + truepos;
		CLHEP::Hep3Vector newdirectionchanged;
		newdirectionchanged.setRThetaPhi(1.,std::acos(newvalvecchanged.at(4)),newvalvecchanged.at(5));
		CLHEP::Hep3Vector directionchanged = cross(mtrueInvert,newdirectionchanged);
		std::vector<double> valvecchanged;
		valvecchanged.push_back(positionchanged.x());
		valvecchanged.push_back(positionchanged.y());
		valvecchanged.push_back(positionchanged.z());
		valvecchanged.push_back(newvalvecchanged.at(3) + ttrueminus);
		valvecchanged.push_back(directionchanged.cosTheta());
		valvecchanged.push_back(directionchanged.phi());
		if(parnum == 7)
		  valvecchanged.push_back(newvalvecchanged.at(6));
		double value = 0;
		if(funcname == "returnvalue")
		  value = func->returnvaluecontents(valvecchanged);
		h1->Fill(xval,yval,value);
	      }
	  }
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
  std::vector<double> returnval;
  returnval.push_back(minimizedvaluex);
  returnval.push_back(minimizedvaluey);
  returnval.push_back(beforeminimizevaluex);
  returnval.push_back(beforeminimizevaluey);
  returnval.push_back(truevaluex);
  returnval.push_back(truevaluey);
  return returnval;
}

void AnalizeManager::SetTH2DFunctionDisTrueaxismultievent(TH2D* h1,std::string funcname,int parnum,int variablenumberx,int variablenumbery,std::string mode,int nevent,std::string flistname,std::string minimizedfuncname)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	if(minimizedfuncname == "default")
	  (*iterin).second.GetTagstring("MinimizeFunctionName",minimizedfuncname);
	MinimizedFunction* func = new MinimizedFunction(minimizedfuncname.c_str(),(*iterin).second,data,parnum);
	for(int ievent = 0;ievent < nevent;ievent++){
	  func->SetEventNumber(ievent);
	  std::vector<double> valvecfixedtrue;
	  std::vector<double> valvecfixedbeforeminimize;
	  std::vector<double> valvecfixedminimized;
	  for(int i = 0; i < parnum;i++)
	    {
	      double valtrue = 0;
	      double valbeforeminimize = 0.;
	      double valminimized = 0.;
	      valtrue = func->GetTruevalue(i);
	      std::cout << "i = " << i << " : true value = " << valtrue << std::endl;
	      valbeforeminimize = func->Getfirstvalue()[i];
	      std::cout << "i = " << i << " : before minimize value = " << valbeforeminimize << std::endl;
	      if(data->reconstructdataminimize){
		valminimized = data->reconstructdataminimize->GetParameter(i);
		std::cout << "i = " << i << " : minimized value = " << valminimized << std::endl;
	      }
	      valvecfixedtrue.push_back(valtrue);
	      valvecfixedbeforeminimize.push_back(valbeforeminimize);
	      valvecfixedminimized.push_back(valminimized);
	    }
	  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
	  double truedirx = track->GetPdir(0);
	  double truediry = track->GetPdir(1);
	  double truedirz = track->GetPdir(2);
	  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
	  TMatrixD mtrue = rotation3D(dir);
	  TMatrixD mtrueInvert = rotation3D(dir).Invert();
	  CLHEP::Hep3Vector positionminimized(valvecfixedminimized.at(0),valvecfixedminimized.at(1),valvecfixedminimized.at(2));
	  CLHEP::Hep3Vector truepos(data->wcsimrootevent->GetTrigger(0)->GetVtx(0),data->wcsimrootevent->GetTrigger(0)->GetVtx(1),data->wcsimrootevent->GetTrigger(0)->GetVtx(2));
	  CLHEP::Hep3Vector newpositionminimized = cross(mtrue,positionminimized - truepos);
	  double costhetaminimized = valvecfixedminimized.at(4);
	  double phiminimized = valvecfixedminimized.at(5);
	  if(costhetaminimized > 1.)
	    {
	      costhetaminimized = 2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  else if(costhetaminimized < -1.)
	    {
	      costhetaminimized = -2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  CLHEP::Hep3Vector directionminimized;
	  directionminimized.setRThetaPhi(1.,std::acos(costhetaminimized),phiminimized);
	  CLHEP::Hep3Vector newdirectionminimized = cross(mtrue,directionminimized);
	  double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
	  ttrueminus = -ttrueminus;
	  std::vector<double> newvalvecfixedminimized;
	  newvalvecfixedminimized.push_back(newpositionminimized.x());
	  newvalvecfixedminimized.push_back(newpositionminimized.y());
	  newvalvecfixedminimized.push_back(newpositionminimized.z());
	  newvalvecfixedminimized.push_back(valvecfixedminimized.at(3) - ttrueminus);
	  newvalvecfixedminimized.push_back(newdirectionminimized.cosTheta());
	  newvalvecfixedminimized.push_back(newdirectionminimized.phi());
	  if(parnum == 7)
	    newvalvecfixedminimized.push_back(valvecfixedminimized.at(6));
	  CLHEP::Hep3Vector positionbeforeminimize(valvecfixedbeforeminimize.at(0),valvecfixedbeforeminimize.at(1),valvecfixedbeforeminimize.at(2));
	  CLHEP::Hep3Vector newpositionbeforeminimize = cross(mtrue,positionbeforeminimize - truepos);
	  double costhetabeforeminimize = valvecfixedbeforeminimize.at(4);
	  double phibeforeminimize = valvecfixedbeforeminimize.at(5);
	  CLHEP::Hep3Vector directionbeforeminimize;
	  directionbeforeminimize.setRThetaPhi(1.,std::acos(costhetabeforeminimize),phibeforeminimize);
	  CLHEP::Hep3Vector newdirectionbeforeminimize = cross(mtrue,directionbeforeminimize);
	  std::vector<double> newvalvecfixedbeforeminimize;
	  newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.x());
	  newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.y());
	  newvalvecfixedbeforeminimize.push_back(newpositionbeforeminimize.z());
	  newvalvecfixedbeforeminimize.push_back(valvecfixedbeforeminimize.at(3) - ttrueminus);
	  newvalvecfixedbeforeminimize.push_back(newdirectionbeforeminimize.cosTheta());
	  newvalvecfixedbeforeminimize.push_back(newdirectionbeforeminimize.phi());
	  if(parnum == 7)
	    newvalvecfixedbeforeminimize.push_back(valvecfixedbeforeminimize.at(6));
	  CLHEP::Hep3Vector positiontrue(valvecfixedtrue.at(0),valvecfixedtrue.at(1),valvecfixedtrue.at(2));
	  CLHEP::Hep3Vector newpositiontrue = cross(mtrue,positiontrue - truepos);
	  double costhetatrue = valvecfixedtrue.at(4);
	  double phitrue = valvecfixedtrue.at(5);
	  CLHEP::Hep3Vector directiontrue;
	  directiontrue.setRThetaPhi(1.,std::acos(costhetatrue),phitrue);
	  CLHEP::Hep3Vector newdirectiontrue = cross(mtrue,directiontrue);
	  std::vector<double> newvalvecfixedtrue;
	  newvalvecfixedtrue.push_back(newpositiontrue.x());
	  newvalvecfixedtrue.push_back(newpositiontrue.y());
	  newvalvecfixedtrue.push_back(newpositiontrue.z());
	  newvalvecfixedtrue.push_back(valvecfixedtrue.at(3) - ttrueminus);
	  newvalvecfixedtrue.push_back(newdirectiontrue.cosTheta());
	  newvalvecfixedtrue.push_back(newdirectiontrue.phi());
	  if(parnum == 7)
	    newvalvecfixedtrue.push_back(valvecfixedtrue.at(6));
	  std::vector<double> newvalvecchanged;
	  if(mode == "true")
	    newvalvecchanged = newvalvecfixedtrue;
	  if(mode == "beforeminimize")
	    newvalvecchanged = newvalvecfixedbeforeminimize;
	  if(mode == "minimized")
	    newvalvecchanged = newvalvecfixedminimized;
	  int binxN = h1->GetXaxis()->GetNbins();
	  int binyN = h1->GetYaxis()->GetNbins();
	  for(int i = 1;i < binxN + 1 ;i++)
	    {
	      for(int j = 1;j < binyN + 1 ;j++)
		{
		  double xval = h1->GetXaxis()->GetBinCenter(i);
		  double yval = h1->GetYaxis()->GetBinCenter(j);
		  newvalvecchanged.at(variablenumberx) = xval;
		  newvalvecchanged.at(variablenumbery) = yval;
		  CLHEP::Hep3Vector newpositionchanged(newvalvecchanged.at(0),newvalvecchanged.at(1),newvalvecchanged.at(2));
		  CLHEP::Hep3Vector positionchanged = cross(mtrueInvert,newpositionchanged) + truepos;
		  CLHEP::Hep3Vector newdirectionchanged;
		  newdirectionchanged.setRThetaPhi(1.,std::acos(newvalvecchanged.at(4)),newvalvecchanged.at(5));
		  CLHEP::Hep3Vector directionchanged = cross(mtrueInvert,newdirectionchanged);
		  std::vector<double> valvecchanged;
		  valvecchanged.push_back(positionchanged.x());
		  valvecchanged.push_back(positionchanged.y());
		  valvecchanged.push_back(positionchanged.z());
		  valvecchanged.push_back(newvalvecchanged.at(3) + ttrueminus);
		  valvecchanged.push_back(directionchanged.cosTheta());
		  valvecchanged.push_back(directionchanged.phi());
		  if(parnum == 7)
		    valvecchanged.push_back(newvalvecchanged.at(6));
		  double value = 0.;
		  if(funcname == "returnvalue")
		    value = func->returnvaluecontents(valvecchanged);
		  h1->SetBinContent(i,j,h1->GetBinContent(i,j) + value);
		  //		  h1->Fill(xval,yval,value); 
		}
	    }
	}
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

void AnalizeManager::SetTH2DCorrectionCoefficient(TH2D* h1,std::string flistname){
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	std::vector<double> vaveraged(7,0.);
	std::vector<double> vsum(7,0.);
	std::vector<double> c(7,0.);
	int nevent = data->GetEntriesMin();
	int ntrigger = 0;
	for(int ievent = 0;ievent < nevent;ievent++){
	  data->GetEntry(ievent);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    ntrigger++;
	    for(int param = 0;param < 7;param++){
	      double y = data->reconstructdataminimize->GetParameter(param) - c[param];
	      double t = vsum[param] + y;
	      c[param] = (t - vsum[param]) - y;
	      vsum[param] = t;
	    }
	  }
	}
	for(int param = 0;param < 7;param++){
	  vaveraged[param] = vsum[param]/(double)ntrigger;
	}
	std::vector<double> vsumpower(7,0.);
	std::vector<double> cpower(7,0.);
	std::vector<std::vector<double>> vsumcovariance(7,std::vector<double>(7,0.));
	std::vector<std::vector<double>> ccovariance(7,std::vector<double>(7,0.));
	for(int ievent = 0;ievent < nevent;ievent++){
	  data->GetEntry(ievent);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    ntrigger++;
	    for(int param = 0;param < 7;param++){
	      double power2difference = data->reconstructdataminimize->GetParameter(param) - vaveraged[param];
	      double ypower = power2difference*power2difference - cpower[param];
	      double tpower = vsumpower[param] + ypower;
	      cpower[param] = (tpower - vsumpower[param]) - ypower;
	      vsumpower[param] = tpower;
	      for(int param2 = 0;param2 < 7;param2++){
		double ycovariance = (data->reconstructdataminimize->GetParameter(param) - vaveraged[param])*(data->reconstructdataminimize->GetParameter(param2) - vaveraged[param2]) - ccovariance[param][param2];
		double tcovariance = vsumcovariance[param][param2] + ycovariance;
		ccovariance[param][param2] = ( tcovariance - vsumcovariance[param][param2] ) - ycovariance;
		vsumcovariance[param][param2] = tcovariance;
	      }
	    }
	  }
	}
	for(int param = 0;param < 7;param++){
	  for(int param2 = 0;param2 < 7;param2++){
	    h1->Fill((double)param,(double)param2,(vsumcovariance[param][param2]/ntrigger)/(std::sqrt(vsumpower[param]/ntrigger)*std::sqrt(vsumpower[param2]/ntrigger)));
	  }
	}
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

void AnalizeManager::SetTH2DCorrectionCoefficientTrueAxis(TH2D* h1,std::string flistname){
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      AnalizeFiledata* data = new AnalizeFiledata();
      try{
	data->Construct((*iterin).second);
	std::vector<double> vaveraged(5,0.);
	std::vector<double> vsum(5,0.);
	std::vector<double> c(5,0.);
	int nevent = data->GetEntriesMin();
	int ntrigger = 0;
	for(int ievent = 0;ievent < nevent;ievent++){
	  data->GetEntry(ievent);
	  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
	  double truedirx = track->GetPdir(0);
	  double truediry = track->GetPdir(1);
	  double truedirz = track->GetPdir(2);
	  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
	  TMatrixD mtrue = rotation3D(dir);
	  CLHEP::Hep3Vector positionminimized(data->reconstructdataminimize->GetParameter(0),data->reconstructdataminimize->GetParameter(1),data->reconstructdataminimize->GetParameter(2));
	  CLHEP::Hep3Vector positiontrue(data->wcsimrootevent->GetTrigger(0)->GetVtx(0),data->wcsimrootevent->GetTrigger(0)->GetVtx(1),data->wcsimrootevent->GetTrigger(0)->GetVtx(2));
	  CLHEP::Hep3Vector newpositionminimized = cross(mtrue,positionminimized - positiontrue);
	  double costhetaminimized = data->reconstructdataminimize->GetParameter(4);
	  double phiminimized = data->reconstructdataminimize->GetParameter(5);
	  if(costhetaminimized > 1.)
	    {
	      costhetaminimized = 2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  else if(costhetaminimized < -1.)
	    {
	      costhetaminimized = -2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  CLHEP::Hep3Vector directionminimized;
	  directionminimized.setRThetaPhi(1.,std::acos(costhetaminimized),phiminimized);
	  CLHEP::Hep3Vector newdirectionminimized = cross(mtrue,directionminimized);
	  double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
	  ttrueminus = -ttrueminus;
	  std::vector<double> rotvalue(5,0.);
	  rotvalue[0] = std::sqrt(newpositionminimized.x()*newpositionminimized.x()+newpositionminimized.y()*newpositionminimized.y());
	  rotvalue[1] = newpositionminimized.z();
	  rotvalue[2] = data->reconstructdataminimize->GetParameter(3) - ttrueminus;
	  rotvalue[3] = newdirectionminimized.cosTheta();
	  rotvalue[4] = data->reconstructdataminimize->GetParameter(6);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    ntrigger++;
	    for(int param = 0;param < 5;param++){
	      double y = rotvalue[param] - c[param];
	      double t = vsum[param] + y;
	      c[param] = (t - vsum[param]) - y;
	      vsum[param] = t;
	    }
	  }
	}
	for(int param = 0;param < 5;param++){
	  vaveraged[param] = vsum[param]/(double)ntrigger;
	}
	std::vector<double> vsumpower(5,0.);
	std::vector<double> cpower(5,0.);
	std::vector<std::vector<double>> vsumcovariance(5,std::vector<double>(5,0.));
	std::vector<std::vector<double>> ccovariance(5,std::vector<double>(5,0.));
	for(int ievent = 0;ievent < nevent;ievent++){
	  data->GetEntry(ievent);
	  WCSimRootTrack* track = (WCSimRootTrack*)data->wcsimrootevent->GetTrigger(0)->GetTracks()->At(0);
	  double truedirx = track->GetPdir(0);
	  double truediry = track->GetPdir(1);
	  double truedirz = track->GetPdir(2);
	  CLHEP::Hep3Vector dir(truedirx,truediry,truedirz);
	  TMatrixD mtrue = rotation3D(dir);
	  CLHEP::Hep3Vector positionminimized(data->reconstructdataminimize->GetParameter(0),data->reconstructdataminimize->GetParameter(1),data->reconstructdataminimize->GetParameter(2));
	  CLHEP::Hep3Vector positiontrue(data->wcsimrootevent->GetTrigger(0)->GetVtx(0),data->wcsimrootevent->GetTrigger(0)->GetVtx(1),data->wcsimrootevent->GetTrigger(0)->GetVtx(2));
	  CLHEP::Hep3Vector newpositionminimized = cross(mtrue,positionminimized - positiontrue);
	  double costhetaminimized = data->reconstructdataminimize->GetParameter(4);
	  double phiminimized = data->reconstructdataminimize->GetParameter(5);
	  if(costhetaminimized > 1.)
	    {
	      costhetaminimized = 2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  else if(costhetaminimized < -1.)
	    {
	      costhetaminimized = -2 - costhetaminimized;
	      phiminimized = phiminimized + PI;
	    }
	  CLHEP::Hep3Vector directionminimized;
	  directionminimized.setRThetaPhi(1.,std::acos(costhetaminimized),phiminimized);
	  CLHEP::Hep3Vector newdirectionminimized = cross(mtrue,directionminimized);
	  double ttrueminus = data->wcsimrootevent->GetTrigger(0)->GetTriggerTime();
	  ttrueminus = -ttrueminus;
	  std::vector<double> rotvalue(5,0.);
	  rotvalue[0] = std::sqrt(newpositionminimized.x()*newpositionminimized.x()+newpositionminimized.y()*newpositionminimized.y());
	  rotvalue[1] = newpositionminimized.z();
	  rotvalue[2] = data->reconstructdataminimize->GetParameter(3) - ttrueminus;
	  rotvalue[3] = newdirectionminimized.cosTheta();
	  rotvalue[4] = data->reconstructdataminimize->GetParameter(6);
	  int ncherenkovdigihits = data->wcsimrootevent->GetTrigger(0)->GetNcherenkovdigihits();
	  if(ncherenkovdigihits != 0){
	    ntrigger++;
	    for(int param = 0;param < 5;param++){
	      double power2difference = rotvalue[param] - vaveraged[param];
	      double ypower = power2difference*power2difference - cpower[param];
	      double tpower = vsumpower[param] + ypower;
	      cpower[param] = (tpower - vsumpower[param]) - ypower;
	      vsumpower[param] = tpower;
	      for(int param2 = 0;param2 < 5;param2++){
		double ycovariance = (rotvalue[param] - vaveraged[param])*(rotvalue[param2] - vaveraged[param2]) - ccovariance[param][param2];
		double tcovariance = vsumcovariance[param][param2] + ycovariance;
		ccovariance[param][param2] = ( tcovariance - vsumcovariance[param][param2] ) - ycovariance;
		vsumcovariance[param][param2] = tcovariance;
	      }
	    }
	  }
	}
	for(int param = 0;param < 5;param++){
	  for(int param2 = 0;param2 < 5;param2++){
	    h1->Fill((double)param,(double)param2,(vsumcovariance[param][param2]/ntrigger)/(std::sqrt(vsumpower[param]/ntrigger)*std::sqrt(vsumpower[param2]/ntrigger)));
	  }
	}
      }
      catch(std::string s){
	delete data;
	throw;
      }
      delete data;
    }
}

double AnalizeManager::EnergyToMeanOnRetrodirectp0(double r){
  if(r == 0.3)
    return -0.868781;
  if(r == 0.4)
    return -0.531386;
  if(r == 0.5)
    return -0.998907;
  if(r == 0.6)
    return -0.991192;
  if(r == 0.7)
    return -1.22726;
  if(r == 0.8)
    return -1.29283;
  if(r == 0.9)
    return -0.98739;
  if(r == 1.0)
    return -1.41003;
  return 0.;
}

double AnalizeManager::EnergyToMeanOnRetrodirectp1(double r){
  if(r == 0.3)
    return 6.56903;
  if(r == 0.4)
    return 6.55038;
  if(r == 0.5)
    return 6.59485;
  if(r == 0.6)
    return 6.60564;
  if(r == 0.7)
    return 6.64542;
  if(r == 0.8)
    return 6.65295;
  if(r == 0.9)
    return 6.63287;
  if(r == 1.0)
    return 6.68674;
  return 0.;
}

double AnalizeManager::EnergyToMeanOnRetroreflectp0(double r){
  if(r == 0.3)
    return 16.264;
  if(r == 0.4)
    return 12.6806;
  if(r == 0.5)
    return 11.3018;
  if(r == 0.6)
    return 9.28269;
  if(r == 0.7)
    return 8.51982;
  if(r == 0.8)
    return 7.00745;
  if(r == 0.9)
    return 6.40479;
  if(r == 1.0)
    return 5.42248;
  return 0.;
}

double AnalizeManager::EnergyToMeanOnRetroreflectp1(double r){
  if(r == 0.3)
    return 5.84489;
  if(r == 0.4)
    return 5.9987;
  if(r == 0.5)
    return 6.03188;
  if(r == 0.6)
    return 6.17281;
  if(r == 0.7)
    return 6.2274;
  if(r == 0.8)
    return 6.34717;
  if(r == 0.9)
    return 6.39847;
  if(r == 1.0)
    return 6.51299;
  return 0.;
}

double AnalizeManager::EnergyToSigmaOnRetrop0(double r){
  if(r == 0.3)
    return 3.64685;
  if(r == 0.4)
    return 2.79433;
  if(r == 0.5)
    return 2.31998;
  if(r == 0.6)
    return 1.80776;
  if(r == 0.7)
    return 1.54869;
  if(r == 0.8)
    return 1.40181;
  if(r == 0.9)
    return 1.32653;
  if(r == 1.0)
    return 1.21651;
  return 0.;
}

double AnalizeManager::EnergyToSigmaOnRetrop1(double r){
  if(r == 0.3)
    return 0.219654;
  if(r == 0.4)
    return 0.199021;
  if(r == 0.5)
    return 0.176755;
  if(r == 0.6)
    return 0.191857;
  if(r == 0.7)
    return 0.199432;
  if(r == 0.8)
    return 0.176121;
  if(r == 0.9)
    return 0.160562;
  if(r == 1.0)
    return 0.154897;
  return 0.;
}

double AnalizeManager::EnergyToSigmaOnRetrop2(double r){
  if(r == 0.3)
    return -0.00420937;
  if(r == 0.4)
    return -0.00292426;
  if(r == 0.5)
    return -0.00101282;
  if(r == 0.6)
    return -0.00149709;
  if(r == 0.7)
    return -0.00217282;
  if(r == 0.8)
    return -0.0010428;
  if(r == 0.9)
    return -0.000500239;
  if(r == 1.0)
    return -0.000252598;
  return 0.;
}

void AnalizeManager::PrintFilename()
{}

