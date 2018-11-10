#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	DllExport int calculateWeatherState();
	DllExport double getProbability();
	DllExport double getRandom(double min, double max);
	DllExport int calculateTransition(int index);
}