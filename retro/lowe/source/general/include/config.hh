#ifndef CONFIG_HH
#define CONFIG_HH

#include <iostream>
#include <cstring>
// ROOT library
#include <TVector3.h>

// self-introduced library
#include "CSearch_range.hh"
#include "AngleRange.hh"
#include "GoodnessParameters.hh"

// config type class is purposed to get environment variable and change to c++ variables

char* Getchar(const char* envname);
// get char type value by environment value

int Getint(const char* envname);
// get int type value by environment value

double Getdouble(const char* envname);
// get double type value by environment value

CSearch_range GetCSearch_range(const char* envxmin="XMIN",const char* envymin="YMIN",const char* envzmin="ZMIN",const char* envtmin="TMIN",const char* envxwidth="XWIDTH",const char* envywidth="YWIDTH",const char* envzwidth="ZWIDTH",const char* envtwidth="TWIDTH",const char* envxnumber="XNUMBER",const char* envynumber="YNUMBER",const char* envznumber="ZNUMBER",const char* envtnumber="TNUMBER");

AngleRange GetAngleRange(const char* envcosthetamin="COSTHETAMIN",const char* envcosthetawidth="COSTHETAWIDTH",const char* envcosthetanum="COSTHETANUM",const char* envphimin="PHIMIN",const char* envphiwidth="PHIWIDTH",const char* envphinum="PHINUM");


template <class T>
typename T::type GetEnum(const char* envname)
{
  T t;
  char* enum_tmp = std::getenv(envname);
  if(enum_tmp == nullptr)
    {
      std::cout << "Environment variable " << envname << " is not exist" << std::endl;
      throw "template<typename T> GetEnum(const char* envname)";
    }
  std::string senum_tmp = enum_tmp;
  std::cout << t.converter.empty() << std::endl;
  if(t.converter.find(senum_tmp) != t.converter.end())
    {
      return t.converter[senum_tmp];
    }
  else
    {
      std::cout << "invalid environment variable" << std::endl;
      throw "template<typename T> GetEnum(const char* envname)";
    }
}

class Config_goodness
{
  // corresponding execute file is goodness_time_and_position_exe.cc
  // This file execute 4-dimension grid search of goodness
public:
  char* infile;
  char* outtree;
  char* gfuncname;
  char* ogfuncname;
  CSearch_range range;
  double sigma;
  Config_goodness();
};

class Config_goodness_image
{
  // corresponding execute file is imagegoodness.cc
  // This file represents the results grid search of goodness for each 3(x,y,z) directions
public:
  char* infile_onretro;
  char* infile_noretro;
  char* infile_compare;
  char* chainname_onretro;
  char* chainname_noretro;
  char* chainname_compare;
  CSearch_range range;
  char* outfile_x;
  char* outfile_y;
  char* outfile_z;
  Config_goodness_image();
};

class Config_goodness_bias_err
{
  // corresponding execute file is goodness_bias_err.cc
  // This file represents bias and error of x-changed grid search of goodness.
public:
  Config_goodness_bias_err();
  char* infilehead_onretro;
  char* infilehead_noretro;
  //  char* infilehead_compare;
  char* infiletail;
  char* intreehead_onretro;
  char* intreehead_noretro;
  //  char* intreehead_compare;
  char* intreetail;
  char* outfile_x_bias;
  char* outfile_y_bias;
  char* outfile_z_bias;
  char* outfile_x_err;
  char* outfile_y_err;
  char* outfile_z_err;
  int xnum;
  double xverwidth;
  CSearch_range rangemin;
};

class Config_distance_image
{
  // corresponding execute file is distance_image.cc
  // This file represents of distribution of light distance to one pmt position changed vertex x,y,z position. distance is changed by  on retro and no retro 
public:
  Config_distance_image();
  char* outfile_x_noretro;
  char* outfile_y_noretro;
  char* outfile_z_noretro;
  char* outfile_x_onretro;
  char* outfile_y_onretro;
  char* outfile_z_onretro;
};

class Config_eventdisplay_sum
{
  // corresponding execute file is eventdisplay_sum.cc
  // This file is to create image file of display of multi event.
public:
  Config_eventdisplay_sum();
  char* infile;
  char* outfile;
  char* name;
  char* title;
  int nevents;
};

class Config_goodness_moment
{
  // corresponding execute file is goodness_moment.cc
  // This file purpose is to calculate direction of event by each hit division(direct or reflect)
public:
  Config_goodness_moment();
  char* infile_goodness;
  char* intree;
  char* name_retro;
  char* infile_data;
  char* outfile;
  char* outtree;
  double sigma;
};

class Config_eventdisplay_moment
{
  // corresponding execute file is eventdisplay_moment.cc
  // This file create eventdisplay to divide direct hit and reflect hit 
public:
  Config_eventdisplay_moment();
  char* infile_goodness;
  char* intree_goodness;
  int n_event;
  char* infile_data;
  int xbin;
  int ybin;
  char* outfile;
  char* outfile_restrict;
};

class Config_grad
{
public:
  Config_grad();
  // corresponding execute file is grad_exe.cc
  // I tried gradient descent by self-making function by this file. But I know it can do by using ROOT library.
  char* infile_first;
  char* intree_first;
  char* infile_data;
  char* outfile;
  char* outtree;
};

class Config_goodness_minimize
{
  // corresponding execute file is goodness_minimize.cc
  // purpose of this file is to calculate vertex position by minimize goodness
public:
  Config_goodness_minimize();
  char* infile_goodness;
  char* intree_goodness;
  char* ogfuncname;
  double sigma;
  char* infile_data;
  char* outfile;
  char* outtree;
  int xbin;
  double xwidth;
  double xmin;
  double xmax;
  int tbin;
  double twidth;
  double tmin;
  double tmax;
  int nevent;
};

class Config_efficiency
{
  // corresponding execute file is efficiency.cc
  // This file create image of trigger efficiency by function of particle energy
public:
  Config_efficiency();
  char* infilehead;
  char* infiletail;
  char* outfile;
  double emin;
  double ewidth;
  int e_num;
  double emax;
};

class Config_func_dir
{
  // corresponding execute file is get_function_direction.cc
  // This file represent costheta distribution for the likelihood of direction
  // likelihood direction is based on http://www-sk.icrr.u-tokyo.ac.jp/sk/_pdf/articles/ikeda-dron.pdf page32 (4.3).
public:
  Config_func_dir();
  char* infile;
  char* outfile;
  char* outtree;
  char* outtree_v;
  TVector3 truevertex;
  TVector3 truedirection;
};

class Config_N200
{
  // corresponding execute file is N200.cc
  // This file represent distribution of number of hit in time window(-200 < t < 0) to check trigger time window
public:
  Config_N200();
  char* infile;
  char* outfile;
  char* outtree;
};

class Config_likelihood_direction_grid_search
{
  // corresponding execute file is likelihood_direction_grid_search_exe.cc
  // This file execute grid search of likelihood of direction and minimize goodness times likelihood function.
public:
  Config_likelihood_direction_grid_search();
  char* infile_data;
  char* infile_goodness;
  char* intree;
  char* outfile;
  char* outtree;
  char* lfuncname;
  char* f_dirfunc_noretroname;
  char* f_dirfunc_onretroname;
  char* afuncname;
  char* voption;
  double truex;
  double truey;
  double truez;
  double trueTheta;
  double truePhi;
  char* gfuncname;
  char* ogfuncname;
  char* gffuncname;
  double sigma;
  CSearch_range range;
  double costheta_width;
  double phi_width;
};

class Config_f_direction_define
{
  // corresponding file is f_direction_define.cc
  // This file is used to define function of direction in likelihood direction for each time window(retro and no retro) 
public:
  Config_f_direction_define();
  char* infile;
  char* outfile;
  char* gfuncname;
  char* ogfuncname;
  CSearch_range range;
  TVector3 truevertex;
  double sigma;
};

class Config_tof_exe
{
  // corresponding file is tof_exe.cc
  // This file is time of flight distribution of hits
public:
  Config_tof_exe();
  char* infile;
  char* outfile;
  char* outtree;
};
  
#endif
