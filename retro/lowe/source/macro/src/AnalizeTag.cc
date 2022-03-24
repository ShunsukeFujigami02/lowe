#include "AnalizeTag.hh"
#include <string>
#include <utility>
#include <iostream>

ClassImp(AnalizeTag)

AnalizeTag::AnalizeTag(std::string name,std::string type,int value)
{
  tagname = name;
  tagtype = type;
  valueint = value;
}

AnalizeTag::AnalizeTag(std::string name,std::string type,double value)
{
  tagname = name;
  tagtype = type;
  valuedouble = value;
}

AnalizeTag::AnalizeTag(std::string name,std::string type,std::string value)
{
  tagname = name;
  tagtype = type;
  valuestring = value;
}

AnalizeTag::AnalizeTag(const AnalizeTag& tag) : TObject(tag)
{
  tagname = tag.GetTagName();
  tagtype = tag.GetTagType();
  valueint = tag.GetValueint();
  valuedouble = tag.GetValuedouble();
  valuestring = tag.GetValuestring();
}

AnalizeTag::AnalizeTag(AnalizeTag&& tag) : TObject(tag)
{
  *this = std::move(tag);
}

AnalizeTag& AnalizeTag::operator=(const AnalizeTag& tag)
{
  tagname = tag.tagname;
  tagtype = tag.tagtype;
  valueint = tag.valueint;
  valuedouble = tag.valuedouble;
  valuestring = tag.valuestring;

  return *this;
}


AnalizeTag& AnalizeTag::operator=(AnalizeTag&& tag)
{
  tagname = std::move(tag.tagname);
  tagtype = std::move(tag.tagtype);
  valueint = tag.GetValueint();
  valuedouble = tag.GetValuedouble();
  valuestring = std::move(tag.valuestring);

  return *this;
}

bool AnalizeTag::operator==(const AnalizeTag& tag)
{
  if(tagname != tag.tagname)
    return false;
  else if(tagtype == "int")
    return (valueint == tag.valueint);
  else if(tagtype == "double")
    return (valuedouble == tag.valuedouble);
  else if(tagtype == "string")
    return (valuestring == tag.valuestring);
  else
    {
      std::cout << "invalid tagtype!" << std::endl;
      throw "AnalizeTag::operator==(AnalizeTag& tag)";
    }
}

bool AnalizeTag::operator!=(const AnalizeTag& tag)
{
  return !((*this) == tag);
}

void AnalizeTag::print()
{
  if(tagtype == "string")
    std::cout << "|" << tagname << "|" << tagtype << "|" << valuestring << "|" << std::endl;
  if(tagtype == "double")
    std::cout << "|" << tagname << "|" << tagtype << "|" << valuedouble << "|" << std::endl;
  if(tagtype == "int")
    std::cout << "|" << tagname << "|" << tagtype << "|" << valueint << "|" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
}

