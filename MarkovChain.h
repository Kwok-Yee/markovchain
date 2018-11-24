#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	// calculate the weather state
	DllExport int calculateWeatherState(int size, double ** p);

	// return the random number 
	DllExport double getRandom();

	// calculate the random number
	DllExport double calculateRandom(double min, double max);

	// calculate the transition
	DllExport int calculateTransition(int index);

	void validateProbabilities(int size, double ** p);
}