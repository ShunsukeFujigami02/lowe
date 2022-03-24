#ifndef CONFIG_HH
#define CONFIG_HH

#include "CArea.hh"

class config_TinyTIFF_test
{
public:
  config_TinyTIFF_test();
  virtual ~config_TinyTIFF_test(){};
  const char* filename;
  const char* outfile;
};

class config_makehist
{
public:
  config_makehist();
  virtual ~config_makehist(){};
  const char* infile;
  const char* outfile;
};

class config_integral_photo
{
public:
  config_integral_photo();
  virtual ~config_integral_photo(){};
  const char* infile;
  CArea sigarea;
  CArea bgarea;
  double gamma;
};


class Config_integral_photo_dis
{
public:
  Config_integral_photo_dis();
  virtual ~Config_integral_photo_dis(){};
  const char* outfile;
  int anglenum;
  double anglewidth;
  double anglemin;
  double anglemax;
  const char* infilehead;
  const char* infiletail;
  CArea sigarea;
  CArea bgarea;
  double gamma;
};

class Config_fitting_responce_ccd
{
public:
  Config_fitting_responce_ccd();
  const char* infileND30;
  const char* infileND3010;
  int x1;
  int y1;
  CArea bgarea;
};

class Config_gamma_correction
{
public:
  Config_gamma_correction();
  const char* outfile;
  const char* infileND30;
  const char* infileND3010;
  double gamma;
  double averagebg30;
  double averagebg3010;
};
#endif

class Config_reflectivity_angle_dis
{
public:
  Config_reflectivity_angle_dis();
  const char* outfile;
  int anglenum;
  double anglewidth;
  double anglemin;
  double anglemax;
  const char* infilehead;
  const char* infiletail;
  const char* referencefile;
  CArea sigarea;
  CArea bgarea;
  double gamma;
};
