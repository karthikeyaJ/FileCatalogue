/////////////////////////////////////////////////////////////////////////////
// DataStore.cpp : Provides Storage class for Paths and FileNames          //
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

#include "DataStore.h"
#include <iostream>

#ifdef TEST_DATASTORE
int main()
{
  DataStore ds;
  ds.save("d:/one"); 
  ds.save("d:/two");
  ds.save("d:/three");
  ds.save("karthik.cpp", "c:/karthik");
  DataStore::iterator iter = ds.begin();
  for (auto elem : ds)
  {
	std::cout << "\n" << elem.first << std::endl;
  }
  std::cout << "\n\n";
  return 0;
}
#endif
