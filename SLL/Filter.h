#ifndef INSERTSLL
#define INSERTSLL
#endif 



#include <Windows.h>
#include <fstream>
#include <iostream>
#include <cassert>
using namespace std;

//function return values 
const int Success = 0;
const int Failure = -1;
const int DllNotFound = -2;			//can't find dll to import
const int DllInvalidFormat = -3;	//Unable to find import function in the dll
const int UnknownError = -4;		
const int InvalidParameters = -5;	

const int MAX_DATA = 1000;			// the maximum size of the array for loading data 

int LoadMeasurements(const WCHAR* outputFile, int data[], int maxSize);								//loads data into an array from a specified input text document
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString);			//loads the dll, calls the filter function in the dll which then filters the data array
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize);								//saves the filtered data to an output document 

#ifndef ASEXPORT																					//if not defined will inport the function rather than exporting 
#define DLLIMPORTOREXPORT dllimport
#else
#define DLLIMPORTOREXPORT dllexport
#endif


#ifdef __cplusplus																					//enables the use of c-style strings and prevent name mangling when calling the function below
extern "C" 
{
#endif
	_declspec(DLLIMPORTOREXPORT) int filter(int data[], int count, const WCHAR* parameterString);

#ifdef __cplusplus
}
#endif