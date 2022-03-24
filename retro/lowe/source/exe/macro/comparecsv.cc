#include <string>
#include "AnalizeFile.hh"
#include <iostream>
#include <exception>

int main(int argc,char** argv)
{
  try
    {
      if(argc != 3)
	{
	  std::cout << "value number is wrong" << std::endl;
	  throw "int main(int argc,char** argv) in comparecsv.cc";
	}
      std::string fname1 = argv[1];
      std::string fname2 = argv[2];
      AnalizeFile a1(fname1);
      AnalizeFile a2(fname2);
      bool b = (a1 == a2);
      if(b == true)
	std::cout << "true" << std::endl;
      if(b == false)
	std::cout << "false" << std::endl;
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

