// c++ STL
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
// self-introduced library
#include "OneDataParameters.hh"

ClassImp(OneDataParameters)

void OneDataParameters::Setpair(std::string filename)
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

void OneDataParameters::SetValue()
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
	    throw "void OneDataParameters::SetValue()";
	    
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
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
	      throw "void OneDataParameters::SetValue()";
	    }
	}
      else if((*itr).first == "N")
	{
	  eventnumber = atoi((*itr).second.c_str());
	}
      else
	{
	  std::cout << "invalid identifier value!" << std::endl;
	  throw "void OneDataParameters::SetValue()";
	}
    }
}

void OneDataParameters::PrintValue()
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
}

bool OneDataParameters::hasname(std::vector<std::string> vname,std::string name)
{
  for(auto itr = vname.begin(); itr != vname.end(); itr++)
    {
      if((*itr) == name)
	return true;
    }
  return false;
}


bool OneDataParameters::isEqual(OneDataParameters compare,std::vector<std::string> vexclusionname)
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
  return true;
}


std::vector<std::string> OneDataParameters::split(std::string& str)
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

  
