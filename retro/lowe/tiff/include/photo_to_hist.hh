#ifndef PHOTO_TO_HIST_HH
#define PHOTO_TO_HIST_HH

#include <TH2D.h>
TH2D* photo_to_hist(const char* infile,const char* histname);

TH2D* photo_to_hist_empty(const char* infile,const char* histname);

TH2D* photo_to_hist(const char* infile,const char* histname,double gamma);
#endif
