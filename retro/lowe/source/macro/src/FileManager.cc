#include "FileManager.hh"
#include <dirent.h>
#include <iostream>
#include <string>

ClassImp(FileManager)

std::string FileManager::directory = "/rhome/fujigami/retro/lowe/analizefile/";

FileManager::FileManager()
{
}

void FileManager::SetAllFile()
{
  DIR* dir;
  dir = opendir(directory.c_str());
  if(dir == NULL)
    {
      std::cout << "directory is not found";
      throw "void FileManager::SetAllFile()";
    }
  dirent* entry = readdir(dir);
  while(entry)
    {
      std::string sdname = entry->d_name;
      if(sdname.find(".csv") != std::string::npos)
	{
	  std::string fullpath = directory + sdname;
	  allfilemap[fullpath] = AnalizeFile(fullpath);
	}
      entry = readdir(dir);
    }
}

void FileManager::printfilelist()
{
  std::cout << "file name table" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  for(auto iter = allfilemap.begin();iter != allfilemap.end();iter++)
    {
      std::cout << (*iter).first << std::endl;
    }
  std::cout << "---------------------------------------------" << std::endl;
}

void FileManager::reflectNarrowDownTag(std::string filetype)
{
  selectedfilemap.clear();
  std::vector<int> isselected(allfilemap.size(),1);
  for(auto itertag = narrowdowntag.begin();itertag != narrowdowntag.end();itertag++)
    {
      std::vector<int> isselectedone(allfilemap.size(),0);
      int i = 0;
      for(auto iterfile = allfilemap.begin();iterfile != allfilemap.end();iterfile++,i++)
	{
	  if((*iterfile).second.hasEqualTag((*itertag)))
	    isselectedone.at(i) = 1;
	}
      for(int k = 0;k != (int)allfilemap.size();k++)
	{
	  if(isselectedone.at(k) == 0)
	    {
	      isselected.at(k) = 0;
	    }
	  
	}
    }
  int j = 0;
  for(auto iter = allfilemap.begin();iter != allfilemap.end();iter++,j++)
    {
      if((isselected.at(j) == 1 )&&((*iter).first.find(filetype) != std::string::npos))
	{
	  selectedfilemap[(*iter).first] = (*iter).second;
	}
    }
}

void FileManager::printselectedfile()
{
  std::cout << "selected file table" << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;
  for(auto iter = selectedfilemap.begin();iter != selectedfilemap.end();iter++)
    {
      std::cout << (*iter).first << std::endl;
    }
  std::cout << "-----------------------------------------------------" << std::endl;
}

bool FileManager::isexistsamefile()
{
  for(auto iter = allfilemap.begin();iter != allfilemap.end();iter++)
    {
      for(auto iter2 = allfilemap.begin();iter2 != allfilemap.end();iter2++)
	{
	  if((*iter).first != (*iter2).first)
	    {
	      if((*iter).second == (*iter2).second)
		return true;
	    }
	}
    }
  return false;
}

bool FileManager::isexistsamefile(AnalizeFile file)
{
  for(auto iter = allfilemap.begin();iter != allfilemap.end();iter++)
    {
      if((*iter).first != file.filecsv)
	{
	  if((*iter).second == file)
	    return true;
	}
    }
  return false;
}

void FileManager::setselectedfile(std::string filename){
  selectedfilemap[filename] = AnalizeFile(filename);
}
