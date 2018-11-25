#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	// Validate the probabilities
	void validateProbabilities(int size, double ** p);

	// Calculate the random number
	DllExport double calculateRandom(double min, double max);

	// Calculate the transition
	DllExport int calculateTransition(int size, int ** t, double ** p, int index);

	// Calculate the weather state
	DllExport int calculateWeatherState(int size, int ** trans, double ** p);
}