#ifndef ANALIZETAG_HH
#define ANALIZETAG_HH

#include <string>
#include <TObject.h>

class AnalizeTag : public TObject
{
public:
  AnalizeTag(){};
  AnalizeTag(std::string name,std::string type,int value);
  AnalizeTag(std::string name,std::string type,double value);
  AnalizeTag(std::string name,std::string type,std::string value);
  AnalizeTag(const AnalizeTag& tag);
  AnalizeTag(AnalizeTag&& tag);
  virtual ~AnalizeTag(){};
  AnalizeTag& operator=(const AnalizeTag& tag);
  AnalizeTag& operator=(AnalizeTag&& tag);
  bool operator==(const AnalizeTag& tag);
  bool operator!=(const AnalizeTag& tag);
  std::string GetTagName() const
  {
    return tagname;
  }
  std::string GetTagType() const
  {
    return tagtype;
  }
  int GetValueint() const 
  {
    return valueint;
  }
  double GetValuedouble() const
  {
    return valuedouble;
  }
  std::string GetValuestring() const
  {
    return valuestring;
  }
  void print();
private:
  std::string tagname;
  std::string tagtype;
  int valueint;
  double valuedouble;
  std::string valuestring;
public:
  ClassDef(AnalizeTag,1)
};

#endif
