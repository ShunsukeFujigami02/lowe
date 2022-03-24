#ifndef FILEMANAGER_HH
#define FILEMANAGER_HH

// c++ STL
#include <vector>
#include <string>
#include <map>

// ROOT
#include <TObject.h>

// self
#include "AnalizeFile.hh"

class FileManager : public TObject
{
public:
  FileManager();
  virtual ~FileManager(){};
  void SetAllFile();
  void printfilelist();
  void reflectNarrowDownTag(std::string filetype="");
  void printselectedfile();
  void setselectedfile(std::string filename);
  bool isexistsamefile();
  bool isexistsamefile(AnalizeFile file);
  std::map<std::string,AnalizeFile> allfilemap;
  std::map<std::string,AnalizeFile> selectedfilemap;
  std::vector<AnalizeTag> narrowdowntag;
  static std::string directory;
  ClassDef(FileManager,1)
};
  

#endif
