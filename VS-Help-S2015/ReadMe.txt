***********************************************************************************************************
**********************************************ReadMe*******************************************************
***********************************************************************************************************


***********************************************************************************************************
This project was tested for following outputs:
***********************************************************************************************************
 "." *.* /s /d /f text
 "." *.* /f text
 "." *.* /s 
 "." *.* /d
 "." *.* /d /s
 "." *.* /s /d
 "." *.* /f text /s /d

***********************************************************************************************************
Expected behaviour:
***********************************************************************************************************
 a)Whenever there is /d in the list of options all the dup files are printed
 b)Whenever there is /s in the list of options all the folders are searched recursively and printed
 c)Please give text to be searched after /f like this :
   "." *.* /f text
   "." *.* /s /d /f text
 d)This Project always takes path as first input. So this is fixed and rest of all the options can be given in any order according to user    needs.
 e) Execution starts from the main function of Executive package.
 