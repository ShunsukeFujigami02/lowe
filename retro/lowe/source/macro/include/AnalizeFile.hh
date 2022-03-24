#ifndef ANALIZEFILE_HH
#define ANALIZEFILE_HH

#include <vector>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <map>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "AnalizeTag.hh"
#include "TReconstructdata.hh"

class AnalizeFile : public TObject
{
public:
  AnalizeFile(){};
  AnalizeFile(std::string filename);
  virtual ~AnalizeFile();
  AnalizeFile(const AnalizeFile& file);
  AnalizeFile(AnalizeFile&& file);
  AnalizeFile& operator=(const AnalizeFile& file);
  AnalizeFile& operator=(AnalizeFile&& file);
  bool operator==(AnalizeFile file);
  std::vector<AnalizeTag> tags;
  std::vector<AnalizeFile> originfiles;
  std::vector<std::string> originfilenames;
  std::string fileroot;
  std::string filecsv;
  bool GetTagstring(std::string tagname,std::string& value,std::vector<std::string> pass);
  bool GetTagint(std::string tagname,int& value,std::vector<std::string> pass);
  bool GetTagdouble(std::string tagname,double& value,std::vector<std::string> pass);
  bool GetTagstring(std::string tagname,std::string& value);
  bool GetTagint(std::string tagname,int& value);
  bool GetTagdouble(std::string tagname,double& value);
  bool hasEqualTag(AnalizeTag tag);
  bool hasEqualTagName(std::string name);
  bool hasEqualOriginFile(std::string filename);
  void print();
  void printall();
  static std::string changecsvroot(std::string basename);
  static std::map<std::string,AnalizeFile> allfilemap;
  ClassDef(AnalizeFile,1)
};

#endif
