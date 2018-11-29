#pragma once

#define DllExport __declspec(dllexport) 

extern "C"
{
	// Validate the probabilities
	void validateProbabilities(int size, double ** p, bool debug);

	// Calculate the random number
	double calculateRandom(double min, double max);

	// Calculate the transition
	int calculateTransition(int size, int ** t, double ** p, int index);

	// Calculate the weather state
	DllExport int calculateWeatherState(int size, int ** trans, double ** p);
}