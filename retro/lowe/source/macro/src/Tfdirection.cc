// c++ STL
#include <cmath>

// self-introduced library
#include "Ttheta_dir_i.hh"
#include "Tfdirection.hh"

ClassImp(Tfdirection)
ClassImp(Tfdirprototypenoretro)
ClassImp(Tfdirprototypeonretro)
ClassImp(Tfdirbydatanoretro)
ClassImp(Tfdirbydataonretro)

double Tfdirprototypenoretro::returnvalue()
{
  double a0 = 0.929027;
  double b0 = 4.69195;
  double a1 = 7.97348;
  double b1 = -0.310661;
  Ttheta_dir_i theta;
  theta.SetHitInfo(info);
  theta.SetReconstructdata(data);
  double vtheta = theta.returnvalue();
  double costheta_dir_i = std::cos(vtheta);
  if(costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i - 0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i - 0.75 )) - 1));
  }
}

double Tfdirprototypeonretro::returnvalue()
{
  double a0 = 0.929027;
  double b0 = 4.69195;
  double a1 = 7.97348;
  double b1 = -0.310661;
  Ttheta_dir_i theta;
  theta.SetHitInfo(info);
  theta.SetReconstructdata(data);
  double vtheta = theta.returnvalue();
  double costheta_dir_i = std::cos(vtheta);
  if(-costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (-costheta_dir_i - 0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (-costheta_dir_i - 0.75 )) - 1));
  }
} 

double Tfdirbydatanoretro::returnvalue()
{
  double a0 = 0.97648;
  double b0 = 3.51958;
  double a1 = 0.88353;
  double b1 = -3.52407;
  Ttheta_dir_i theta;
  theta.SetHitInfo(info);
  theta.SetReconstructdata(data);
  double vtheta = theta.returnvalue();
  double costheta_dir_i = std::cos(vtheta);
  if(costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i -0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i - 0.75 )) - 1));
  }
}
double Tfdirbydataonretro::returnvalue()
{
  double a0 = 1.55324;
  double b0 = 1.53637;
  double a1 = 0.75423;
  double b1 = -2.31295;
  Ttheta_dir_i theta;
  theta.SetHitInfo(info);
  theta.SetReconstructdata(data);
  double vtheta = theta.returnvalue();
  double costheta_dir_i = std::cos(vtheta);
  if(costheta_dir_i < -0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i +0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i + 0.75 )) - 1));
  }
}
