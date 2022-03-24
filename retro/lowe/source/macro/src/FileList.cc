// c++ STL
#include <fstream>
#include <iostream>
#include <cstring>
// ROOT library
#include <TFile.h>
// self-introduced library
#include "FileList.hh"

ClassImp(FileList)

FileList::FileList()
{
}


FileList::FileList(const char* filelist,int NFile)
  :TClonesArray("TFile",NFile)
{
  std::ifstream file(filelist);
  std::string str;
  if(file.fail())
    {
      std::cout << "failed to open file" << std::endl;
      std::cout << "Error: " << strerror(errno) << std::endl;
      throw "FileList::FileList(const char* filelist)";
    }
  
  for(int i = 0;std::getline(file,str);i++)
    {
      new((*this)[i]) TFile(str.c_str());
    }
 }
