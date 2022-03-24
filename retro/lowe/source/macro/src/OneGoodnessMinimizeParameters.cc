// c++ STL
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
// self
#include "OneGoodnessMinimizeParameters.hh"

ClassImp(OneGoodnessMinimizeParameters)

void OneGoodnessMinimizeParameters::Setpair(std::string filename)
{
  file = filename;
  vp.clear();
  size_t lastslashpos = filename.rfind("/");
  if(lastslashpos == std::string::npos)
    {
    }
  else
    {
      filename.erase(filename.begin(),filename.begin() + lastslashpos);
    }
  for(int i = 0 ; i < 5 ; i++)
    {
      filename.pop_back();
    }
  std::cout << "filename is " << filename << std::endl;
  std::string tempUp;
  std::string tempvalue;
  std::pair<std::string,std::string> ptemp;
  bool preup = false;
  for(auto itr =filename.begin(); itr != filename.end();itr++)
    {
      unsigned char c = static_cast<unsigned char>(*itr);
      bool bup = (bool)std::isupper(c);
      if(bup && preup)
	{
	  tempUp += *itr;
	}
      if(!bup)
	{
	  tempvalue += *itr;
	}
      if(bup && !preup)
	{
	  ptemp = make_pair(tempUp,tempvalue);
	  vp.push_back(ptemp);
	  tempUp.clear();
	  tempvalue.clear();
	  tempUp += *itr;
	}
      preup = bup;
    }
  ptemp = make_pair(tempUp,tempvalue);
  vp.push_back(ptemp);
  vp.erase(vp.begin());
}

void OneGoodnessMinimizeParameters::SetValue()
{
  std::vector<std::string> secondvec;
   for(auto itr = vp.begin(); itr != vp.end(); itr++)
    {
      if((*itr).first == "DET")
	{
	  if((*itr).second == "sk")
	    detector = SK;
	  else if((*itr).second == "hk")
	    detector = HK;
	  else
	    {
	    std::cout << "invalid detector value!" << std::endl;
	    throw "void OneLikelihoodParamters::SetValue()";
	    
	    }
	  
	}
      else if((*itr).first == "P")
	{
	  if((*itr).second == "e")
	    particle = electron;
	  else if((*itr).second == "ep")
	    particle = positron;
	  else if((*itr).second == "mu")
	    particle = muon;
	  else if((*itr).second == "mup")
	    particle = antimuon;
	  else if((*itr).second == "p")
	    particle = proton;
	  else
	    {
	      std::cout << "invalid detector value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "POS")
	{
	  secondvec = split((*itr).second);
	  if(secondvec[0] == "f")
	    {
	      postype = postype_fixed;
	      fixedPosition.SetXYZ(atof(secondvec[1].c_str()),atof(secondvec[2].c_str()),atof(secondvec[3].c_str()));
	    }
	  else if(secondvec[0] == "ur")
	    {
	      postype = postype_uniformrandom;
	      uniformPositionmin.SetXYZ(atof(secondvec[1].c_str()),atof(secondvec[3].c_str()),atof(secondvec[5].c_str()));
	      uniformPositionmax.SetXYZ(atof(secondvec[2].c_str()),atof(secondvec[4].c_str()),atof(secondvec[6].c_str()));
	    }
	  else
	    {
	      std::cout << "invalid position value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "DIR")
	{
	  secondvec = split((*itr).second);
	  if(secondvec[0] == "f")
	    {
	      dirtype = dirtype_fixed;
	      fixedcostheta = atof(secondvec[1].c_str());
	      fixedphi = atof(secondvec[2].c_str());
	    }
	  else if(secondvec[0] == "ur")
	    {
	      dirtype = dirtype_uniformrandom;
	      uniformcosthetamin = atof(secondvec[1].c_str());
	      uniformcosthetamax = atof(secondvec[2].c_str());
	      uniformphimin = atof(secondvec[3].c_str());
	      uniformphimax = atof(secondvec[4].c_str());
	    }
	  else
	    {
	      std::cout << "invalid Direction value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "E")
	{
	  secondvec = split((*itr).second);
	  if(secondvec[0] == "f")
	    {
	      etype = etype_fixed;
	      fixedenergy = atof(secondvec[1].c_str());
	    }
	  else if(secondvec[0] == "ur")
	    {
	      etype = etype_uniformrandom;
	      uniformenergymin = atof(secondvec[1].c_str());
	      uniformenergymax = atof(secondvec[1].c_str());
	    }
	  else
	    {
	      std::cout << "invalid energy value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "RF")
	{
	  secondvec = split((*itr).second);
	  if((*itr).second == "bs")
	    {
	      inforeflectivity = Inforeflectivity_blacksheet;
	    }
	  else if((*itr).second == "con")
	    {
	      inforeflectivity = Inforeflectivity_conventional;
	    }
	  else if(secondvec[0] == "tz")
	    {
	      inforeflectivity = Inforeflectivity_trapezoid;
	      trapezoidreflectivity = atof(secondvec[1].c_str());
	      trapezoidanglemin = atof(secondvec[2].c_str());
	      trapezoidanglemax = atof(secondvec[3].c_str());
	    }
	  else
	    {
	      std::cout << "invalid inforeflectivity value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "RS")
	{
	  if((*itr).second == "bs")
	    {
	      reflectspread = Reflectspread_blacksheet;
	    }
	  else if((*itr).second == "ns")
	    {
	      reflectspread = nospread;
	    }
	  else
	    {
	      std::cout << "invalid reflectspread value!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "TT")
	{
	  triggerthereshold = atoi((*itr).second.c_str());
	}
      else if((*itr).first == "TW")
	{
	  triggerwindow = atoi((*itr).second.c_str());
	}
      else if((*itr).first == "PR")
	{
	  triggerprewindow = atof((*itr).second.c_str());
	}
      else if((*itr).first == "PO")
	{
	  triggerpostwindow = atof((*itr).second.c_str());
	}
      else if((*itr).first == "DR")
	{
	  darkrate = atof((*itr).second.c_str());
	}
      else if((*itr).first == "AN")
	{
	  if((*itr).second == "t")
	    {
	      adjustfornoise = true;
	    }
	  else if((*itr).second == "f")
	    {
	      adjustfornoise = false;
	    }
	  else
	    {
	      std::cout << "invalid adjust for noise parameter!" << std::endl;
	      throw "void OneLikelihoodParamters::SetValue()";
	    }
	}
      else if((*itr).first == "N")
	{
	  eventnumber = atoi((*itr).second.c_str());
	}
      else if((*itr).first == "SIG")
	{
	  sigma = atof((*itr).second.c_str());
	}
      else if((*itr).first == "GT")
	{
	  if((*itr).second == "nr")
	    {
	      goodnesstype = GoodnessType_noretro;
	    }
	  else if((*itr).second == "or")
	    {
	      goodnesstype = GoodnessType_onretro;
	    }
	  else if((*itr).second == "s")
	    {
	      goodnesstype = GoodnessType_sum;
	    }
	  else if((*itr).second == "c")
	    {
	      goodnesstype = GoodnessType_compare;
	    }
	  else
	    {
	      std::cout << "invalid goodness type parameter!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "GR")
	{
	  secondvec = split((*itr).second);
	  if((*itr).second == "t")
	    {
	      goodnesssearchrangetype = GSRT_true;
	    }
	  else if(secondvec[0] == "n")
	    {
	      goodnesssearchrangetype = GSRT_normal;
	      TLorentzVector searchmin;
	      TLorentzVector searchwidth;
	      C4Number searchnumber;
	      searchnumber.SetX(atoi(secondvec[1].c_str()));
	      searchmin.SetX(atof(secondvec[2].c_str()));
	      searchwidth.SetX(atof(secondvec[3].c_str()));
	      searchnumber.SetY(atoi(secondvec[4].c_str()));
	      searchmin.SetY(atof(secondvec[5].c_str()));
	      searchwidth.SetY(atof(secondvec[6].c_str()));
	      searchnumber.SetZ(atoi(secondvec[7].c_str()));
	      searchmin.SetZ(atof(secondvec[8].c_str()));
	      searchwidth.SetZ(atof(secondvec[9].c_str()));
	      searchnumber.SetT(atoi(secondvec[10].c_str()));
	      searchmin.SetT(atof(secondvec[11].c_str()));
	      searchwidth.SetT(atof(secondvec[12].c_str()));
	      searchrange.Setmin(searchmin);
	      searchrange.Setwidth(searchwidth);
	      searchrange.SetNum(searchnumber);
	    }
	  else
	    {
	      std::cout << "invalid GSRT value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "GN")
	{
	  goodnesseventnumber = atoi((*itr).second.c_str());
	}
      else if((*itr).first == "LT")
	{
	  if((*itr).second == "nr")
	    likelihoodtype = LikelihoodType_noretro;
	  else if((*itr).second == "or")
	    likelihoodtype = LikelihoodType_onretro;
	  else if((*itr).second == "s")
	    likelihoodtype = LikelihoodType_sum;
	  else
	    {
	      std::cout << "invalid LT value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "NF")
	{
	  if((*itr).second == "n")
	    noretrofdirection = NoRetroFdirection_notuse;
	  else if((*itr).second == "p")
	    noretrofdirection = NoRetroFdirection_prototype;
	  else if((*itr).second == "d")
	    noretrofdirection = NoRetroFdirection_bydata;
	  else
	    {
	      std::cout << "invalid NF value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "OF")
	{
	  if((*itr).second == "n")
	    onretrofdirection = OnRetroFdirection_notuse;
	  else if((*itr).second == "p")
	    onretrofdirection = OnRetroFdirection_prototype;
	  else if((*itr).second == "d")
	    onretrofdirection = OnRetroFdirection_bydata;
	  else
	    {
	      std::cout << "invalid OF value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "NA")
	{
	  if((*itr).second == "n")
	    noretroafunction = NoRetroAfunction_notuse;
	  else if((*itr).second == "p")
	    noretroafunction = NoRetroAfunction_prototype;
	  else
	    {
	      std::cout << "invalid NA value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "OA")
	{
	  if((*itr).second == "n")
	    onretroafunction = OnRetroAfunction_notuse;
	  else if((*itr).second == "p")
	    onretroafunction = OnRetroAfunction_prototype;
	  else
	    {
	      std::cout << "invalid OA value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "LR")
	{
	  secondvec = split((*itr).second);
	  if((*itr).second == "t")
	    likelihoodsearchrangetype = likelihoodsearchrangetype_true;
	  else if(secondvec[0] == "n")
	    {
	      likelihoodsearchrangetype = likelihoodsearchrangetype_normal;
	      costhetanum = atof(secondvec[1].c_str());
	      phinum = atof(secondvec[2].c_str());
	    }
	  else
	    {
	      std::cout << "invalid LR value!" << std::endl;
	      throw "void OneLikelihoodParameters::SetValue()";
	    }
	}
      else if((*itr).first == "WN")
	{
	  timewindownoretro = atof((*itr).second.c_str());
	}
      else if((*itr).first == "WO")
	{
	  timewindowonretro = atof((*itr).second.c_str());
	}
      else if((*itr).first == "GMT")
	{
	  if( (*itr).second == "nr")
	    goodnessminimizetype = GoodnessMinimizeType_noretro;
	  if( (*itr).second == "s")
	    goodnessminimizetype = GoodnessMinimizeType_sum;
	}
      else if((*itr).first == "TO")
	{
	  tolerance = atof((*itr).second.c_str());
	}
      else if((*itr).first == "GST")
	{
	  secondvec = split((*itr).second);
	  stepx = atoi(secondvec[0].c_str());
	  stepy = atoi(secondvec[1].c_str());
	  stepz = atoi(secondvec[2].c_str());
	  stept = atoi(secondvec[3].c_str());
	  stepcostheta = atoi(secondvec[4].c_str());
	  stepphi = atoi(secondvec[5].c_str());
	}
      else if((*itr).first == "GMS")
	{
	  goodnessminimizesigma = atof((*itr).second.c_str());
	}
      else if((*itr).first == "SA")
	{
	  sigmaangle = atof((*itr).second.c_str());
	}
      else if((*itr).first == "RC")
	{
	  secondvec = split((*itr).second);
	  if( (*itr).second == "n")
	    onretrocorrectiontype = OnRetroCorrectionType_notuse;
	  else if( secondvec[0] == "u")
	    {
	      onretrocorrectiontype = OnRetroCorrectionType_use;
	      onretrocorrection = atof(secondvec[1].c_str());
	    }
	}
      else
	{
	  std::cout << "invalid identifier value!" << std::endl;
	  throw "void OneLikelihoodParamters::SetValue()";
	}
    }
}

void OneGoodnessMinimizeParameters::PrintValue()
{
    if(detector == SK)
    std::cout << "detector is SK" << std::endl;
  if(detector == HK)
    std::cout << "detector is HK" << std::endl;
  if(particle == electron)
    std::cout << "particle is electron" << std::endl;
  if(particle == positron)
    std::cout << "particle is positron" << std::endl;
  if(particle == muon)
    std::cout << "particle is muon" << std::endl;
  if(particle == antimuon)
    std::cout << "particle is antimuon" << std::endl;
  if(particle == proton)
    std::cout << "particle is proton" << std::endl;
  if(postype == postype_fixed)
    {
      std::cout << "Position is fixed at (" << fixedPosition.X() << "," << fixedPosition.Y() << "," << fixedPosition.Z() << ")cm" << std::endl;
    }
  if(postype == postype_uniformrandom)
    {
      std::cout << "Position is uniform random in range of " << uniformPositionmin.X() << " < x < " << uniformPositionmax.X() << " , " << uniformPositionmin.Y() << " < y < " << uniformPositionmax.Y() << " , " << uniformPositionmin.Z() << " < z < " << uniformPositionmax.Z() << "(cm)" <<  std::endl;
    }
  if(dirtype == dirtype_fixed)
    {
      std::cout << "Direction is fixed at costheta = " << fixedcostheta << ", phi = " << fixedphi << std::endl;
    }
  if(dirtype == dirtype_uniformrandom)
    {
      std::cout << "Direction is uniform random in range of " << uniformcosthetamin << " < costheta < " << uniformcosthetamax << " , " << uniformphimin << " < phi < " << uniformphimax << std::endl;
    }
  if(inforeflectivity == Inforeflectivity_blacksheet)
    {
      std::cout << "blacksheet is using" << std::endl;
    }
  if(inforeflectivity == Inforeflectivity_conventional)
    {
      std::cout << "conventional reflectivity calculate" << std::endl;
    }
  if(inforeflectivity == Inforeflectivity_trapezoid)
    {
      std::cout << "trapezoid reflectivity shape, max = " << trapezoidreflectivity << ", anglemin = " << trapezoidanglemin << "(deg), anglemax = " << trapezoidanglemax << "(deg)" << std::endl;
    }
  if(reflectspread == Reflectspread_blacksheet)
    {
      std::cout << "reflectspread type is blacksheet" << std::endl;
    }
  if(reflectspread == nospread)
    {
      std::cout << "reflectspread type is nospread" << std::endl;
    }
  std::cout << "trigger thereshold is " << triggerthereshold << std::endl;
  std::cout << "triggerwindow is " << triggerwindow << "(ns)" << std::endl;
  std::cout << "triggerprewindow is " << triggerprewindow << "(ns)" << std::endl;
  std::cout << "triggerpostwindow is " << triggerpostwindow << "(ns)" << std::endl;
  if(adjustfornoise == true)
    std::cout << "adjust for noise is on" << std::endl;
  if(adjustfornoise == false)
    std::cout << "adjust for noise is off" << std::endl;
  std::cout << "eventnumber is " << eventnumber << std::endl;

  std::cout << "sigma is " << sigma << "(ns)" << std::endl;
  if(goodnesstype == GoodnessType_noretro)
    std::cout << "goodness type is no retro" << std::endl;
  if(goodnesstype == GoodnessType_onretro)
    std::cout << "goodness type is on retro" << std::endl;
  if(goodnesstype == GoodnessType_sum)
    std::cout << "goodness type is sum" << std::endl;
  if(goodnesstype == GoodnessType_compare)
    std::cout << "goodness type is compare" << std::endl;
  if(goodnesssearchrangetype == GSRT_true)
    std::cout << "goodness search range type is true" << std::endl;
  if(goodnesssearchrangetype == GSRT_normal)
    {
      std::cout << "goodness search range type is normal" << std::endl;
      searchrange.Printrange();
    }
  std::cout << "goodness event number is " << goodnesseventnumber << std::endl;
  if(likelihoodtype == LikelihoodType_noretro)
    std::cout << "likelihood type is noretro" << std::endl;
  if(likelihoodtype == LikelihoodType_onretro)
    std::cout << "likelihood type is onretro" << std::endl;
  if(likelihoodtype == LikelihoodType_sum)
    std::cout << "lieklihood type is sum" << std::endl;
  if(noretrofdirection == NoRetroFdirection_notuse)
    std::cout << "no retro fdirection is not use" << std::endl;
  if(noretrofdirection == NoRetroFdirection_prototype)
    std::cout << "no retro fdirection is prototype" << std::endl;
  if(noretrofdirection == NoRetroFdirection_bydata)
    std::cout << "no retro fdirection is bydata" << std::endl;
  if(onretrofdirection == OnRetroFdirection_notuse)
    std::cout << "on retro fdirection is not use" << std::endl;
  if(onretrofdirection == OnRetroFdirection_prototype)
    std::cout << "on retro fdirection is prototype" << std::endl;
  if(onretrofdirection == OnRetroFdirection_bydata)
    std::cout << "on retro fdirection is bydata" << std::endl;
  if(noretroafunction == NoRetroAfunction_notuse)
    std::cout << "no retro afunction is not use" << std::endl;
  if(noretroafunction == NoRetroAfunction_prototype)
    std::cout << "no retro afunction is prototype" << std::endl;
  if(onretroafunction == OnRetroAfunction_notuse)
    std::cout << "on retro afunction is not use" << std::endl;
  if(onretroafunction == OnRetroAfunction_prototype)
    std::cout << "on retro afunction is prototype" << std::endl;
  if(likelihoodsearchrangetype == likelihoodsearchrangetype_true)
    std::cout << "likelihood search range type is true" << std::endl;
  if(likelihoodsearchrangetype == likelihoodsearchrangetype_normal)
    {
      std::cout << "likelihood search range type is normal" << std::endl;
      std::cout << "costheata number is " << costhetanum << std::endl;
      std::cout << "phi number is " << phinum << std::endl;
    }
  std::cout << "time window no retro is " << timewindownoretro << std::endl;
  std::cout << "time window on retro is " << timewindowonretro << std::endl;
  if(goodnessminimizetype == GoodnessMinimizeType_noretro)
    std::cout << "goodnessminimizetype is noretro" << std::endl;
  if(goodnessminimizetype == GoodnessMinimizeType_sum)
    std::cout << "goodnessminimizetype is sum" << std::endl;
  std::cout << "tolerance is " << tolerance << std::endl;
  std::cout << "step is (x,y,z,t,costheta,phi) = (" << stepx << "," << stepy << "," << stepz << "," << stept << "," << stepcostheta << "," << stepphi << ")" << std::endl;
  std::cout << "goodness minimize sigma is " << goodnessminimizesigma << std::endl;
  std::cout << "sigmaangle is " << sigmaangle << std::endl;
  if(onretrocorrectiontype == OnRetroCorrectionType_notuse)
    std::cout << "OnRetroCorectionType is not use" << std::endl;
  if(onretrocorrectiontype == OnRetroCorrectionType_use)
    std::cout << "onretrocorrection value is " << onretrocorrection << std::endl;
}

bool OneGoodnessMinimizeParameters::hasname(std::vector<std::string> vname,std::string name)
{
  for(auto itr = vname.begin(); itr != vname.end(); itr++)
    {
      if((*itr) == name)
	return true;
    }
  return false;
}

bool OneGoodnessMinimizeParameters::isEqual(OneGoodnessMinimizeParameters compare,std::vector<std::string> vexclusionname)
{
  if(!hasname(vexclusionname,"DET"))
    {
      if(compare.detector != detector)
	{
	  return false;
	}
      
    }
  if(!hasname(vexclusionname,"P"))
    {
      if(compare.particle != particle)
	{
	  return false;
	}
      
    }
  if(compare.postype != postype)
    {
      return false;
    }
  
  if(postype == postype_fixed)
    {
      if(!hasname(vexclusionname,"fPOSx"))
	{
	  if(compare.fixedPosition.X() != fixedPosition.X())
	    {
	      return false;
	    }
	  
	}
      if(!hasname(vexclusionname,"fPOSy"))
	{
	  if(compare.fixedPosition.Y() != fixedPosition.Y())
	    {
	      return false;
	    }
	  
	}
      if(!hasname(vexclusionname,"fPOSz"))
	{
	  if(compare.fixedPosition.Z() != fixedPosition.Z())
	    {
	      return false;
	    }
	  
	}
    }
  if(postype == postype_uniformrandom)
    {
      // undefined
    }
  if(compare.dirtype != dirtype)
    {
      return false;
    }
  
  if(dirtype == dirtype_fixed)
    {
      if(!hasname(vexclusionname,"fDIRcostheta"))
	{
	  if(compare.fixedcostheta != fixedcostheta)
	    {
	      return false;
	    }
	  
	}
      if(!hasname(vexclusionname,"fDIRphi"))
	{
	  if(compare.fixedphi != fixedphi)
	    {
	      return false;
	    }
	  
	}
    }
  if(dirtype == dirtype_uniformrandom)
    {
      // undefined
    }
  if(compare.etype != etype)
    {
      return false;
    }
  
  if(etype == etype_fixed)
    {
      if(!hasname(vexclusionname,"fE"))
	{
	  if(compare.fixedenergy != fixedenergy)
	    {
	      return false;
	    }
	  
	}
    }
  if(etype == etype_uniformrandom)
    {
      // undefined
    }
  if(compare.inforeflectivity != inforeflectivity)
    {
      return false;
    }
  
  if(inforeflectivity == Inforeflectivity_trapezoid)
    {
      if(!hasname(vexclusionname,"RFtrmax"))
	{
	  if(compare.trapezoidreflectivity != trapezoidreflectivity)
	    return false;
	}
      if(!hasname(vexclusionname,"RFtranglemin"))
	{
	  if(compare.trapezoidanglemin != trapezoidanglemin)
	    return false;
	}
      if(!hasname(vexclusionname,"RFtranglemax"))
	{
	  if(compare.trapezoidanglemax != trapezoidanglemax)
	    return false;
	}
    }
  if(compare.reflectspread != reflectspread)
    return false;
  if(!hasname(vexclusionname,"TT"))
    {
      if(compare.triggerthereshold != triggerthereshold)
	return false;
    }
  if(!hasname(vexclusionname,"TW"))
    {
      if(compare.triggerwindow != triggerwindow)
	return false;
    }
  if(!hasname(vexclusionname,"PR"))
    {
      if(compare.triggerprewindow != triggerprewindow)
	return false;
    }
  if(!hasname(vexclusionname,"PO"))
    {
      if(compare.triggerpostwindow != triggerpostwindow)
	return false;
    }
  if(!hasname(vexclusionname,"DR"))
    {
      if(compare.darkrate != darkrate)
	return false;
    }
  if(compare.adjustfornoise != adjustfornoise)
    return false;
  if(!hasname(vexclusionname,"N"))
    {
      if(compare.eventnumber != eventnumber)
	return false;
    }
  if(!hasname(vexclusionname,"SIG"))
    {
      if(compare.sigma != sigma)
	return false;
    }
  if(compare.goodnesssearchrangetype != goodnesssearchrangetype)
    return false;
  if(goodnesssearchrangetype == GSRT_true)
    {
    }
  if(goodnesssearchrangetype == GSRT_normal)
    {
      if(!hasname(vexclusionname,"GSRT_xmin"))
	{
	  if(searchrange.GetXmin() != compare.searchrange.GetXmin())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_ymin"))
	{
	  if(searchrange.GetYmin() != compare.searchrange.GetYmin())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_zmin"))
	{
	  if(searchrange.GetZmin() != compare.searchrange.GetZmin())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_tmin"))
	{
	  if(searchrange.GetTmin() != compare.searchrange.GetTmin())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_xwidth"))
	{
	  if(searchrange.GetXwidth() != compare.searchrange.GetXwidth())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_ywidth"))
	{
	  if(searchrange.GetYwidth() != compare.searchrange.GetYwidth())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_zwidth"))
	{
	  if(searchrange.GetZwidth() != compare.searchrange.GetZwidth())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_twidth"))
	{
	  if(searchrange.GetTwidth() != compare.searchrange.GetTwidth())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_xnum"))
	{
	  if(searchrange.GetXNum() != compare.searchrange.GetXNum())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_ynum"))
	{
	  if(searchrange.GetYNum() != compare.searchrange.GetYNum())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_znum"))
	{
	  if(searchrange.GetZNum() != compare.searchrange.GetZNum())
	    return false;
	}
      if(!hasname(vexclusionname,"GSRT_tnum"))
	{
	  if(searchrange.GetTNum() != compare.searchrange.GetTNum())
	    return false;
	}
    }
  if(!hasname(vexclusionname,"GN"))
    {
      if(goodnesseventnumber != compare.goodnesseventnumber)
	return false;
    }
  if(!hasname(vexclusionname,"LT"))
    {
      if(likelihoodtype != compare.likelihoodtype)
	return false;
    }
  if(!hasname(vexclusionname,"NF"))
    {
      if(noretrofdirection != compare.noretrofdirection)
	return false;
    }
  if(!hasname(vexclusionname,"OF"))
    {
      if(onretrofdirection != compare.onretrofdirection)
	return false;
    }
  if(!hasname(vexclusionname,"NA"))
    {
      if(noretroafunction != compare.noretroafunction)
	return false;
    }
  if(!hasname(vexclusionname,"OA"))
    {
      if(onretroafunction != compare.onretroafunction)
	return false;
    }
  if(likelihoodsearchrangetype != compare.likelihoodsearchrangetype)
    return false;
  if(likelihoodsearchrangetype == likelihoodsearchrangetype_true)
    {
    }
  if(likelihoodsearchrangetype == likelihoodsearchrangetype_normal)
    {
      if(!hasname(vexclusionname,"LSR_costhetaNum"))
	{
	  if(costhetanum != compare.costhetanum)
	    return false;
	}
      if(!hasname(vexclusionname,"LSR_phiNum"))
	{
	  if(phinum != compare.phinum)
	    return false;
	}
    }
  if(!hasname(vexclusionname,"WN"))
    {
      if(timewindownoretro != compare.timewindownoretro)
	return false;
    }
  if(!hasname(vexclusionname,"WO"))
    {
      if(timewindowonretro != compare.timewindowonretro)
	return false;
    }
  if(compare.goodnessminimizetype != goodnessminimizetype)
    return false;
  if(!hasname(vexclusionname,"TO"))
    {
      if(tolerance != compare.tolerance)
	return false;
    }
  if(!hasname(vexclusionname,"GSTx"))
    {
      if(stepx != compare.stepx)
	return false;
    }
  if(!hasname(vexclusionname,"GSTy"))
    {
      if(stepy != compare.stepy)
	return false;
    }
  if(!hasname(vexclusionname,"GSTz"))
    {
      if(stepz != compare.stepz)
	return false;
    }
  if(!hasname(vexclusionname,"GSTt"))
    {
      if(stept != compare.stept)
	return false;
    }
  if(!hasname(vexclusionname,"GSTcostheta"))
    {
      if(stepcostheta != compare.stepcostheta)
	return false;
    }
  if(!hasname(vexclusionname,"GSTphi"))
    {
      if(stepphi != compare.stepphi)
	return false;
    }
  if(!hasname(vexclusionname,"GMS"))
    {
      if(goodnessminimizesigma != compare.goodnessminimizesigma)
	return false;
    }
  if(!hasname(vexclusionname,"SA"))
    {
      if(sigmaangle != compare.sigmaangle)
	return false;
    }
  if(onretrocorrectiontype != compare.onretrocorrectiontype)
    return false;
  if(onretrocorrectiontype == OnRetroCorrectionType_notuse)
    {
    }
  if(onretrocorrectiontype == OnRetroCorrectionType_use)
    {
      if(!hasname(vexclusionname,"RCOvalue"))
	{
	  if(onretrocorrection != compare.onretrocorrection)
	    return false;
	}
    }
  return true;
}

std::vector<std::string> OneGoodnessMinimizeParameters::split(std::string& str)
{
  std::vector<std::string> v;
  std::istringstream ss(str);
  std::string buffer;
  while( std::getline(ss,buffer,'_'))
    {
      v.push_back(buffer);
    }
  return v;
}
