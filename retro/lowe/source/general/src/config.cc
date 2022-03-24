
// c++ STL
#include <cstdlib>
#include <iostream>

// ROOT library
#include <TLorentzVector.h>

// self-introduced library
#include "CSearch_range.hh"
#include "AngleRange.hh"
#include "C4Number.hh"
#include "config.hh"
#include "GoodnessParameters.hh"
#include "EnumManager.hh"

char* Getchar(const char* envname)
{
  char* tempval = std::getenv(envname);
  if(tempval == nullptr){
    std::cout << "Environment variable " << envname << " is not exist" << std::endl;
    throw "Setchar(char*& val,const char* envname)";
  }
  else{
    return tempval;
  }
}

int Getint(const char* envname)
{
  const char* tempval = std::getenv(envname);
  char* endp;
  if(tempval == nullptr){
    std::cout << "Enviroment variable " << envname << " is not exist" << std::endl;
    throw "Setint(int& val,const char* envname)";
  }
  long lval = strtol(tempval,&endp,10);
  if(*endp != '\0'){
    std::cout << "invalid value is contained" << std::endl;
    throw "Setint(int& val,const char* envname)";
  }
  return (int)lval;
}
double Getdouble(const char* envname)
{
  const char* tempval = std::getenv(envname);
  char* endp;
  if(tempval == nullptr){
    std::cout << "Environment variable " << envname << " is not exist" << std::endl;
    throw "Setdouble(int& val,const char* envname)";
  }
  double valtemp = strtod(tempval,&endp);
  if(*endp != '\0'){
    std::cout << "invalid value is contained" << std::endl;
    throw "Setdouble(double& val,const char* envname)";
  }
  return valtemp;
}

CSearch_range GetCSearch_range(const char* envxmin,const char* envymin,const char* envzmin,const char* envtmin,const char* envxwidth,const char* envywidth,const char* envzwidth,const char* envtwidth,const char* envxnumber,const char* envynumber,const char* envznumber,const char* envtnumber)
{
  CSearch_range range;
  double xmin = Getdouble(envxmin);
  double ymin = Getdouble(envymin);
  double zmin = Getdouble(envzmin);
  double tmin = Getdouble(envtmin);
  double xwidth = Getdouble(envxwidth);
  double ywidth = Getdouble(envywidth);
  double zwidth = Getdouble(envzwidth);
  double twidth = Getdouble(envtwidth);
  int xnumber = Getint(envxnumber);
  int ynumber = Getint(envynumber);
  int znumber = Getint(envznumber);
  int tnumber = Getint(envtnumber);
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  range.Setmin(min);
  range.Setwidth(width);
  range.SetNum(number);
  return range;
}

AngleRange GetAngleRange(const char* envcosthetamin,const char* envcosthetawidth,const char* envcosthetanum,const char* envphimin,const char* envphiwidth,const char* envphinum)
{
  AngleRange range;
  range.SetCosthetamin(Getdouble(envcosthetamin));
  range.SetCosthetawidth(Getdouble(envcosthetawidth));
  range.SetCosthetaNum(Getint(envcosthetanum));
  range.SetPhimin(Getdouble(envphimin));
  range.SetPhiwidth(Getdouble(envphiwidth));
  range.SetPhiNum(Getint(envphinum));
  return range;
}


Config_goodness::Config_goodness(){
  infile = Getchar("INFILE");
  outtree = Getchar("OUTTREE");
  gfuncname = Getchar("GFUNCNAME");
  ogfuncname = Getchar("OGFUNCNAME");
  double xmin = Getdouble("XMIN");
  double ymin = Getdouble("YMIN");
  double zmin = Getdouble("ZMIN");
  double tmin = Getdouble("TMIN");
  double xwidth = Getdouble("XWIDTH");
  double ywidth = Getdouble("YWIDTH");
  double zwidth = Getdouble("ZWIDTH");
  double twidth = Getdouble("TWIDTH");
  int xnumber = Getint("XNUMBER");
  int ynumber = Getint("YNUMBER");
  int znumber = Getint("ZNUMBER");
  int tnumber = Getint("TNUMBER");
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  range.Setmin(min);
  range.Setwidth(width);
  range.SetNum(number);
  sigma = Getdouble("SIGMA");
}

Config_goodness_image::Config_goodness_image()
{
  infile_onretro = Getchar("INFILEONRETRO");
  infile_noretro = Getchar("INFILENORETRO");
  infile_compare = Getchar("INFILECOMPARE");
  chainname_onretro = Getchar("CHAINNAMEONRETRO");
  chainname_noretro = Getchar("CHAINNAMENORETRO");
  chainname_compare = Getchar("CHAINNAMECOMPARE");
  double xmin = Getdouble("XMIN");
  double ymin = Getdouble("YMIN");
  double zmin = Getdouble("ZMIN");
  double tmin = Getdouble("TMIN");
  double xwidth = Getdouble("XWIDTH");
  double ywidth = Getdouble("YWIDTH");
  double zwidth = Getdouble("ZWIDTH");
  double twidth = Getdouble("TWIDTH");
  int xnumber = Getint("XNUMBER");
  int ynumber = Getint("YNUMBER");
  int znumber = Getint("ZNUMBER");
  int tnumber = Getint("TNUMBER");
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  range.Setmin(min);
  range.Setwidth(width);
  range.SetNum(number);
  outfile_x = Getchar("OUTFILEX");
  outfile_y = Getchar("OUTFILEY");
  outfile_z = Getchar("OUTFILEZ");
}

Config_goodness_bias_err::Config_goodness_bias_err()
{
  infilehead_onretro = Getchar("INFILEHEADONRETRO");
  infilehead_noretro = Getchar("INFILEHEADNORETRO");
  //  infilehead_compare = Getchar("INFILEHEADCOMPARE");
  infiletail = Getchar("INFILETAIL");
  intreehead_onretro = Getchar("INTREEHEADONRETRO");
  intreehead_noretro = Getchar("INTREEHEADNORETRO");
  //  intreehead_compare = Getchar("INTREEHEADCOMPARE");
  intreetail = Getchar("INTREETAIL");
  outfile_x_bias = Getchar("OUTFILEXBIAS");
  outfile_y_bias = Getchar("OUTFILEYBIAS");
  outfile_z_bias = Getchar("OUTFILEZBIAS");
  outfile_x_err = Getchar("OUTFILEXERR");
  outfile_y_err = Getchar("OUTFILEYERR");
  outfile_z_err = Getchar("OUTFILEZERR");
  xnum = Getint("XNUM");
  xverwidth = Getdouble("XVERWIDTH");
  double xmin = Getdouble("XMIN");
  double ymin = Getdouble("YMIN");
  double zmin = Getdouble("ZMIN");
  double tmin = Getdouble("TMIN");
  double xwidth = Getdouble("XWIDTH");
  double ywidth = Getdouble("YWIDTH");
  double zwidth = Getdouble("ZWIDTH");
  double twidth = Getdouble("TWIDTH");
  int xnumber = Getint("XNUMBER");
  int ynumber = Getint("YNUMBER");
  int znumber = Getint("ZNUMBER");
  int tnumber = Getint("TNUMBER");
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  rangemin.Setmin(min);
  rangemin.Setwidth(width);
  rangemin.SetNum(number);
}

Config_distance_image::Config_distance_image(){
  outfile_x_noretro = Getchar("OUTFILEXNORETRO");
  outfile_y_noretro = Getchar("OUTFILEYNORETRO");
  outfile_z_noretro = Getchar("OUTFILEZNORETRO");
  outfile_x_onretro = Getchar("OUTFILEXONRETRO");
  outfile_y_onretro = Getchar("OUTFILEYONRETRO");
  outfile_z_onretro = Getchar("OUTFILEZONRETRO");
}

Config_eventdisplay_sum::Config_eventdisplay_sum(){
  infile = Getchar("INFILE");
  outfile = Getchar("OUTFILE");
  name = Getchar("NAME");
  title = Getchar("TITLE");
  nevents = Getint("NEVENTS");
}

Config_goodness_moment::Config_goodness_moment(){
  infile_goodness = Getchar("INFILEGOODNESS");
  intree = Getchar("INTREE");
  infile_data = Getchar("INFILEDATA");
  name_retro = Getchar("NAMERETRO");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
  sigma = Getdouble("SIGMA");
}

Config_eventdisplay_moment::Config_eventdisplay_moment(){
  infile_goodness = Getchar("INFILEGOODNESS");
  intree_goodness = Getchar("INTREEGOODNESS");
  n_event = Getint("NEVENT");
  infile_data = Getchar("INFILEDATA");
  xbin = Getint("XBIN");
  ybin = Getint("YBIN");
  outfile = Getchar("OUTFILE");
  outfile_restrict = Getchar("OUTFILERESTRICT");
}

Config_grad::Config_grad(){
  infile_first = Getchar("INFILEFIRST");
  intree_first = Getchar("INTREEFIRST");
  infile_data = Getchar("INFILEDATA");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
}

Config_goodness_minimize::Config_goodness_minimize(){
  infile_goodness = Getchar("INFILEGOODNESS");
  intree_goodness = Getchar("INTREEGOODNESS");
  infile_data = Getchar("INFILEDATA");
  ogfuncname = Getchar("OGFUNCNAME");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
  sigma = Getdouble("SIGMA");
  xbin = Getint("XBIN");
  xwidth = Getdouble("XWIDTH");
  xmin = Getdouble("XMIN");
  xmax = Getdouble("XMAX");
  tbin = Getint("TBIN");
  twidth = Getdouble("TWIDTH");
  tmin = Getdouble("TMIN");
  tmax = Getdouble("TMAX");
  nevent = Getint("NEVENT");
}

Config_efficiency::Config_efficiency(){
  infilehead = Getchar("INFILEHEAD");
  infiletail = Getchar("INFILETAIL");
  outfile = Getchar("OUTFILE");
  emin = Getdouble("EMIN");
  ewidth = Getdouble("EWIDTH");
  e_num = Getint("ENUM");
  emax = Getdouble("EMAX");
}

Config_func_dir::Config_func_dir(){
  infile = Getchar("INFILE");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
  outtree_v = Getchar("OUTTREEV");
  double truex = Getdouble("TRUEX");
  double truey = Getdouble("TRUEY");
  double truez = Getdouble("TRUEZ");
  truevertex = TVector3(truex,truey,truez);
  double truedirx = Getdouble("TRUEDIRX");
  double truediry = Getdouble("TRUEDIRY");
  double truedirz = Getdouble("TRUEDIRZ");
  truedirection = TVector3(truedirx,truediry,truedirz);
}

Config_N200::Config_N200(){
  infile = Getchar("INFILE");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
}

Config_likelihood_direction_grid_search::Config_likelihood_direction_grid_search(){
  infile_data = Getchar("INFILEDATA");
  infile_goodness = Getchar("INFILEGOODNESS");
  intree = Getchar("INTREE");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
  lfuncname = Getchar("LFUNCNAME");
  f_dirfunc_noretroname = Getchar("FDIRFUNCNORETRONAME");
  f_dirfunc_onretroname = Getchar("FDIRFUNCONRETRONAME");
  afuncname = Getchar("AFUNCNAME");
  voption = Getchar("VOPTION");
  truex = Getdouble("TRUEX");
  truey = Getdouble("TRUEY");
  truez = Getdouble("TRUEZ");
  trueTheta = Getdouble("TRUETHETA");
  truePhi = Getdouble("TRUEPHI");
  gfuncname = Getchar("GFUNCNAME");
  ogfuncname = Getchar("OGFUNCNAME");
  gffuncname = Getchar("GFFUNCNAME");
  sigma = Getdouble("SIGMA");
  double xmin = Getdouble("XMIN");
  double ymin = Getdouble("YMIN");
  double zmin = Getdouble("ZMIN");
  double tmin = Getdouble("TMIN");
  double xwidth = Getdouble("XWIDTH");
  double ywidth = Getdouble("YWIDTH");
  double zwidth = Getdouble("ZWIDTH");
  double twidth = Getdouble("TWIDTH");
  int xnumber = Getint("XNUMBER");
  int ynumber = Getint("YNUMBER");
  int znumber = Getint("ZNUMBER");
  int tnumber = Getint("TNUMBER");
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  range.Setmin(min);
  range.Setwidth(width);
  range.SetNum(number);
  costheta_width = Getdouble("COSTHETAWIDTH");
  phi_width = Getdouble("PHIWIDTH");
}

Config_f_direction_define::Config_f_direction_define(){
  infile = Getchar("INFILE");
  outfile = Getchar("OUTFILE");
  gfuncname = Getchar("GFUNCNAME");
  ogfuncname = Getchar("OGFUNCNAME");
  double truex = Getdouble("TRUEX");
  double truey = Getdouble("TRUEY");
  double truez = Getdouble("TRUEZ");
  truevertex = TVector3(truex,truey,truez);
  double xmin = Getdouble("XMIN");
  double ymin = Getdouble("YMIN");
  double zmin = Getdouble("ZMIN");
  double tmin = Getdouble("TMIN");
  double xwidth = Getdouble("XWIDTH");
  double ywidth = Getdouble("YWIDTH");
  double zwidth = Getdouble("ZWIDTH");
  double twidth = Getdouble("TWIDTH");
  int xnumber = Getint("XNUMBER");
  int ynumber = Getint("YNUMBER");
  int znumber = Getint("ZNUMBER");
  int tnumber = Getint("TNUMBER");
  TLorentzVector min(xmin,ymin,zmin,tmin);
  TLorentzVector width(xwidth,ywidth,zwidth,twidth);
  C4Number number(xnumber,ynumber,znumber,tnumber);
  range.Setmin(min);
  range.Setwidth(width);
  range.SetNum(number);
  sigma = Getdouble("SIGMA");
}

Config_tof_exe::Config_tof_exe(){
  infile = Getchar("INFILE");
  outfile = Getchar("OUTFILE");
  outtree = Getchar("OUTTREE");
}
