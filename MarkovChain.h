#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	// calculate the weather state
	DllExport int calculateWeatherState();
	// return the probability
	DllExport double getProbability();
	// return a random number 
	DllExport double getRandom(double min, double max);
	// calculate the transition
	DllExport int calculateTransition(int index);
}