/////////////////////////////////////////////////////////////////////////////
// FileMgr.cpp - Collects file specifications from directory tree          //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Venkata Karthikeya Jangal, 2015                             //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Dell , Core i5, Windows 8.1 SP1                            //
// Author:      Venkata Karthikeya Jangal								   //
//              MS in CE, email: vjangal@syr.edu						   //
/////////////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include "..\Display\Display.h"

#include <iostream>
#include <string>

void FileMgr::search(const std::string& path,bool k)  //searching files
{
	for (auto patt : patterns_)
	{

		find(path_, patt);
	}

	for (auto patt : patterns_)
	{

		if (k==true)
		recursive(path_, patt);
	}
}

void FileMgr::find(const std::string& path,std::string patt)      //finding files with specific pattern from path
{
		std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
		for (auto f : files)
		{
			std::string k;
			std::string l;
			std::string kl;
			k = FileSystem::Path::fileSpec(path, f);
			l = FileSystem::Path::getFullFileSpec(k);
			kl = FileSystem::Path::getPath(l);
			store_.save(kl);
			store_.save(f, kl);
	}
}

// recursive search of directories----------------------------
void FileMgr::recursive(const std::string& path,std::string s)
  {
    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(path);
    // remove "." and ".." from dirs
    auto iter = std::find(std::begin(dirs), std::end(dirs), ".");
    if (iter != std::end(dirs))
    {
      dirs.erase(iter);
    }
    iter = std::find(std::begin(dirs), std::end(dirs), "..");
    if (iter != std::end(dirs))
    {
      dirs.erase(iter);
    }
    for (auto d : dirs)
    {		
		std::string lk = path_ + "\\" + d;
		std::string p;
		std::string q;
		p = FileSystem::Path::fileSpec(path, d);
		q = FileSystem::Path::getFullFileSpec(p);
		std::vector<std::string> files = FileSystem::Directory::getFiles(q, s);
		for (auto f : files)
		{
			std::string k;
			std::string l;
			std::string pq;
			k = FileSystem::Path::fileSpec(p, f);
			l = FileSystem::Path::getFullFileSpec(k);
			pq = FileSystem::Path::getPath(l);
			store_.save(pq);
			store_.save(f, pq);
		}
		recursive(lk, s);
	}
  }

  void FileMgr::textSearch(std::string& mystring)                   //text search
  {
	  std::string k = mystring;  
	  store_.searching(k);
  }



#ifdef TEST_FILEMGR

int main()
{
  std::cout << "\n  Testing FileMgr class";
  std::cout << "\n =======================\n";
  DataStore ds; 
  Display dstr;
  FileMgr fm(".", ds);
   fm.addPattern("*.h");
  fm.addPattern("*.cpp");
  fm.search(".",true);
  dstr.print(fm.get());
  //hi
  std::string pk="karthik";
  fm.textSearch(pk);
  return 0;
}

#endif 
