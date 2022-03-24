// c++ STL
#include <cstring>
#include <sstream>
// ROOT library
#include <TH2D.h>
// self-introduced library
#include "OneRunAnalizeManager.hh"
#include "CSearch_range.hh"
#include "constants.hh"
#include "Tdistance_function.hh"
#include "Ttof.hh"
#include "MyString.hh"
#include "BiasError.hh"
#include "Tfunction.hh"
#include "Tfsumgoodness.hh"

OneRunAnalizeManager::OneRunAnalizeManager()
{
}

OneRunAnalizeManager::OneRunAnalizeManager(const char* datafile,const char* mode)
{
  std::string smode = mode;
  if(smode == "d")
    Setdatafile(datafile);
  if(smode == "g")
    SetGoodnessfile(datafile);
  if(smode == "l")
    SetLikelihoodfile(datafile);
  if(smode == "gm")
    SetGoodnessMinimizefile(datafile);
}


void OneRunAnalizeManager::Setdatafile(const char* datafile)
{
  if(datamanager)
    {
      std::cout << "data file is already exist!" << std::endl;
      throw "void OneRunAnalizeManager::Setdatafile(const char* datafile)";
    }
  datamanager = new OneRunDataAnalizeManager();
  datamanager->Setdatafile(datafile);
}

void OneRunAnalizeManager::SetGoodnessfile(const char* goodnessfile)
{
  if(datamanager)
    {
      std::cout << "data file is already exist!" << std::endl;
      throw "OneRunAnalizeManager::SetGoodnessfile(const char* goodnessfile)";
    }
  TFile* gfile = new TFile(goodnessfile);
  MyString* infiledataname = (MyString*)gfile->Get("infilename");
  datamanager = new OneRunDataAnalizeManager();
  datamanager->Setdatafile(infiledataname->Getstring().c_str());
  goodnessmanager = new OneRunGoodnessAnalizeManager();
  goodnessmanager->Setgoodnessfile(goodnessfile);
  delete gfile;
}

void OneRunAnalizeManager::SetLikelihoodfile(const char* likelihoodfile)
{
  if(datamanager)
    {
      std::cout << "data file is already exist!" << std::endl;
      throw "OneRunAnalizeManager::SetLikelihoodfile(const char* likelihoodfile)";
    }
  if(goodnessmanager)
    {
      std::cout << "goodness file is already exist!" << std::endl;
      throw "OnneRunAnalizeManager::SetLikelihoodfile(const char* likelihoodfile)";
    }
  TFile* lfile = new TFile(likelihoodfile);
  MyString* infiledataname = (MyString*)lfile->Get("infiledataname");
  MyString* infilegoodnessname = (MyString*)lfile->Get("infilegoodnessname");
  datamanager = new OneRunDataAnalizeManager();
  datamanager->Setdatafile(infiledataname->Getstring().c_str());
  goodnessmanager = new OneRunGoodnessAnalizeManager();
  goodnessmanager->Setgoodnessfile(infilegoodnessname->Getstring().c_str());
  likelihoodmanager = new OneRunLikelihoodAnalizeManager();
  likelihoodmanager->Setlikelihoodfile(likelihoodfile);
  delete lfile;
}

void OneRunAnalizeManager::SetGoodnessMinimizefile(const char* goodnessminimizefile)
{
  if(datamanager)
    {
      std::cout << "data file is already exist!" << std::endl;
      throw "OneRunAnalizeManager::SetGoodnessMinimizefile(const char* goodnessminimizefile)";
    }
  if(goodnessmanager)
    {
      std::cout << "goodness file is already exist!" << std::endl;
      throw "OneRunAnalizeManager::SetGoodnessMinimizefile(const char* goodnessminimizefile)";
    }
  if(likelihoodmanager)
    {
      std::cout << "likelihood file is already exist!" << std::endl;
      throw "OneRunAnalizeManager::SetGoodnessMinimizefile(const char* goodnessminimizefile)";
    }
  TFile* gmfile = new TFile(goodnessminimizefile);
  MyString* infiledataname = (MyString*)gmfile->Get("infiledataname_bygoodnessminimize");
  MyString* infilegoodnessname = (MyString*)gmfile->Get("infilegoodnessname_bygoodnessminimize");
  MyString* infilelikelihoodname = (MyString*)gmfile->Get("infilelikelihoodname_bygoodnessminimize");
  datamanager = new OneRunDataAnalizeManager();
  datamanager->Setdatafile(infiledataname->Getstring().c_str());
  goodnessmanager = new OneRunGoodnessAnalizeManager();
  goodnessmanager->Setgoodnessfile(infilegoodnessname->Getstring().c_str());
  likelihoodmanager = new OneRunLikelihoodAnalizeManager();
  likelihoodmanager->Setlikelihoodfile(infilelikelihoodname->Getstring().c_str());
  goodnessminimizemanager->Setgoodnessminimizefile(goodnessminimizefile);
  delete gmfile;
}


OneRunAnalizeManager::~OneRunAnalizeManager()
{
  if(datamanager)
    delete datamanager;
  if(goodnessmanager)
    delete goodnessmanager;
  if(likelihoodmanager)
    delete likelihoodmanager;
  if(goodnessminimizemanager)
    delete goodnessminimizemanager;
}


void OneRunAnalizeManager::GetTH2DEvent(TH2D* h1,int n,const char* xvar,const char* yvar)
{
  if(!h1)
    {
      std::cout << "hist is null!" << std::endl;
      throw "void OneRunAnalizeManager::GetTH2DEvent(TH2D* h1,const char* xvar,const char* yvar)";
    }
  
  for(int i = 0;i < n;i++)
    {
      if(datamanager->Getncherenkovdigihits(i) != 0)
	{
	  double xval = GetVariableEvent(xvar,i);
	  double yval = GetVariableEvent(yvar,i);
	  h1->Fill(xval,yval);
	}
    }
}

void OneRunAnalizeManager::GetTH2DHit(TH2D* h1,int n,const char* xvar,const char* yvar)
{
  if(!h1)
    {
      std::cout << "hist is null!" << std::endl;
      throw "void OneRunAnalizeManager::GetTH2DHit(TH2D* h1,const char* xvar,const char* yvar)";
    }
  for(int i = 0;i < n;i++)
    {
      for(int j = 0; j < datamanager->Getncherenkovdigihits(i); j++)
	{
	  double xval = GetVariableHit(xvar,i,j);
	  double yval = GetVariableHit(yvar,i,j);
	  h1->Fill(xval,yval);
	}
    }
}

void OneRunAnalizeManager::GetTH1DEvent(TH1D* h1,int n,const char* var)
{
  if(!h1)
    {
      std::cout << "hist is null!" << std::endl;
      throw "void OneRunAnalizeManager::GetTH1DEvent(TH1D* h1,const char* xvar)";
    }
  for(int i = 0; i < n;i++)
    {
      if(datamanager->Getncherenkovdigihits(i) != 0)
	{
	  double val = GetVariableEvent(var,i);
	  h1->Fill(val);
	}
      
    }
}

void OneRunAnalizeManager::GetTH1DHit(TH1D* h1,int n,const char* var)
{
  if(!h1)
    {
      std::cout << "hist is null!" << std::endl;
      throw "void OneRunAnalizeManager::GetTH1DHit(TH1D* h1,const char* xvar)";
    }
  for(int i = 0; i < n;i++)
    {
      for(int j = 0; j < datamanager->Getncherenkovdigihits(i);j++)
	{
	  double val = GetVariableHit(var,i,j);
	  h1->Fill(val);
	}
    }
}

void OneRunAnalizeManager::GetFuncmap1DTrue(TH1D* h1,const char* xvar,const char* yvar,int ievent)
{
  if(!h1)
    {
      std::cout << "hist is null!" << std::endl;
      throw "void OneRunAnalizeManager::GetFuncmap1DTrue(TH1D* h1,const char* xvar,const char* yvar,int ievent)";
    }
  std::string xvalname = xvar;
  std::string yvalname = yvar;
  double xval = h1->GetBinCenter(1);
  double xwidth = h1->GetBinWidth(1);
  Tfunction* function = nullptr;
  if(yvalname == "sumgoodnessnoretro")
    {
      function = new Tfsumgoodnessnoretro();
      function->Setsigma(goodnessminimizemanager->GetGoodnessMinimizeParameters()->goodnessminimizesigma);
      function->Setsigmaangle(goodnessminimizemanager->GetGoodnessMinimizeParameters()->sigmaangle);
    }
  if(yvalname == "sumgoodnesssum")
    {
      function = new Tfsumgoodnesssum();
      function->Setsigma(goodnessminimizemanager->GetGoodnessMinimizeParameters()->goodnessminimizesigma);
      function->Setsigmaangle(goodnessminimizemanager->GetGoodnessMinimizeParameters()->sigmaangle);
      function->Setonretrocorrection(goodnessminimizemanager->GetGoodnessMinimizeParameters()->onretrocorrection);
    }
  
  else
    {
      std::cout << "invalid yvalname " << yvalname << std::endl;
      throw "void OneRunAnalizeManager::GetFuncmap1DTrue(TH1D* h1,int n,const char* xvar,const char* yvar,int ievent)";
    }
  function->SetvHitInfo(datamanager->vhitinfo);
  for(int bin = 1;bin <= h1->GetNbinsX();bin++,xval += xwidth)
    {
      double x = datamanager->Getxvtx(ievent);
      double y = datamanager->Getyvtx(ievent);
      double z = datamanager->Getzvtx(ievent);
      double t = -datamanager->GetTriggerTime(ievent);
      double costheta = datamanager->Getdirection(ievent).CosTheta();
      double phi = datamanager->Getdirection(ievent).Phi();
      if(xvalname == "x")
	x = xval;
      if(xvalname == "y")
	y = xval;
      if(xvalname == "z")
	z = xval;
      if(xvalname == "t")
	t = xval;
      if(xvalname == "costheta")
	costheta = xval;
      if(xvalname == "phi")
	phi = xval;
      TLorentzVector vec(x,y,z,t);
      TVector3 dir;
      dir.SetMagThetaPhi(1.,std::acos(costheta),phi);
      TReconstructdata data;
      data.Set4Vector(vec);
      data.Setdirection(dir);
      function->SetReconstructdata(data);
      double value = function->returnvalue();
      h1->Fill(xval,value);
    }
  delete function;
}


double OneRunAnalizeManager::GetVariableEvent(const char* valname,int i)
{
  std::string s_valname = valname;
  if(s_valname == "tvertexbygoodness")
    {
      return goodnessmanager->GetT(i);
    }
  if(s_valname == "triggertimetrue")
    {
      return datamanager->GetTriggerTime(i);
    }
  if(s_valname == "xvertexbygoodness")
    {
      return goodnessmanager->GetX(i);
    }
  if(s_valname == "yvertexbygoodness")
    {
      return goodnessmanager->GetY(i);
    }
  if(s_valname == "zvertexbygoodness")
    {
      return goodnessmanager->GetZ(i);
    }
  if(s_valname == "goodness")
    {
      return goodnessmanager->Getgoodness(i);
    }
  if(s_valname == "ncherenkovdigihits")
    {
      return (double)datamanager->Getncherenkovdigihits(i);
    }
  if(s_valname == "xvertextrue")
    {
      return datamanager->Getxvtx(i);
    }
  if(s_valname == "yvertextrue")
    {
      return datamanager->Getyvtx(i);
    }
  if(s_valname == "zvertextrue")
    {
      return datamanager->Getzvtx(i);
    }
  if(s_valname == "xbiasgoodness")
    {
      return goodnessmanager->GetX(i) - datamanager->Getxvtx(i);
    }
  if(s_valname == "ybiasgoodness")
    {
      return goodnessmanager->GetY(i) - datamanager->Getyvtx(i);
    }
  if(s_valname == "zbiasgoodness")
    {
      return goodnessmanager->GetZ(i) - datamanager->Getzvtx(i);
    }
  if(s_valname == "xbiasgoodnessminimize")
    {
      return goodnessminimizemanager->GetX(i) - datamanager->Getxvtx(i);
    }
  if(s_valname == "ybiasgoodnessminimize")
    {
      return goodnessminimizemanager->GetY(i) - datamanager->Getyvtx(i);
    }
  if(s_valname == "zbiasgoodnessminimize")
    {
      return goodnessminimizemanager->GetZ(i) - datamanager->Getzvtx(i);
    }
  
  if(s_valname == "angleerrorlikelihood")
    {
      return likelihoodmanager->GetDirection(i).Angle(datamanager->Getdirection(i));
    }
  if(s_valname == "angleerrorbygoodnessminimize")
    {
      return goodnessminimizemanager->GetDirection(i).Angle(datamanager->Getdirection(i));
    }
  std::cout << "invalid valname!" << std::endl;
  throw "OneRunAnalizeManager::GetVariable(const char* valname)";;
}

double OneRunAnalizeManager::GetVariableHit(const char* valname,int ievent,int jhit)
{
  std::string s_valname = valname;
  if(s_valname == "hittimeraw")
    {
      return datamanager->Gethittimeraw(ievent,jhit);
    }
  if(s_valname == "tofnoretrotrue")
    {
      return datamanager->Gettofnoretrotrue(ievent,jhit);
    }
  if(s_valname == "tofonretrotrue")
    {
      return datamanager->Gettofonretrotrue(ievent,jhit);
    }
  if(s_valname == "toferrornoretrotrue")
    {
      return datamanager->Gettoferrornoretrotrue(ievent,jhit);
    }
  if(s_valname == "toferroronretrotrue")
    {
      return datamanager->Gettoferroronretrotrue(ievent,jhit);
    }
  if(s_valname == "hittimetrue")
    {
      return datamanager->Gethittimetrue(ievent,jhit);
    }
  std::cout << "invalid valname!" << std::endl;
  throw "OneRunAnalizeManager::GetVariableHit(const char* valname,int ievent,int jhit)";
}

BiasError OneRunAnalizeManager::GetXBiasErrorbygoodness()
{
  CSearch_range range = goodnessmanager->GetCSearch_range();
  double histmin = -(range.GetXmax()-range.GetXmin())/2. - range.GetXwidth()/2;
  double histmax = (range.GetXmax()-range.GetXmin())/2. + range.GetXwidth()/2.;
  int histnum = range.GetXNum();
  TH1D* h1 = new TH1D("","",histnum,histmin,histmax);
  GetTH1DEvent(h1,goodnessmanager->Getnevent(),"xbiasgoodness");
  TF1* f1 = new TF1("f1","[0]*exp(-0.5*pow((x-[1])/[2],2))",h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  f1->SetParameters(goodnessmanager->Getnevent()/10.,0.,100.);
  h1->Fit("f1","0");
  double xbias = f1->GetParameter(1);
  double xbiaserror = f1->GetParError(1);
  double xerror = f1->GetParameter(2);
  double xerrorerror = f1->GetParError(2);
  BiasError biaserror;
  biaserror.bias = xbias;
  biaserror.biaserror = xbiaserror;
  biaserror.error = xerror;
  biaserror.errorerror = xerrorerror;
  delete f1;
  delete h1;
  return biaserror;
}

BiasError OneRunAnalizeManager::GetYBiasErrorbygoodness()
{
  CSearch_range range = goodnessmanager->GetCSearch_range();
  double histmin = -(range.GetYmax()-range.GetYmin())/2. - range.GetYwidth()/2;
  double histmax = (range.GetYmax()-range.GetYmin())/2. + range.GetYwidth()/2.;
  int histnum = range.GetYNum();
  TH1D* h1 = new TH1D("","",histnum,histmin,histmax);
  GetTH1DEvent(h1,goodnessmanager->Getnevent(),"ybiasgoodness");
  TF1* f1 = new TF1("f1","[0]*exp(-0.5*pow((x-[1])/[2],2))",h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  f1->SetParameters(goodnessmanager->Getnevent()/10.,0.,100.);
  h1->Fit("f1","0");
  double ybias = f1->GetParameter(1);
  double ybiaserror = f1->GetParError(1);
  double yerror = f1->GetParameter(2);
  double yerrorerror = f1->GetParError(2);
  BiasError biaserror;
  biaserror.bias = ybias;
  biaserror.biaserror = ybiaserror;
  biaserror.error = yerror;
  biaserror.errorerror = yerrorerror;
  delete f1;
  delete h1;
  return biaserror;
}

BiasError OneRunAnalizeManager::GetZBiasErrorbygoodness()
{
  CSearch_range range = goodnessmanager->GetCSearch_range();
  double histmin = -(range.GetZmax()-range.GetZmin())/2. - range.GetZwidth()/2;
  double histmax = (range.GetZmax()-range.GetZmin())/2. + range.GetZwidth()/2.;
  int histnum = range.GetZNum();
  TH1D* h1 = new TH1D("","",histnum,histmin,histmax);
  GetTH1DEvent(h1,goodnessmanager->Getnevent(),"zbiasgoodness");
  TF1* f1 = new TF1("f1","[0]*exp(-0.5*pow((x-[1])/[2],2))",h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  f1->SetParameters(goodnessmanager->Getnevent()/10.,0.,100.);
  h1->Fit("f1","0");
  double zbias = f1->GetParameter(1);
  double zbiaserror = f1->GetParError(1);
  double zerror = f1->GetParameter(2);
  double zerrorerror = f1->GetParError(2);
  BiasError biaserror;
  biaserror.bias = zbias;
  biaserror.biaserror = zbiaserror;
  biaserror.error = zerror;
  biaserror.errorerror = zerrorerror;
  delete f1;
  delete h1;
  return biaserror;
}

double OneRunAnalizeManager::angleerror1sigma()
{
  TH1D* h1 = new TH1D("","",10000,0.,3.141593);
  GetTH1DEvent(h1,likelihoodmanager->Getevent(),"angleerrorlikelihood");
  double all = h1->Integral();
  double angle = 0;
  double ratio = 0.6827;
  for(int min = 1;min < h1->GetNbinsX();min++)
    {
      double integral = h1->Integral(1,min);
      if(integral/all > ratio)
	{
	  angle = h1->GetBinCenter(min);
	  break;
	}
    }
  delete h1;
  return angle;
}

  
