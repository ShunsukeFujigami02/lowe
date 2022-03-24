#ifndef INTEGRAL_PHOTO_HH
#define INTEGRAL_PHOTO_HH

double integral_photo(const char* infile,CArea sigarea,CArea bgarea,double gamma = 1.);

double integral_all(const char* infile,double gamma = 1.);

double integral_photo(const char* infile,CArea sigarea,double gamma = 1.);
#endif
