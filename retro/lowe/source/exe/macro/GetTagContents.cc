#include <string>
#include "AnalizeFile.hh"
#include <iostream>
#include <exception>

int main(int argc,char**argv)
{
  try
    {
      if(argc != 4)
	{
	  std::cout << "value number is wrong" << std::endl;
	  throw "int main(int,argc,char** argv) in GetTagContents.cc";
	}
      std::string fname = argv[1];
      std::string tagname = argv[2];
      std::string tagtype = argv[3];
      AnalizeFile a(fname);
      if(tagtype == "double")
	{
	  double value = 0.;
	  bool b = a.GetTagdouble(tagname,value);
	  if(b)
	    std::cout << value << std::endl;
	  else
	    std::cout << "false" << std::endl;
	}
      if(tagtype == "string")
	{
	  std::string value = "";
	  bool b = a.GetTagstring(tagname,value);
	  if(b)
	    std::cout << value << std::endl;
	  else
	    std::cout << "false" << std::endl;
	}
      if(tagtype == "int")
	{
	  int value = 0;
	  bool b = a.GetTagint(tagname,value);
	  if(b)
	    std::cout << value << std::endl;
	  else
	    std::cout << "false" << std::endl;
	}
    }
    catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  
  catch(std::string str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  return 0;
}
