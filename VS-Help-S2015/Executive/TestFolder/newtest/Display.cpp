/////////////////////////////////////////////////////////////////////////////
// Display.cpp :  Testing functions for printing the output                //
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
#include "Display.h"
#include <iostream>
#include "..\FileMgr\FileMgr.h"


#ifdef DISPLAY_H
int main()
{
	std::cout << "\n  Testing Display class";
	std::cout << "\n =======================\n";
	DataStore ds;
	Display dstr;
	FileMgr fm(".", ds);
	fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	fm.search(".",true);
	dstr.print(fm.get());
	return 0;
}
#endif