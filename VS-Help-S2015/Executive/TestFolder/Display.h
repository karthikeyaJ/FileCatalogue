#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////////////
// Display.h :Supports printing the output on the command line             //
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
* Module Operations:
* ==================
* This module provides display functions to print the output to the command line
* Public Interface:
* =================
* void totalFiles(DataStore s)
* void dupFiles(DataStore& s)
* void searching(std::string kkr)
* void print(DataStore& store)
*
* Required Files:
* ===============
* "DataStore.h"
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILESYSTEM FileSystem.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 12 Feb 15
****************************************************************************************/


#include <vector>
#include <string>
#include <set>
#include <list>
#include <map>
#include<iostream>
#include "..\DataStore\DataStore.h"

	static class Display
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

		void totalFiles(DataStore s)   // Prints the total number of files if no options are given i.e SUMMARY is printed
		{
			std::cout <<" ------------------------------------------------------------------ "<< std::endl;
			std::cout << "No options are entered \n There are " << (s.getPaths().size())  <<" number of files present in this directory"<<std::endl;
			std::cout << " ------------------------------------------------------------------ " << std::endl;
		}

		void dupFiles(DataStore& s)     //Prints the duplicate files present in the data store
		{
			std::cout << "\n###############################################################################\n " << std::endl;
			std::cout << "Duplicate files are: \n " << std::endl;
			std::cout << "################################################################################\n " << std::endl;			
			for (iterator pt = s.begin(); pt != s.end(); pt++)
			{
				ListOfIters tempe = pt->second;
				if (tempe.size() > 1)
				{
					std::cout << "file name is:: " << pt->first << "\n\n";				
					for (ListOfIters::iterator ite = tempe.begin(); ite != tempe.end(); ite++)
					{
						std::cout << "path is" << **ite << "\n\n";
					}
				}
				else
					std::cout << "\n---------No duplicate files are found--------------\n\n";
			}		
		}

		void searching(std::string kkr)                 // Printing the searched files which has the text entered
		{
			std::cout << "\n#############################################################################\n" << std::endl;
			std::cout << "Searching the entered text:\" " << kkr << " \"\n" << std::endl;
			std::cout << "##############################################################################\n" << std::endl;
			std::cout << "\n here is the files with the given text: \n" << kkr << " \n" << std::endl;
			for (PathIters it = paths.begin(); it != paths.end(); ++it)
			{
				std::ifstream fileinput;
				int offset;
				std::string line;
				std::string search = kkr;
				fileinput.open(*it);
				if (fileinput.is_open())
				{
					while (!fileinput.eof())
					{
						getline(fileinput, line);
						if ((offset = line.find(search, 0)) != std::string::npos)
						{
							fs.insert(*it);
						}

					}
					fileinput.close();
				}
				else
					std::cout << "\n one file named " << *it << "was unable to open \n \n" << std::endl;
			}
			for (PathIterations pi = fs.begin(); pi != fs.end(); pi++)
			{
				std::cout << "\n" << *pi << "\n" << std::endl;
			}			
		}


		void print(DataStore& store)               //Printing the list of files and paths stored in the datastore
		{
			std::cout << "###########################################################################" << std::endl;
			std::cout << "Printing list of files and paths" << std::endl;
			std::cout << "################################################################################\n" << std::endl;
			for (iterator it = store.begin(); it != store.end(); it++)
			{
				std::cout << ">>>>>>>>>file name is :" << it->first << "\n";
				ListOfIters tempe = it->second;
				for (ListOfIters::iterator ite = tempe.begin(); ite != tempe.end(); ite++)
				{
					std::cout << "path is---> " << **ite << "\n\n";
				}
			}
			std::cout << "------------------------------------------ \n";
		}

		void printingString(std::string k)
		{
			std::cout << k << std::endl;
		}



	private:
		Store store;
		Paths paths;
		FoundFiles fs;
	}dis;

#endif