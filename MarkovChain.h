#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	// calculate the weather state
	DllExport int calculateWeatherState();
	// return the probability
	DllExport double getProbability();
	// return the random number 
	DllExport double getRandom();
	// calculate the random number
	DllExport double calculateRandom();
	// calculate the transition
	DllExport int calculateTransition(int index);
}