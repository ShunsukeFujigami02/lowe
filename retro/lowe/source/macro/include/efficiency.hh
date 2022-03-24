#ifndef EFFICIENCY_HH
#define EFFICIENCY_HH
// ROOT library
#include <TH1D.h>

// self-introduced library
#include "FileList.hh"
class efficiency :public TH1D
{
 public:
  efficiency();
  efficiency(FileList* filelist_in,const char* name,const char* title,int num,double min,double max,double width);
  virtual ~efficiency(){};
  void SetEfError();
 private:
  FileList filelist;
  int Nevent;
  void fillloop(int i,double iter);
 public:
  ClassDef(efficiency,1)
};


#endif
