#ifndef F_DIRECTION_FUNC_HH
#define F_DIRECTION_FUNC_HH

// ROOT library
#include <TH1D.h>

double f_direction_exp_noretro(double* x,double* par);

double f_direction_exp_noretro2(double* x,double* par);

double f_direction_exp_onretro(double* x,double* par);

double f_direction_exp_onretro2(double* x,double* par);

void fitting_f_direction_noretro(TH1D* h1);

void fitting_f_direction_noretro2(TH1D* h1);

void fitting_f_direction_onretro(TH1D* h1);

void fitting_f_direction_onretro2(TH1D* h1);

#endif
