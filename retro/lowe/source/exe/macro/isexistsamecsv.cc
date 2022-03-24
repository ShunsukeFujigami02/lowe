#include <iostream>
#include <string>
#include "FileManager.hh"
#include <exception>

int main(int argc,char** argv)
{
  try
    {
      if(argc == 1)
	{
	  FileManager* filemanager = new FileManager();
	  filemanager->SetAllFile();
	  bool b = filemanager->isexistsamefile();
	  if(b == true)
	    std::cout << "true" << std::endl;
	  if(b == false)
	    std::cout << "false" << std::endl;
	  delete filemanager;	  
	}
      else
	{
	  FileManager* filemanager = new FileManager();
	  filemanager->SetAllFile();
	  std::string filename = argv[1];
	  AnalizeFile file(filename);
	  bool b = filemanager->isexistsamefile(file);
	  if(b == true)
	    std::cout << "true" << std::endl;
	  if(b == false)
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
