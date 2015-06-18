#ifndef FILEMGR_H
#define FILEMGR_H

// FileMgr.h - Collects file specifications from directory tree

#include "FileSystem.h"
#include "..\DataStore\DataStore.h"
#include <vector>
#include <string>

class FileMgr
{
public:
  using iterator = DataStore::iterator;
  using patterns = std::vector < std::string > ;
  //using iterator = DataStore::iterator;

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
  void search();
  void find(const std::string&path);
  iterator begin() { return store_.begin(); }
  iterator end() { return store_.end(); }

private:
  DataStore& store_;
  std::string path_;
  patterns patterns_;
};
#endif
