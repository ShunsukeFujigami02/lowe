#ifndef FUNCLIST_HH
#define FUNCLIST_HH

#include <TH2D.h>

void BinaryOperation(TH2D* hist,TH2D* h1,TH2D* h2,const char* type);

void BinaryOperation(TH1D* hist,TH1D* h1,TH1D* h2,const char* type);

#endif
