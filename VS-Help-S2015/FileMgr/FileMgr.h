#ifndef FILEMGR_H
#define FILEMGR_H
/////////////////////////////////////////////////////////////////////////////
// FileManager.h :It is responsible for handling files and searching       //
//                iteratively if /s is given. Also responsible for adding  //
//                patterns. Basically it Collects file specifications      //
//                from directory tree									   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Venkata Karthikeya Jangal, 2015                             //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell , Core i5, Windows 8.1 SP1                            //
// Author:      Venkata Karthikeya Jangal								   //
//              MS in CE, email: vjangal@syr.edu						   //
/////////////////////////////////////////////////////////////////////////////
/*
* Public Interface:
* =================
* FileMgr(const std::string& path, DataStore& store) : path_(path), store_(store)
* void addPattern(const std::string& patt)
* void search(const std::string& path,bool flag);
* void recursive(const std::string& path, std::string pa);
* patterns  gets(){ return patterns_; }

* Required Files:
* ===============
* "DataStore.h"
* "Display.h"
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILESYSTEM FileSystem.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 12 Feb 15
****************************************************************************************/
#include "FileSystem.h"
#include "..\DataStore\DataStore.h"
#include "..\Display\Display.h"

#include <vector>
#include <string>

class FileMgr
{
public:
  using iterator = DataStore::iterator;
  using patterns = std::vector < std::string > ;
  FileMgr(const std::string& path, DataStore& store) : path_(path), store_(store) 
  {
    patterns_.push_back("*.*");
  }
  void addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }
  void search(const std::string& path,bool flag);
  void recursive(const std::string& path, std::string pa);
  void textSearch(std::string& mystring);
  void find(const std::string&path, std::string p);
  iterator begin() { return store_.begin(); }
  iterator end() { return store_.end(); }

  patterns  gets(){ return patterns_; }
  DataStore get(){ return store_; }
private:
  DataStore& store_;
  std::string path_;
  patterns patterns_;
  Display d;
};
#endif
