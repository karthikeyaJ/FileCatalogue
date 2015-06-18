#ifndef DATASTORE_H
#define DATASTORE_H
/////////////////////////////////////////////////////////////////////////////
// DataStore.h : Provides Storage class for Paths and FileNames            //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Venkata Karthikeya Jangal                                   //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell , Core i5, Windows 8.1 SP1                            //
// Author:      Venkata Karthikeya Jangal								   //
//              MS in CE, email: vjangal@syr.edu						   //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provies functions to save file paths and filenames in datastore
* Public Interface:
* =================
* 	void save(const std::string& filespec)
*   void save(const std::string& filename, const std::string& path)
*   void searchForSpecificPattern(std::string text, std::string pa)
*   void searching(std::string kkr)
*
* Required Files:
* ===============
* "FileSystem.h"
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILESYSTEM FileSystem.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 12 Feb 15
*/


// DataStore.h - Stub for DataStore class 

#include <vector>
#include <string>
#include <set>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "..\FileMgr\FileSystem.h"

class DataStore
{
public:
	using Path = std::string;
	using Paths = std::set<Path>;
	using PathIters = Paths::iterator;
	using ListOfIters = std::list<PathIters>;     //using ListOfIters = map < string, list < set < string >::iterator > >;
	using FoundFile = std::string;
	using FoundFiles = std::set<FoundFile>;
	using PathIterations = FoundFiles::iterator;
	using File = std::string;
	using Store = std::map<File, ListOfIters>;
	using iterator = Store::iterator;

	void save(const std::string& filespec)                             //saves path to the set container
	{
		paths.insert(filespec);
	}

	void save(const std::string& filename, const std::string& path)    //saves File anme and path to the map container
	{
		PathIters it;
		iterator f;
		std::string fn = filename;
		f = store.find(fn);
		if (f == store.end())                                      // if key in map is not found
		{
			store[filename].push_back(paths.insert(path).first);
		}
		else
		{
			ListOfIters temp = f->second;
			temp.push_back(paths.insert(path).first);
			store[filename] = temp;
		}
	}

	//lollipop
	void openSearch(iterator it, std::string text, FoundFiles& sf)
	{
		ListOfIters tempe = it->second;
		for (ListOfIters::iterator ite = tempe.begin(); ite != tempe.end(); ite++)
		{
			std::string filename = **ite + it->first;
			std::ifstream fileinput;
			int offset;
			std::string line;
			std::string search = text;
			fileinput.open(filename);
			if (fileinput.is_open())
			{
				while (!fileinput.eof())
				{
					getline(fileinput, line);
					if ((offset = line.find(search, 0)) != std::string::npos)
					{
						sf.insert(filename);
					}
				}
				fileinput.close();
			}
			else
				std::cout << "\n one file named " << filename << "was unable to open \n \n" << std::endl;
		}

	}


	void searchForSpecificPattern(std::string text, std::string pa)     //supports printing files for requirement 8. i.e,
	{																	//prints files which has text present in specific pattern
		FoundFiles sf;
		bool condition = true;
		std::string sentence = pa;
		std::istringstream iss(sentence);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} }; //putting patterns in vector
		std::vector<std::string> findFiles;
		if (store.size() == 0)
			std::cout << "\n =========No files found with given text. Reason: datastore is not built previously.Please give atleast one path and pattern to support text search in specified files===========\n";
		else if (tokens.size() == 0)
			std::cout << "\n =========\n No files found with given text. Reason: \n > Empty Pattern \n===========\n";
		for (size_t i = 0; i < tokens.size(); i++)
		{
			if (tokens.at(i) == "*.*")
			{
				condition = false;
				searching(text);
				break;
			}
		}
		//if (condition)
		//{
		//	for (iterator it = store.begin(); it != store.end(); it++)
		//	{
		//		std::string k = FileSystem::Path::fileSpec(".", it->first);
		//		std::string pk = FileSystem::Path::getExt(k);
		//		std::string actualext = "*." + pk;
		//		std::string l = FileSystem::Path::getFullFileSpec(k);
		//		for (size_t i = 0; i < tokens.size(); i++)
		//		{
		//			if (actualext == tokens.at(i))                             //comparing files in store to pattern
		//			{
		//				openSearch(it, text,sf);
		//			}
		//		}
		//	}
		//	for (PathIterations pi = sf.begin(); pi != sf.end(); pi++)
		//	{
		//		std::cout << "\n=========Entered text is present in file provided with absolutepath=============\n";
		//		std::cout << "\n" << *pi << "\n" << std::endl;
		//	}
		//	if (sf.size()==0)
		//		std::cout << "\n===============No files with entered text is present in Datastore==============\n";

		//}
		DoSearch(condition, tokens, text);
	}

	void DoSearch(bool condition, std::vector<std::string> tokens, std::string text)
	{
		if (condition)
		{
			for (iterator it = store.begin(); it != store.end(); it++)
			{
				std::string k = FileSystem::Path::fileSpec(".", it->first);
				std::string pk = FileSystem::Path::getExt(k);
				std::string actualext = "*." + pk;
				std::string l = FileSystem::Path::getFullFileSpec(k);
				for (size_t i = 0; i < tokens.size(); i++)
				{
					if (actualext == tokens.at(i))                             //comparing files in store to pattern
					{
						openSearch(it, text, sf);
					}
				}
			}
			for (PathIterations pi = sf.begin(); pi != sf.end(); pi++)
			{
				std::cout << "\n=========Entered text is present in file provided with absolutepath=============\n";
				std::cout << "\n" << *pi << "\n" << std::endl;
			}
			if (sf.size() == 0)
				std::cout << "\n===============No files with entered text is present in Datastore==============\n";

		}
	}

	void searching(std::string kkr)                        // searching the text present after /f option in the files present in containers
	{
		FoundFiles fs;
		std::cout << "\n#############################################################################\n";
		std::string te = "Searching the entered text:\"" + kkr + " \"\n";
		std::cout << te << std::endl;
		std::cout << "##############################################################################\n";
		std::cout << "\n here is the files with the given text: \n" + kkr + " \n";
		for (iterator it = store.begin(); it != store.end(); it++)
		{
			ListOfIters tempe = it->second;
			for (ListOfIters::iterator ite = tempe.begin(); ite != tempe.end(); ite++)
			{
				std::string file_name = **ite + it->first;
				std::ifstream fileinput;
				int offset;
				std::string line;
				std::string search = kkr;
				fileinput.open(file_name);
				if (fileinput.is_open())
				{
					while (!fileinput.eof())
					{
						getline(fileinput, line);
						if ((offset = line.find(search, 0)) != std::string::npos)
						{
							fs.insert(file_name);                           //storing found files in container
						}
					}
					fileinput.close();
				}
				else
					std::cout << "\n one file named " << file_name << "was unable to open \n \n" << std::endl;
			}
		}
		for (PathIterations pi = fs.begin(); pi != fs.end(); pi++)
		{
			std::cout << "\n" << *pi << "\n" << std::endl;
		}
	}

	iterator begin() { return store.begin(); }

	iterator end() { return store.end(); }

	Paths getPaths(){ return paths; }
	Store getStore(){ return store; }

private:
	Store store;
	Paths paths;
	FoundFiles fs, sf;
};
#endif

/*ListOfIters tempe = it->second;
for (ListOfIters::iterator ite = tempe.begin(); ite != tempe.end(); ite++)
{
std::string karthik = **ite + it->first;
std::ifstream fileinput;
int offset;
std::string line;
std::string search = text;
fileinput.open(karthik);
if (fileinput.is_open())
{
while (!fileinput.eof())
{
getline(fileinput, line);
if ((offset = line.find(search, 0)) != std::string::npos)
{
sf.insert(l);
}
}
fileinput.close();
}
else
std::cout << "\n one file named " << l << "was unable to open \n \n" << std::endl;
}*/