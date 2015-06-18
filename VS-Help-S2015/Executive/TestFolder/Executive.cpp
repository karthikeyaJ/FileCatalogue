/////////////////////////////////////////////////////////////////////////////
// Executive.cpp :  Command line args processing and responsible           // 
//                         for interacting with other packages             //
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

#include <iostream> 
#include <cstdlib> 
#include "..\FileMgr\FileMgr.h"
#include "..\Display\Display.h"

void recur(std::vector<std::string> options_, std::vector<std::string> paath_, DataStore& ds,bool f) //Adding patterns and searching
{                                                                                      // recursive if bool is true
	bool flag = f;
	std::string path = *(paath_.begin());
	FileMgr fm(path, ds);
	for (size_t i = 1; i < paath_.size(); i++)
	{
		fm.addPattern(paath_[i]);
	}
	fm.search(path, flag);
}

void printDupFile(std::vector<std::string> options_, std::vector<std::string> paath_, DataStore& ds, bool f)
{																					//prints duplicate files is /s is already given
	Display dstr;																	// else build datastore and print
	if (f)
	{
		dstr.dupFiles(ds);
	}
	else
	{		
		recur(options_, paath_, ds, f);
		dstr.dupFiles(ds);
	}
}

void process(std::vector<std::string> options_, std::vector<std::string> paath_, DataStore& ds, FileMgr fm, int argc, std::string text)
{                                                                              //processing file paths
	Display dstr;
	bool f = false;
	if (paath_.size() < 2)
	{
		std::cout << "Please enter pattern also" << std::endl;
		return;
	}
	else
	{
		for (size_t i = 0; i < options_.size(); i++)
		{
			if (options_[i] == "/s")
			{
				f = true;
				recur(options_, paath_, ds, f);
				dstr.print(ds);
			}
		}
		for (size_t i = 0; i < options_.size(); i++)
		{
			if (options_[i] == "/d")
			{
				printDupFile(options_, paath_, ds, f);
			}
			else if (options_[i] == "/f")
			{
				fm.textSearch(text);
			}
		}
	}
}

void demonReq(DataStore& ds)
{
	Display t;
	t.printingString("\n\n#############################################################################");
	t.printingString("Demonstrating the requirement 8.\n");
	t.printingString("################################################################################\n\n");
	t.printingString("\n Please enter the text to be searched.\n");
	std::string reqText;
	std::getline(std::cin, reqText);
	t.printingString("\n Please enter the pattern to search in.\n");
	std::string patternz;
	std::getline(std::cin, patternz);
	ds.searchForSpecificPattern(reqText, patternz);
}


int main(int argc, char** argv)
{
	bool flag = false;
	std::string text="";
	DataStore ds,m;
	Display n;
	std::vector<std::string> options_,paath_;
	n.printingString("Processing........................... \n");
	try{
		if (argc < 3)
		{
			n.printingString("Please enter atleast 2 inputs:path and pattern:\n");
			return 0;
		}
			std::string path = argv[1];
			FileMgr fm(path, ds);
		if (argc >= 3)
		{
			for (int k = 1; k < argc; k++)
			{
				if (strcmp(argv[k], "/s") == 0 || strcmp(argv[k], "/d") == 0 || strcmp(argv[k], "/f") == 0)
				{
					if ( (strcmp(argv[k], "/f") == 0) && ((k + 1) < argc))
					{
						text = argv[k + 1];
						options_.push_back(argv[k]);
						break;
					}
					else if ((strcmp(argv[k], "/f") == 0) && ((k + 1) >= argc))
					{
						n.printingString("#############################################################################\n");
						n.printingString("This information is regarding File search.Please enter text after /f to search properly \n ");
						n.printingString("################################################################################\n\n");
						break;
					}
					else
					options_.push_back(argv[k]);
				}
				else
					paath_.push_back(argv[k]);				
			}
			process(options_, paath_, ds,fm,argc,text);
		}
		demonReq(ds);
	}
	catch (std::exception e)
	{
		n.printingString(e.what());
	}
	return 0;
}



