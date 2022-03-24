#ifndef LIKELIHOODDIRECTIONEVENTMANAGER_HH
#define LIKELIHOODDIRECTIONEVENTMANAGER_HH

// geant4 library
#include <CLHEP/Vector/ThreeVector.h>

// self-introduced library
#include "ProcessManager.hh"
#include "AngleRange.hh"
class afunction;
class afuncprototype;

class LikelihoodDirectionEventManager : public ProcessManager
{
public:
  LikelihoodDirectionEventManager();
  virtual ~LikelihoodDirectionEventManager();  
  void Doprocess();
  void Doloopin();
  void SetAngleRange(AngleRange rangein)
  {
    range = rangein;
  }
  void Setafunctionnoretro(std::shared_ptr<afunction> afunc)
  {
    afunctionnoretro = afunc;
  }
  void Setafunctiononretro(std::shared_ptr<afunction> afunc)
  {
    afunctiononretro = afunc;
  }
  double likelihoodnoretro(const size_t& k);
  double likelihoodsum(const size_t& k);
  inline double costheta_dir_i_func(const size_t& k) const;
  inline double fdirectionnoretro_prototype(const double& costheta) const;
  inline double fdirectionnoretro_bydata(const double& costheta) const;
  inline double fdirectiononretro_prototype(const double& costheta) const;
  inline double fdirectiononretro_bydata(const double& costheta) const;
  void Settimewindownoretro(double t)
  {
    timewindownoretro = t;
  }
  void Settimewindowonretro(double t)
  {
    timewindowonretro = t;
  }
  
private:
  AngleRange range;
  size_t ncherenkovdigihits;
  double currentlikelihood;
  double maxlikelihood;
  double currentcostheta;
  double maxcostheta;
  double currentphi;
  double maxphi;
  double currentdirectionx;
  double currentdirectiony;
  double currentdirectionz;
  CLHEP::Hep3Vector fittedposition;
  double timewindownoretro;
  double timewindowonretro;
  std::vector<double> vonelikelihoodonretro;
  std::vector<double> vonelikelihoodnoretro;
  std::vector<double> vmaxonelikelihoodonretro;
  std::vector<double> vmaxonelikelihoodnoretro;
  std::vector<int> isbetweentimewindownoretro;
  std::vector<int> isbetweentimewindowonretro;
  std::vector<int> isbetweentimewindowatleastone;
  std::vector<double> vcostheta_ioveranoretro;
  std::vector<double> vcostheta_ioveraonretro;
  std::vector<double> hminusvxnor;
  std::vector<double> hminusvynor;
  std::vector<double> hminusvznor;
  std::vector<double> hminusvmag;
  std::shared_ptr<afunction> afunctionnoretro;
  std::shared_ptr<afunction> afunctiononretro;
  int likelihoodfunctype; // 0 noretro 1 sum
  int fdirnoretrotype; // 0 prototype 1 bydata
  int fdironretrotype; // 0 prototype 1 bydata
  std::string slikelihoodfunctype;
public:
  void Setlikelihoodfunctype(std::string s)
  {
    slikelihoodfunctype = s;
  }
private:
  std::string sfdirnoretrotype;
public:
  void Setfdirnoretrotype(std::string s)
  {
    sfdirnoretrotype = s;
  }
private:
  std::string sfdironretrotype;
public:
  void Setfdironretrotype(std::string s)
  {
    sfdironretrotype = s;
  }
private:
  const double prototypea0 = 0.929027;
  const double prototypeb0 = 4.69195;
  const double prototypea1 = 7.97348;
  const double prototypeb1 = -0.310661;
  
  const double bydatanoretroa0 = 0.97648;
  const double bydatanoretrob0 = 3.51958;
  const double bydatanoretroa1 = 0.88353;
  const double bydatanoretrob1 = -3.52407;
  
  const double bydataonretroa0 = 1.55324;
  const double bydataonretrob0 = 1.53637;
  const double bydataonretroa1 = 0.75423;
  const double bydataonretrob1 = -2.31295;
};

#endif
