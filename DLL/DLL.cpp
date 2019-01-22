// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#define ASEXPORT
#include "../SLL/Filter.h"

int filter(int data[], int count, const WCHAR* parameterString)
{
	int sizeOfString = wcslen(parameterString); //gets the size of the string
	
	const int ASCIISpace = 32;					//values for ASCII symbols, parameterString outputs them instead of numbers
	const int ASCIIPlus = 43;
	const int ASCIIMinus = 45;
	const int ASCIIZero = 48;
	const int ASCIINine = 57;

	int noOfSigns = 0;							//increments if a sign is found
	int numberOfSpaces = 0;						//if this isnt 1 after the array for loop has finished, outputs InvalidParameter 
	int stringArray[2];							//holds a number before a space has been detected
	int arrayCount = 0;							//increments depending on how many characters are in parameter string after spaces are taken away


	if (sizeOfString < 2)						//stops less than 2 characters being inputted into the parameter string
	{
		return(InvalidParameters);
	}

	for (int i = 0; i < sizeOfString; i++)		//error checking, detects amount of spaces, how many signs there are and if the numbers are between 0 and 9
	{
		if ((int)*(parameterString + i) == ASCIISpace)
		{
			numberOfSpaces++;
			noOfSigns = 0;
		}
		else if ((int)*(parameterString + i) == ASCIIPlus)				
		{																
			noOfSigns++;												
			if (noOfSigns > 1)											
			{															
				return(InvalidParameters);
			}
		}
		else if ((int)*(parameterString + i) == ASCIIMinus)
		{
			noOfSigns++;
			if (noOfSigns > 1)
			{
				return(InvalidParameters);
			}

		}
		else if ((int)*(parameterString + i) < ASCIIZero || (int)*(parameterString + i) > ASCIINine)
		{
			return(InvalidParameters);
		}
	}

	if (numberOfSpaces != 1)									//makes sure there is only 1 space in the parameter string
	{
		return(InvalidParameters);
	}

	WCHAR*& pEnd = const_cast<WCHAR*&>(parameterString);		//changes a constant WCHAR to a WCHAR to prevent any errors 
	while(*pEnd != '\0')
	{															//method for changing a WCHAR to an array of integers 
		stringArray[arrayCount] = (int)(wcstod(pEnd, &pEnd));	//stores the intagers in the amount of arrays equal to the amount of times that the while loop, loops.
		arrayCount++;											//e.g. if it goes through the while loop 2 times there will be 2 arrays
	}

	for (int i = 0; i < count; i++)							
	{
		if (data[i] < stringArray[0])							//all data in the array is checked to see if it is smaller than the first parameter
		{
			data[i] = stringArray[0];							//if it is, the data is set to that number
		}
		else if (data[i] > stringArray[1])						//checks whether the data is bigger than the second parameter
		{
			data[i] = stringArray[1];							//data is set to that number if it is
		}
	}

	return(Success);
}


