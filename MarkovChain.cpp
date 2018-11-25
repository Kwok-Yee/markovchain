// MarkovChain.cpp : Defines the exported functions for the DLL application.
//

#include "MarkovChain.h"
#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

extern "C" {
#define STATES 4

	bool validated = false;
	int transition = 0;
	double random = 0;
	int currentState = 0;

	// Validating each row for the probabilities to add up to 1 
	void validateProbabilities(int size, double ** p)
	{
		double total = 0;
		for (size_t i = 0; i < size; i++)
		{
			cout << "Row " << i << ": ";
			for (size_t j = 0; j < size; j++)
			{
				total += p[i][j];
				cout << p[i][j] << " ";
			}
			if (i == 0)
				cout << "== " << total << endl;
			else
				cout << "== " << total - i << endl;
		}
		assert(total - size < 0.000001);
		validated = true;
	};

	// Calculate a random double value
	__declspec(dllexport) double calculateRandom(double min, double max)
	{
		double r = (double)rand() / RAND_MAX;
		return min + r * (max - min);
	}

	// Calculate the transtition from one state to another
	__declspec(dllexport) int calculateTransition(int size, int ** t, double ** p, int index)
	{
		int c = 0;
		double max = 1;
		random = calculateRandom(0, max);

		for (size_t i = 0; i < size; i++)
		{
			random -= p[index][i];
			if (random <= 0)
				return t[index][i];
		}
	}

	// Calculate the new weather state
	__declspec(dllexport) int calculateWeatherState(int size, int ** t, double ** p)
	{
		if (!validated)
			validateProbabilities(size, p);

		transition = calculateTransition(size, t, p, currentState);

		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (transition == t[i][j])
				{
					currentState = j;
				}
			}
		}
		return currentState;
	}
}

