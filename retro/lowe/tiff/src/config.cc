#include "config.hh"
#include <cstdlib>
#include <iostream>
config_TinyTIFF_test::config_TinyTIFF_test(){
  filename = std::getenv("FILENAME");
  outfile = std::getenv("OUTFILE");
}
config_makehist::config_makehist(){
  infile = std::getenv("INFILE");
  outfile = std::getenv("OUTFILE");
}

config_integral_photo::config_integral_photo(){
  infile = std::getenv("INFILE");
  const char* sigfirstxbin_val = std::getenv("SIGFIRSTXBIN");
  int sigfirstxbin = atoi(sigfirstxbin_val);
  const char* siglastxbin_val = std::getenv("SIGLASTXBIN");
  int siglastxbin = atoi(siglastxbin_val);
  const char* sigfirstybin_val = std::getenv("SIGFIRSTYBIN");
  int sigfirstybin = atoi(sigfirstybin_val);
  const char* siglastybin_val = std::getenv("SIGLASTYBIN");
  int siglastybin = atoi(siglastybin_val);
  const char* bgfirstxbin_val = std::getenv("BGFIRSTXBIN");
  int bgfirstxbin = atoi(bgfirstxbin_val);
  const char* bglastxbin_val = std::getenv("BGLASTXBIN");
  int bglastxbin = atoi(bglastxbin_val);
  const char* bgfirstybin_val = std::getenv("BGFIRSTYBIN");
  int bgfirstybin = atoi(bgfirstybin_val);
  const char* bglastybin_val = std::getenv("BGLASTYBIN");
  int bglastybin = atoi(bglastybin_val);
  sigarea = CArea(sigfirstxbin,siglastxbin,sigfirstybin,siglastybin);
  bgarea = CArea(bgfirstxbin,bglastxbin,bgfirstybin,bglastybin);
  const char* gamma_val = std::getenv("GAMMA");
  gamma = atof(gamma_val);
}

Config_integral_photo_dis::Config_integral_photo_dis(){
  outfile = std::getenv("OUTFILE");
  const char* anglenum_val = std::getenv("ANGLENUM");
  anglenum = atoi(anglenum_val);
  const char* anglewidth_val = std::getenv("ANGLEWIDTH");
  anglewidth = atof(anglewidth_val);
  const char* anglemin_val = std::getenv("ANGLEMIN");
  anglemin = atof(anglemin_val);
  const char* anglemax_val = std::getenv("ANGLEMAX");
  anglemax = atof(anglemax_val);
  infilehead = std::getenv("INFILEHEAD");
  infiletail = std::getenv("INFILETAIL");
  const char* sigfirstxbin_val = std::getenv("SIGFIRSTXBIN");
  int sigfirstxbin = atoi(sigfirstxbin_val);
  const char* siglastxbin_val = std::getenv("SIGLASTXBIN");
  int siglastxbin = atoi(siglastxbin_val);
  const char* sigfirstybin_val = std::getenv("SIGFIRSTYBIN");
  int sigfirstybin = atoi(sigfirstybin_val);
  const char* siglastybin_val = std::getenv("SIGLASTYBIN");
  int siglastybin = atoi(siglastybin_val);
  const char* bgfirstxbin_val = std::getenv("BGFIRSTXBIN");
  int bgfirstxbin = atoi(bgfirstxbin_val);
  const char* bglastxbin_val = std::getenv("BGLASTXBIN");
  int bglastxbin = atoi(bglastxbin_val);
  const char* bgfirstybin_val = std::getenv("BGFIRSTYBIN");
  int bgfirstybin = atoi(bgfirstybin_val);
  const char* bglastybin_val = std::getenv("BGLASTYBIN");
  int bglastybin = atoi(bglastybin_val);
  sigarea = CArea(sigfirstxbin,siglastxbin,sigfirstybin,siglastybin);
  bgarea = CArea(bgfirstxbin,bglastxbin,bgfirstybin,bglastybin);
  const char* gamma_val = std::getenv("GAMMA");
  gamma = atof(gamma_val);
}

Config_fitting_responce_ccd::Config_fitting_responce_ccd(){
  infileND30 = std::getenv("INFILEND30");
  infileND3010 = std::getenv("INFILEND3010");
  const char* x1_val = std::getenv("X1");
  x1 = atoi(x1_val);
  const char* y1_val = std::getenv("Y1");
  y1 = atoi(y1_val);
  const char* firstxbin_val = std::getenv("FIRSTXBIN");
  int firstxbin = atoi(firstxbin_val);
  const char* lastxbin_val = std::getenv("LASTXBIN");
  int lastxbin = atoi(lastxbin_val);
  const char* firstybin_val = std::getenv("FIRSTYBIN");
  int firstybin = atoi(firstybin_val);
  const char* lastybin_val = std::getenv("LASTYBIN");
  int lastybin = atoi(lastybin_val);
  bgarea = CArea(firstxbin,lastxbin,firstybin,lastybin);
}

Config_gamma_correction::Config_gamma_correction(){
  outfile = std::getenv("OUTFILE");
  infileND30 = std::getenv("INFILEND30");
  infileND3010 = std::getenv("INFILEND3010");
  const char* gamma_val = std::getenv("GAMMA");
  gamma = atof(gamma_val);
  const char* averagebg30_val = std::getenv("AVERAGEBG30");
  averagebg30 = atof(averagebg30_val);
  const char* averagebg3010_val = std::getenv("AVERAGEBG3010");
  averagebg3010 = atof(averagebg3010_val);
}

Config_reflectivity_angle_dis::Config_reflectivity_angle_dis(){
  outfile = std::getenv("OUTFILE");
  const char* anglenum_val = std::getenv("ANGLENUM");
  anglenum = atoi(anglenum_val);
  const char* anglewidth_val = std::getenv("ANGLEWIDTH");
  anglewidth = atof(anglewidth_val);
  const char* anglemin_val = std::getenv("ANGLEMIN");
  anglemin = atof(anglemin_val);
  const char* anglemax_val = std::getenv("ANGLEMAX");
  anglemax = atof(anglemax_val);
  infilehead = std::getenv("INFILEHEAD");
  infiletail = std::getenv("INFILETAIL");
  referencefile = std::getenv("REFERENCEFILE");
  const char* sigfirstxbin_val = std::getenv("SIGFIRSTXBIN");
  int sigfirstxbin = atoi(sigfirstxbin_val);
  const char* siglastxbin_val = std::getenv("SIGLASTXBIN");
  int siglastxbin = atoi(siglastxbin_val);
  const char* sigfirstybin_val = std::getenv("SIGFIRSTYBIN");
  int sigfirstybin = atoi(sigfirstybin_val);
  const char* siglastybin_val = std::getenv("SIGLASTYBIN");
  int siglastybin = atoi(siglastybin_val);
  const char* bgfirstxbin_val = std::getenv("BGFIRSTXBIN");
  int bgfirstxbin = atoi(bgfirstxbin_val);
  const char* bglastxbin_val = std::getenv("BGLASTXBIN");
  int bglastxbin = atoi(bglastxbin_val);
  const char* bgfirstybin_val = std::getenv("BGFIRSTYBIN");
  int bgfirstybin = atoi(bgfirstybin_val);
  const char* bglastybin_val = std::getenv("BGLASTYBIN");
  int bglastybin = atoi(bglastybin_val);
  sigarea = CArea(sigfirstxbin,siglastxbin,sigfirstybin,siglastybin);
  bgarea = CArea(bgfirstxbin,bglastxbin,bgfirstybin,bglastybin);
  const char* gamma_val = std::getenv("GAMMA");
  gamma = atof(gamma_val);
}
