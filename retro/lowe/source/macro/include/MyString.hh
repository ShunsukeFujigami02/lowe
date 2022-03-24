#ifndef MYSTRING_HH
#define MYSTRING_HH

#include <TNamed.h>
#include <cstring>

class MyString : public TNamed
{
public:
  MyString(){};
  virtual ~MyString(){};
  std::string Getstring()
  {
    return name;
  }
  void Setstring(std::string n)
  {
    name = n;
  }
private:
  std::string name;
public:
  ClassDef(MyString,1)
};

#endif
