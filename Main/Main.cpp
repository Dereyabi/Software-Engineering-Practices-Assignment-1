// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Filter.h"




int main()
{
	int maxSize = 0;					//maximum size of the data 
	int data[MAX_DATA];					//data read in from the input file			
	int useFilterResult;				//used to show any error messages recieved from the useFilter function

	maxSize = LoadMeasurements(L"inputFile.txt", data, MAX_DATA);					//recieves the size of the data array 

	assert(maxSize >= 0);

	if (maxSize == UnknownError)											
	{
		cout << "File Unable to Load - Unknown Error" << endl;
	}

#ifdef _DEBUG

	for (int i = 0; i < maxSize; i++)
	{
		cout << data[i] << endl;
	}

#endif // DEBUG

	

	useFilterResult = UseFilter(L"DLL.DLL", data, maxSize, L"3 6");				//loads the dll and calls the filter function

	if (useFilterResult == Success && maxSize != UnknownError)
	{
		cout << "Filter Successfully Used" << endl;

		if (SaveMeasurements(L"outputFile.txt", data, maxSize) == UnknownError)		//if the dll is successfully loaded and filter successfully used, the data is saved in an output file
		{
			cout << "an Unknown Error Has Occured" << endl;
		}
		else
		{
			cout << "Data Successfully Saved" << endl;
		}
		
	}
	else if (useFilterResult == DllNotFound)
	{
		cout << "Unable to find import function in the dll" << endl;
	}
	else if (useFilterResult == InvalidParameters)
	{
		cout << "Invalid parameters entered" << endl;
	}
	else if (useFilterResult == DllInvalidFormat)
	{
		cout << "DLL Invalid Format" << endl;
	}
	else
	{
		cout << "Unknown Error" << endl;
	}

#ifdef _DEBUG

	for (int i = 0; i < maxSize; i++)
	{
		cout << data[i] << endl;
	}

#endif // DEBUG

	system("pause");

    return 0;
}

