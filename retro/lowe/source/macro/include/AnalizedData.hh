#ifndef ANALIZEDDATA_HH
#define ANALIZEDDATA_HH

// ROOT library
#include <TObject.h>

// self-introduced library
#include "goodness_data.hh"
#include "likelihood_direction_data.hh"

class AnalizedData : public TObject {

public:
  AnalizedData() {}
  virtual ~AnalizedData(){};
  AnalizedData(goodness_data gdatagridsearch_in,l_dir_data ldatagridsearch_in,goodness_data gdataminimized_in,l_dir_data ldataminimized_in);
  goodness_data Getgdatagridsearch(){ return gdatagridsearch;}
  l_dir_data Getldatagridsearch(){ return ldatagridsearch;}
  goodness_data Getdataminimized(){ return gdataminimized;}
  l_dir_data Getldataminimized(){ return ldataminimized;}
  void Setgdatagridsearch(goodness_data gdata){ gdatagridsearch = gdata;}
  void Setldatagridsearch(l_dir_data ldata){ ldatagridsearch = ldata;}
  void Setgdataminimized(goodness_data gdata){ gdataminimized = gdata;}
  void Setldataminimized(l_dir_data ldata){ ldataminimized = ldata;}
private:
  goodness_data gdatagridsearch;
  l_dir_data ldatagridsearch;
  goodness_data gdataminimized;
  l_dir_data ldataminimized;
public:
  ClassDef(AnalizedData,1)
};
#endif
