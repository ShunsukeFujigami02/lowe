#include "AnalizeFile.hh"
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>

ClassImp(AnalizeFile)

AnalizeFile::AnalizeFile(std::string filename)
{
  if(filename.rfind(".csv") != std::string::npos)
    {
      filecsv = filename;
      std::istringstream istreamfile(filecsv);
      std::string str_dot_buf;
      getline(istreamfile,str_dot_buf,'.');
      fileroot = str_dot_buf + ".root";
    }
  if(filename.rfind(".root") != std::string::npos)
    {
      fileroot = filename;
      std::istringstream istreamfile(fileroot);
      std::string str_dot_buf;
      getline(istreamfile,str_dot_buf,'.');
      filecsv = str_dot_buf + ".csv";
    }
  std::string str_buf;
  std::string str_comma_buf;
  std::ifstream ifs_csv_file(filecsv);
  if(!ifs_csv_file)
    {
      std::cout << "file " << filecsv << " is not exist!" << std::endl;
      throw "AnalizeFile::AnalizeFile(std::string filename)";
    }
  getline(ifs_csv_file,str_buf);
  std::istringstream i_stream(str_buf);
  while(getline(i_stream,str_comma_buf,','))
    {
      originfilenames.emplace_back(str_comma_buf);
      originfiles.emplace_back(str_comma_buf);
    }
  while(getline(ifs_csv_file,str_buf))
    {
      std::istringstream i_stream2(str_buf);
      std::string tagname;
      std::string tagtype;
      int valueint;
      double valuedouble;
      std::string valuestring;
      int i = 0;
      while(getline(i_stream2,str_comma_buf,','))
	{
	  if(i == 0)
	    tagname = str_comma_buf;
	  else if(i == 1)
	    tagtype = str_comma_buf;
	  else if(i == 2)
	    valuestring = str_comma_buf;
	  else
	    {
	      std::cout << "invalid csv file!" << std::endl;
	      throw "AnalizeFile::AnalizeFile(std::string::filename)";
	    }
	  i++;
	}
      if(tagtype == "string")
	{
	  tags.emplace_back(tagname,tagtype,valuestring);
	}
      else if(tagtype == "double")
	{
	  valuedouble = std::stod(valuestring);
	  tags.emplace_back(tagname,tagtype,valuedouble);
	}
      else if(tagtype == "int")
	{
	  valueint = std::stoi(valuestring);
	  tags.emplace_back(tagname,tagtype,valueint);
	}
      else
	{
	  std::cout << "tagtype " << tagtype << " is not invalid!" << std::endl;
	  throw "AnalizeFile::AnalizeFile(const AnalizeFile& file)";
	}
    }
}

AnalizeFile::~AnalizeFile(){
}

AnalizeFile::AnalizeFile(const AnalizeFile& file) : TObject(file)
{
  tags = file.tags;
  originfiles = file.originfiles;
  originfilenames = file.originfilenames;
  fileroot = file.fileroot;
  filecsv = file.filecsv;
}

AnalizeFile::AnalizeFile(AnalizeFile&& file) : TObject(file)
{
  *this = std::move(file);
}

 
AnalizeFile& AnalizeFile::operator=(const AnalizeFile& file)
{
  tags = file.tags;
  originfiles = file.originfiles;
  originfilenames = file.originfilenames;
  fileroot = file.fileroot;
  filecsv = file.filecsv;
  return *this;
}

AnalizeFile& AnalizeFile::operator=(AnalizeFile&& file)
{
  tags = std::move(file.tags);
  originfiles = std::move(file.originfiles);
  originfilenames = std::move(file.originfilenames);
  fileroot = std::move(file.fileroot);
  filecsv = std::move(file.filecsv);
  return *this;
}

bool AnalizeFile::operator==(AnalizeFile file)
{
  for(auto iter = tags.begin();iter != tags.end();iter++)
    {
      if(!file.hasEqualTag((*iter)))
	return false;
    }
  for(auto iter = file.tags.begin();iter != file.tags.end();iter++)
    {
      if(!hasEqualTag((*iter)))
	return false;
    }
  for(auto iter = originfilenames.begin();iter != originfilenames.end();iter++)
    {
      if(!file.hasEqualOriginFile((*iter)))
	return false;
    }
  for(auto iter = file.originfilenames.begin();iter != file.originfilenames.end();iter++)
    {
      if(!hasEqualOriginFile((*iter)))
	return false;
    }
  return true;
}
	 
bool AnalizeFile::GetTagstring(std::string tagname,std::string& value,std::vector<std::string> pass)
{
  if(pass.size() == 0)
    { 
      for(auto iter = tags.begin();iter != tags.end();iter++)
	{
	  if(((*iter).GetTagName() == tagname) || ((*iter).GetTagType() == "string"))
	    {
	      value = (*iter).GetValuestring();
	      return true;
	    }
	}
      return false;
    }
  int filenumber = -1;
  for(int i = 0;i != (int)originfilenames.size();i++)
    {
      if((*(pass.end() - 1)) == originfilenames.at(i))
	filenumber = i;
    }
  if(filenumber == -1)
    {
      std::cout << "pass is not found" << std::endl;
      return false;
    }
  pass.pop_back();
  return originfiles.at(filenumber).GetTagstring(tagname,value,pass);
}

bool AnalizeFile::GetTagint(std::string tagname,int& value,std::vector<std::string> pass)
{
    if(pass.size() == 0)
    { 
      for(auto iter = tags.begin();iter != tags.end();iter++)
	{
	  if(((*iter).GetTagName() == tagname) && ((*iter).GetTagType() == "int"))
	    {
	      value = (*iter).GetValueint();
	      return true;
	    }
	}
      return false;
    }
  int filenumber = -1;
  for(int i = 0;i != (int)originfilenames.size();i++)
    {
      if(*(pass.end() - 1) == originfilenames[i])
	filenumber = i;
    }
  if(filenumber == -1)
    return false;
  pass.pop_back();
  return originfiles[filenumber].GetTagint(tagname,value,pass);
}

bool AnalizeFile::GetTagdouble(std::string tagname,double& value,std::vector<std::string> pass)
{
  if(pass.size() == 0)
    { 
      for(auto iter = tags.begin();iter != tags.end();iter++)
	{
	  if(((*iter).GetTagName() == tagname) && ((*iter).GetTagType() == "double"))
	    {
	      value = (*iter).GetValuedouble();
	      return true;
	    }
	}
      return false;
    }
  int filenumber = -1;
  for(int i = 0;i != (int)originfilenames.size();i++)
    {
      if(*(pass.end() - 1) == originfilenames[i])
	filenumber = i;
    }
  if(filenumber == -1)
    return false;
  pass.pop_back();
  return originfiles.at(filenumber).GetTagdouble(tagname,value,pass);
}

bool AnalizeFile::GetTagstring(std::string tagname,std::string& value)
{
  for(auto iter = tags.begin();iter != tags.end();iter++)
    {
      if(((*iter).GetTagName() == tagname) && ((*iter).GetTagType() == "string"))
	{
	  value = (*iter).GetValuestring();
	  return true;
	}
    }
  for(auto iter = originfiles.begin();iter != originfiles.end();iter++)
    {
      if((*iter).GetTagstring(tagname,value))
	return true;
    }
  return false;
}

bool AnalizeFile::GetTagint(std::string tagname,int& value)
{
  for(auto iter = tags.begin();iter != tags.end();iter++)
    {
      if(((*iter).GetTagName() == tagname) && ((*iter).GetTagType() == "int"))
	{
	  value = (*iter).GetValueint();
	  return true;
	}
    }
  for(auto iter = originfiles.begin();iter != originfiles.end();iter++)
    {
      if((*iter).GetTagint(tagname,value))
	return true;
    }
  return false;
}

bool AnalizeFile::GetTagdouble(std::string tagname,double& value)
{
  for(auto iter = tags.begin();iter != tags.end();iter++)
    {
      if(((*iter).GetTagName() == tagname) && ((*iter).GetTagType() == "double"))
	{
	  value = (*iter).GetValuedouble();
	  return true;
	}
    }
  for(auto iter = originfiles.begin();iter != originfiles.end();iter++)
    {
      if((*iter).GetTagdouble(tagname,value))
	return true;
    }
  return false;
}

void AnalizeFile::print()
{
  std::cout << "filename is " << filecsv << std::endl;
  std::cout << "origin file name table" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  for(auto iter = originfilenames.begin();iter != originfilenames.end(); iter++)
    {
      std::cout << (*iter) << std::endl;
    }
  std::cout << "--------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << "tag table" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  std::cout << "tagname/tagtype/tagvalue" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  for(auto iter = tags.begin();iter != tags.end(); iter++)
    {
      (*iter).print();
    }
  std::cout << std::endl;
}

void AnalizeFile::printall()
{
   std::cout << "filename is " << filecsv << std::endl;
  std::cout << "origin file name table" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  for(auto iter = originfilenames.begin();iter != originfilenames.end(); iter++)
    {
      std::cout << (*iter) << std::endl;
    }
  std::cout << "--------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << "tag table" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  std::cout << "tagname/tagtype/tagvalue" << std::endl;
  std::cout << "--------------------------------------------------------------------" << std::endl;
  for(auto iter = tags.begin();iter != tags.end(); iter++)
    {
      (*iter).print();
    }
  std::cout << std::endl;

  for(auto iter = originfiles.begin();iter != originfiles.end(); iter++)
    {
      (*iter).printall();
    }
} 

bool AnalizeFile::hasEqualTag(AnalizeTag tag)
{
  for(auto iter = tags.begin();iter != tags.end(); iter++)
    {
      if((*iter) == tag)
	return true;
    }
  for(auto iter2 = originfiles.begin();iter2 != originfiles.end();iter2++)
    {
      if((*iter2).hasEqualTag(tag))
	return true;
    }
  return false;
}

bool AnalizeFile::hasEqualTagName(std::string name)
{
  for(auto iter = tags.begin();iter != tags.end();iter++)
    {
      if((*iter).GetTagName() == name)
	return true;
    }
  for(auto iter = originfiles.begin();iter != originfiles.end();iter++)
    {
      if((*iter).hasEqualTagName(name))
	return true;
    }
  return false;
}

  
bool AnalizeFile::hasEqualOriginFile(std::string filename)
{
  for(auto iter = originfilenames.begin();iter != originfilenames.end();iter++)
    {
      if((*iter) == filename)
	return true;
    }
  return false;
}

std::string AnalizeFile::changecsvroot(std::string basename)
{
  if(basename.rfind(".csv") != std::string::npos)
    {
      std::istringstream istreamfile(basename);
      std::string str_dot_buf;
      getline(istreamfile,str_dot_buf,'.');
      return (str_dot_buf + ".root");
    }
  if(basename.rfind(".root") != std::string::npos)
    {
      std::istringstream istreamfile(basename);
      std::string str_dot_buf;
      getline(istreamfile,str_dot_buf,'.');
      return (str_dot_buf + ".root");
    }
  std::cout << "invalid input name " << basename << std::endl;
  throw "static std:;string changecsvroot(std::string basename)";
}
