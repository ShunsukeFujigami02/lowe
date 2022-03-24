#ifndef FILELIST_HH
#define FILELIST_HH

// C++ STL
#include <vector>
#include <cstring>

// ROOT library
#include <TClonesArray.h>

class FileList :public TClonesArray
{
public:
  FileList();
  FileList(const char* filelist,int NFile=1000);
  virtual ~FileList(){};
private:
public:
  ClassDef(FileList,1)
};

#endif
