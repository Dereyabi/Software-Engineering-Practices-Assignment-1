
#include <Windows.h>
#ifndef ASEXPORT
#define DLLIMPORTOREXPORT dllimport
#else
#define DLLIMPORTOREXPORT dllexport
#endif

_declspec(DLLIMPORTOREXPORT) int filter(int data[], int count, const WCHAR* parameterString);


