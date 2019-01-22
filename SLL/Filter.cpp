#include "Filter.h"
using namespace std;

//loads data from a .txt file (can be different sizes of data e.g. sometimes 7 sometimes 10 etc)
int LoadMeasurements(const WCHAR* outputFile, int data[], int maxSize)
{
	ifstream infile(outputFile);
	if (!infile)
	{
		return(UnknownError);
	}
	else
	{
		infile >> maxSize;
		for (int i = 0; i < maxSize; i++)
		{
			infile >> data[i];
		}
	}

	return(maxSize);
}

//loads a DLL by name and uses the function in the DLL
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString)
{
	typedef int(__cdecl *MYPROC)(int data[], int count, const WCHAR* parameterString);
	
		HINSTANCE hinstLib;
		MYPROC ProcAdd;
		BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

		

		hinstLib = LoadLibrary(L"DLL.dll");									//get a handle to the DLL module.

		if (hinstLib != NULL)												//if the handle is valid, try to get the function address.
		{
			ProcAdd = (MYPROC)GetProcAddress(hinstLib, "filter"); 							
			
			if (NULL != ProcAdd)											//if the function address is valid, call the function.
			{
				fRunTimeLinkSuccess = TRUE;
				if ((filter)(data, count, parameterString) == Success)		//calls the function
				{
					return(Success);
				}
				else
				{
					fFreeResult = FreeLibrary(hinstLib);
					return(InvalidParameters);
				}
				
			}
			else
			{
				fFreeResult = FreeLibrary(hinstLib);
				return(DllInvalidFormat);
			}
		}
		else
		{
			return(DllNotFound);
		}
		

	return 0;
}

//saves the data to a .txt file
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize)
{
	ofstream outfile(outputFile);
	if (!outfile)
	{
		return(UnknownError);
	}
	else
	{
		outfile << maxSize << endl;
		for (int i = 0; i < 7; i++)
		{
			outfile << data[i] << endl;
		}

		outfile.close();

		return(Success);
	}
}

