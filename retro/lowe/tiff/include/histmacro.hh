#ifndef HISTMACRO_HH
#define HISTMACRO_HH

#include <TH2D.h>
#include <TH1D.h>

void Fillconstvalue(TH2D* h1,double value);

bool Issamestructure(TH2D* h1,TH2D* h2);

bool Issamestructure(TH1D* h1,TH1D* h2);

TH2D* calculate(TH2D* h1,TH2D* h2,const char* histname,const char* type);

void Test();
#endif
